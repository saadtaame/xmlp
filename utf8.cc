#include <cstdio>

using namespace std;

struct UTF8Char {
    unsigned char bytes[4];
    int num_bytes;

    UTF8Char(): num_bytes(0) {}

    UTF8Char( unsigned char bytes_[], int num_bytes_ ): num_bytes(num_bytes_) {
        for(int i = 0; i < num_bytes_; i++)
            bytes[i] = bytes_[i];
    }

    UTF8Char( unsigned char byte1 ): num_bytes(1) {
        bytes[0] = byte1;
    }

    UTF8Char( unsigned char byte1, unsigned char byte2 ): num_bytes(2) {
        bytes[0] = byte1;
        bytes[1] = byte2;
    }

    UTF8Char( unsigned char byte1, unsigned char byte2, unsigned char byte3 ): num_bytes(3) {
        bytes[0] = byte1;
        bytes[1] = byte2;
        bytes[2] = byte3;
    }

    UTF8Char( unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4 ): num_bytes(4) {
        bytes[0] = byte1;
        bytes[1] = byte2;
        bytes[2] = byte3;
        bytes[3] = byte4;
    }
};

UTF8Char utf8_getc( unsigned char *buf ) {
    static unsigned char *bufp = 0; /* pointer to current byte in buf */
    static unsigned char bytes[4];

    /* masks - masks for utf8 first byte prefix bits
       prefix - values for utf8 first byte prefix bits
       the subsequent bytes should all match the pattern 10xxxxxx
    */
    unsigned char masks[] = {128, 224, 240, 248};
    unsigned char prefix[] = {0, 192, 224, 240};

    if(buf) bufp = buf; /* new buffer to scan */

    if(*bufp == EOF)
        return UTF8Char(EOF);

    for(int i = 0; i < 4; i++) {
        if( ( masks[i] & (*bufp) )  == prefix[i] ) {
            bytes[0] = *bufp++;
            for(int j = 1; j < i + 1; j++) {
                if( ( 192 & (*bufp) ) != 128 )
                    /* illegal utf8 byte */
                    ;
                bytes[j] = *bufp++;
            }
            return UTF8Char(bytes, i + 1);
        }
    }

    /* illegal utf8 byte */
}

void utf8_putc( UTF8Char &c ) {
    for(int i = 0; i < c.num_bytes; i++)
        putchar(c.bytes[i]);
}

void cat( const char *fname ) {
    FILE *f;
    UTF8Char c;
    unsigned char buf[4096];

    f = fopen(fname, "rb");
    if(f != NULL) {
        int num_bytes_read = (int)fread(buf, sizeof(unsigned char), sizeof(buf), f);

        c = utf8_getc(buf);
        utf8_putc(c);

        for(int i = c.num_bytes; i < num_bytes_read; i += c.num_bytes)
            utf8_putc( c = utf8_getc(0) );

        fclose(f);
    }
}

int main( void ) {
    cat("doc.txt");
    return 0;
}
