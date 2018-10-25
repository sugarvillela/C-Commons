/* Some general functions, not all of them useful */


unsigned char decPlaces( unsigned short in ){
  /* Finds log 10 of input number */
	if( in==0 ){ return 1;}
	unsigned char i=0;
	for ( i=0; in && i< 0xFF; i++ ){
		in/= 10;
	}
	return i;
}
void nToChars( unsigned short in, unsigned char buf[] ){//buffer 6 for 16 bit range
  /* Returns input number in string form; buf size must be sufficient */
	unsigned char n = decPlaces( in );
	unsigned short next, curr;
	char i;
	for ( i=n-1; i>=0; i-- ){
		next = in/10;
		curr = in - ( next*10 );
		//printf( "curr %d, %c\n", curr, curr+'0' );
		buf[i]=curr+'0';
		in = next;
	}
	buf[n]='\0';
}

enum what{ invisible, notascii, lowercase, uppercase, digit, symbol  };
enum what whatIs( char c ){
  /* splits ascii into enumerated classes; see test below */
  if( c>127 ){
    return notascii;
  }
  if( c>126 ){
    return invisible;
  }
  if( c>122 ){
    return symbol;
  }
  if( c>96 ){
    return lowercase;
  }
  if( c>90 ){
    return symbol;
  }
  if( c>64 ){
    return uppercase;
  }
  if( c>57 ){
    return symbol;
  }
  if( c>47 ){
    return digit;
  }
  if( c>32 ){
    return symbol;
  }
  return invisible;
}
void testWhatIsIt(){
  int i=0;
  int j;
  char* text[] = {
    "invisible", "notascii", "lowercase", "uppercase", "digit", "symbol"
  };
  char* buf="I am 25!\t'Oops?'";
  while( buf[i] ){
    j=whatIs( buf[i] );
    printf( "%c: %s \n", buf[i], text[j] );
    i++;
  }
}
