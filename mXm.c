#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
#include <time.h> 		// for random
#include <sys/time.h> 	// for clock()
//Compile with:  gcc mXm.c -o mxm -std=c99 -lpthread

/* Simplify by making sizes and arrays global */
#define m 2048
#define n 1024
#define p 1024
#define MAX_DISP 5
#define NUM_THREADS 4

static int m1[m][n];
static int m2[n][p];
static int dest[m][p];
static int copy[m][p];
static int ranges[NUM_THREADS+1];

void mXm_nothread();
void setRanges();
void *threadFunct( void* index );
void mXm_multi();
void dispElapsed( time_t t1, time_t t2 );
void initMatrix( int mRows, int nCol , int matrix[][nCol], int val );
void initRand( int mRows, int nCol , int matrix[][nCol] );
void dispMatrix( int mRows, int nCol , int matrix[][nCol] );
int copyMatrix( int mRows, int nCol, int from[][nCol], int to[][nCol] );
int sameMatrix( int mRows, int nCol, int m1[][nCol], int m2[][nCol] );

int main( int argc, char *argv[] ) {
	int dispAll=( m<=MAX_DISP && n<=MAX_DISP && p<=MAX_DISP );
	time_t startTime, elapsed1, elapsed2;
	/* Create matrices */
	srand(time(0));
	initRand( m, n, m1 );
	initRand( n, p, m2 );
	initMatrix( m, p, dest, 0 );//uninitialized values vary on different systems
	if(dispAll){
		/* Display matrices if not too big */
		printf("m1 before\n" );
		dispMatrix( m, n, m1 );
		printf("m2 before\n" );
		dispMatrix( n, p, m2 );
		printf("dest before\n" );
		dispMatrix( m, p, dest );
	}
	/* First pass: unthreaded function */
	startTime=clock();
	mXm_nothread();
	elapsed1=clock()-startTime;
	if(!dispAll){
		printf("Display truncated:  " );
	}
	printf("Result Method 1\n" );
	dispMatrix( m, p, dest );
	/* Second pass: threaded */
	copyMatrix( m, p, dest, copy );	//backup copy for testing
	initMatrix( m, p, dest, 0 );	//need to start with zero matrix
	setRanges();
	startTime=clock();
	mXm_multi();
	elapsed2=clock()-startTime;
	dispElapsed( elapsed1, elapsed2 );

	if(!dispAll){
		printf("Display truncated:  " );
	}
	printf("Result Method 2\n" );
	dispMatrix( m, p, dest );
	if( sameMatrix( m, p, dest, copy ) ){
		printf("Success: results are equal\n" );
	}
	else{
		printf("Fail: results not equal\n" );
	}
	exit(0);
}

void mXm_nothread(){
	/* m1 = [ m, n ]
	 * m2 = [ n, p ]
	 * dest = [ m, p ] 
	 * */
	int i, j, k;
	for ( i = 0; i < m; i++ ) {
		if(i%500==0){
			printf("mXm_nothread: i=%d\n", i );
		}
		for ( j = 0; j < p; j++ ) {
			for ( k = 0; k < n; k++ ) {
				dest[i][j]+=m1[i][k]*m2[k][j];
			}
		}
	}
}
void setRanges(){
	int i, start=0,range=m/NUM_THREADS;
	//printf( "setRanges: range=%d\n", range );
	for( i=0; i<NUM_THREADS; i++ ){
		ranges[i]=start;
		//printf( "  i=%d, start=%d\n", i, ranges[i] );
		start+=range;
	}
	ranges[NUM_THREADS]=m;
	//printf( "  last range =%d\n", ranges[NUM_THREADS] );
}
void *threadFunct( void* param ){
	int index=(int)(long)param, i, j, k;
	int start=ranges[index], end=ranges[index+1];
	int count=0;
	//printf( "threadFunct: start=%d, end=%d\n", start, end );
	for( i = start; i < end; i++ ){
		if(i%500==0){
			printf("threadFunct: i=%d\n", i );
		}
		for( j = 0; j < p; j++ ) {
			for( k = 0; k < n; k++ ) {
				dest[i][j]+=m1[i][k]*m2[k][j];
			}
		}
		count++;
	}
	//printf( "thread %d: ran %d times\n", index, count );
	pthread_exit(NULL);
} 
void mXm_multi(){
	/* m1 = [ m, n ]
	 * m2 = [ n, p ]
	 * dest = [ m, p ] 
	 * */
	int i, err;
	pthread_t threads[NUM_THREADS];
	for ( i = 0; i < NUM_THREADS; i++ ) {
	   err = pthread_create( &threads[i], NULL, threadFunct, (void*)(long)i );
	   if( err ){
		   printf( "Error: return code from pthread_create is %d\n", err );
		   exit(-1);
	   }
	}
	for ( i = 0; i < NUM_THREADS; i++ ) {
	   pthread_join( threads[i], NULL );
	}
}
void dispElapsed( time_t t1, time_t t2 ){
	time_t best_t, worst_t;
	int best, worst;
	if( t2>t1 ){
		best_t=t1;
		worst_t=t2;
		best=1;
		worst=2;
	}
	else{
		best_t=t2;
		worst_t=t1;
		best=2;
		worst=1;
	}
	printf("Method %d took %ld microseconds (faster by %ld)\n", best, best_t, worst_t-best_t );
	printf("Method %d took %ld microseconds\n", worst, worst_t );
	printf("Ratio t%d/t%d:  %f\n", best, worst, best_t/(float)worst_t );
}
void initMatrix( int mRows, int nCol , int matrix[][nCol], int val ){
	/* Init 2-d array so every element equals val */
	int i, j;
	for( i=0; i<mRows; i++ ){
		for( j=0; j<nCol; j++ ){
			matrix[i][j]=val;
		}
	}
}
void initRand( int mRows, int nCol , int matrix[][nCol] ){
	/* Init 2-d array with random values 0-9 */
	int i, j;
	for( i=0; i<mRows; i++ ){
		for( j=0; j<nCol; j++ ){
			matrix[i][j]=rand() % 10;
		}
	}
}
void dispMatrix( int mRows, int nCol , int matrix[][nCol] ){
	/* Print 2-d array with tab-separated columns */
	int i, j;
	for( i=0; i<mRows && i<MAX_DISP; i++ ){
		for( j=0; j<nCol && j<MAX_DISP; j++ ){
			printf( "%d\t", matrix[i][j] );
		}
		printf( "\n" );
	}
}
int copyMatrix( int mRows, int nCol, int from[][nCol], int to[][nCol] ){
	/* Brute force copy */
	int i, j;
	for( i=0; i<mRows; i++ ){
		for( j=0; j<nCol; j++ ){
			to[i][j] = from[i][j];
		}
	}
	return 1;
}
int sameMatrix( int mRows, int nCol, int m1[][nCol], int m2[][nCol] ){
	/* Brute force equality tester */
	int i, j;
	for( i=0; i<mRows; i++ ){
		for( j=0; j<nCol; j++ ){
			if( m1[i][j] != m2[i][j] ){
				return 0;
			}
		}
	}
	return 1;
}
