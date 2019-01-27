/* 
   LZ78 is a lossless data compression algorithm published 
   by Abraham Lempel and Jacob Ziv in 1977

   Why? Because a large document is full of repeated terms.
   An article about Gorbachev would say that name about 100
   times.  If you replaced the name with an integer, you 
   could save some space.  How much? Nine letters of 1 or 2 
   bytes each, depending on encoding, vs an integer and a char.
   You do the math.

   Theres also the overhead of keeping the decode data, which
   is why it works best on large documents.

   The algorithm below is a pretty common 'accumulate and dump' 
   strategy. The trick is to make sure the last character 
   dumps correctly.

   For encode, pass a std:string and two node* vectors.
   The first vector is to store codes.
   The second vector is for the output.
   In Pythonese your output would look like this:
   [(index, data),(index, data),(index, data)...]

   For decode, pass the two filled vectors
   Returns the original string.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int
#define ulong unsigned long 

struct node{
    int i;
    string s;
    node( int seti, string sets ) : i(seti), s(sets){}  //constructor
};

void addto( vector<node*> &dict, int i, string pat ){//wrapper for vector push
    dict.push_back( new node( i, pat ) );
}

//FIND BY SEARCHING FOR THE STRING
int byData( vector<node*> &dict, string target ){
    for( uint i=0; i<dict.size(); i++){
    	if( dict[i]->s==target ){
    	    return dict[i]->i;
    	}
    }
    return 0;
}

//FIND BY SEARCHING FOR THE INDEX
string byIndex( vector<node*> &dict, int index ){
    for( uint i=0; i<dict.size(); i++){
    	if( dict[i]->i==index ){
    	    return dict[i]->s;
    	}
    }
    return "";
}
void encode( vector<node*> &book, vector<node*> &seq, string text ){
    string pat="";
    int found=0;
    for( uint i=0; i<text.length(); i++){
	    if( ( found=byData( book, pat+text[i] ) ) ){
	    	if( (i+1)==text.length() ){	//special case: found pattern at end of string
	    	    addto( seq, found, "" );    //The empty string here, because the pattern already contains it
	    	}
	    	pat += text[i];
	    }
	    else{
	    	found=byData( book, pat );	//This finds the previous pattern that's being used to make the new pattern
	    	addto( book, book.size()+1, pat+text[i] );//add pattern to book
	    	addto( seq, found, string(1, text[i]) );
	    	pat="";				//clear for next accumulate
	    }  	
    }
}

string decode( vector<node*> &book, vector<node*> &seq ){
    string out="";
    int index=0;
    for( uint i=0; i<seq.size(); i++){
	    if( ( index=seq[i]->i ) ){ 		//non-zero index means get it from the book
	        out+=byIndex( book, index );
	    }
	    out+=seq[i]->s;
    }
    return out;
}
void disp(  vector<node*> &dict ){
    for( uint i=0; i<dict.size(); i++){
    	cout << "(" << dict[i]->i << ", " << dict[i]->s<< ") ";
    }
    cout << endl<< endl;
}
int main( int argc, char**argv ) {//pass the input string in the command line
    vector<node*> book;
    vector<node*> seq;
    string text=(argc>1)? string(argv[1]) : "";
	
    cout << "Text=" << text << endl;
    cout << "ENCODE" << endl;
    encode( book, seq, text );
    cout << "BOOK" << endl;
    disp( book );
    cout << "SEQ" << endl;
    disp( seq );
    cout << "DECODE" << endl;
    cout << decode( book, seq ) << endl;
}
