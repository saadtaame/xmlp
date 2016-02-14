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

    inline void step( void );

    public:

    Buffer( void );
    ~Buffer( void ) {}

    void open( const char * );
    void close( void );
    bool has_next( void );
    unsigned char next_byte( void );
};

#endif // XMLP_API_BUFFER_H_
