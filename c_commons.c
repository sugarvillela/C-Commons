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
unsigned char hexPlaces( unsigned short in ){
	/* Finds log 16 of input number */
	if( in==0 ){ return 1; }
	unsigned char i;
	for ( i=0; in && i< 0xFF; i++ ){
		in=in>>4;
	}
	return i;
}
void nToChars( unsigned short in, unsigned char buf[] ){//buffer size 6 for 16 bit range
  /* Returns input number in string form; buf size must be sufficient */
	unsigned char n = decPlaces( in );
	unsigned short next, curr;
	char i;
	for ( i=n-1; i>=0; i-- ){
		next = in/10;
		curr = in - ( next*10 );
		buf[i]=curr+'0';
		in = next;
	}
	buf[n]='\0';
}
void nToHex( unsigned short in, unsigned char buf[] ){//buffer size 5 for 16 bit range
	/* Writes input number in hexadecimal to string buf; buf size must be sufficient */
	unsigned char n = hexPlaces( in );
	char hex[]="0123456789ABCDEF";
	char i;
	for ( i=n-1; i>=0; i-- ){
		buf[i]=hex[in&0x0F];
		in=in>>4;
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
