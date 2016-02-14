#include "../api/utf8.h"

UTF8Char::UTF8Char( unsigned char bytes_[], int num_bytes_ ): num_bytes(num_bytes_) {
    for(int i = 0; i < num_bytes_; i++)
        bytes[i] = bytes_[i];
}

UTF8Char::UTF8Char( unsigned char byte1 ): num_bytes(1) {
    bytes[0] = byte1;
}

UTF8Char::UTF8Char( unsigned char byte1, unsigned char byte2 ): num_bytes(2) {
    bytes[0] = byte1;
    bytes[1] = byte2;
}

UTF8Char::UTF8Char( unsigned char byte1, unsigned char byte2, unsigned char byte3 ): num_bytes(3) {
    bytes[0] = byte1;
    bytes[1] = byte2;
    bytes[2] = byte3;
}

UTF8Char::UTF8Char( unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4 ): num_bytes(4) {
    bytes[0] = byte1;
    bytes[1] = byte2;
    bytes[2] = byte3;
    bytes[3] = byte4;
}

UTF8Char utf8_getc( Buffer &buf ) {
    static unsigned char bytes[4];

    /* masks - masks for utf8 first byte prefix bits
       prefix - values for utf8 first byte prefix bits
       the subsequent bytes should all match the pattern 10xxxxxx
    */
    unsigned char masks[] = {128, 224, 240, 248};
    unsigned char prefix[] = {0, 192, 224, 240};

    unsigned char byte = buf.next_byte();

    for(int i = 0; i < 4; i++) {
        if( ( masks[i] & byte )  == prefix[i] ) {
            bytes[0] = byte;
            for(int j = 1; j < i + 1; j++) {
                byte = buf.next_byte();
                if( ( 192 & byte ) != 128 )
                    /* illegal utf8 byte */
                    ;
                bytes[j] = byte;
            }
            return UTF8Char(bytes, i + 1);
        }
    }

    /* illegal utf8 byte */
}

void utf8_putc( UTF8Char c ) {
    for(int i = 0; i < c.num_bytes; i++)
        putchar(c.bytes[i]);
}

void cat( const char *fname ) {
    Buffer buf;
    UTF8Char c;

    buf.open(fname);
    while(buf.has_next())
        utf8_putc(utf8_getc(buf));

    buf.close();
}
