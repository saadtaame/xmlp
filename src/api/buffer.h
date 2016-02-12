#ifndef XMLP_API_BUFFER_H_
#define XMLP_API_BUFFER_H_

#include <cstdio>

class Buffer {
    static const size_t BLOCK_SIZE = 4096;
    static const unsigned char END_OF_BUFFER = 0xFF;

    unsigned char buffer[ BLOCK_SIZE + BLOCK_SIZE + 2 ];
    int beg, end;
    FILE *f;

    bool is_open;
    bool saw_EOF;

    void step( void ) {
        end += 1;
        if(buffer[end] == Buffer::END_OF_BUFFER) {
            if(end == BLOCK_SIZE) {
                int last_byte_index;
                last_byte_index = (int)fread(buffer + BLOCK_SIZE + 1, sizeof(unsigned char), BLOCK_SIZE, f);
                buffer[last_byte_index + BLOCK_SIZE + 1] = Buffer::END_OF_BUFFER;
                end += 1;
            }
            else if(end == BLOCK_SIZE + BLOCK_SIZE + 1) {
                int last_byte_index;
                last_byte_index = (int)fread(buffer, sizeof(unsigned char), BLOCK_SIZE, f);
                buffer[last_byte_index] = Buffer::END_OF_BUFFER;
                end = 0;
            }
            else {
                saw_EOF = true;
            }
        }
    }

    public:

    Buffer( void );
    ~Buffer( void ) {}

    void open( const char * );
    void close( void );
    bool has_next( void );
    unsigned char next_byte( void );
};

#endif // XMLP_API_BUFFER_H_
