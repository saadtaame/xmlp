#ifndef XMLP_UTF8_API_H_
#define XMLP_UTF8_API_H_

#include <cstdio>
#include <cstring>

struct UTF8Char {
    unsigned char bytes[4];
    int num_bytes;

    UTF8Char( void ): num_bytes(0) {}
    UTF8Char( unsigned char[], int );
    UTF8Char( unsigned char );
    UTF8Char( unsigned char, unsigned char );
    UTF8Char( unsigned char, unsigned char, unsigned char );
    UTF8Char( unsigned char, unsigned char, unsigned char, unsigned char );
};

UTF8Char utf8_getc( unsigned char * );
void utf8_putc( UTF8Char );

#endif // XMLP_UTF8_API_H_
