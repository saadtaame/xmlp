#include <cstdio>

class Buffer {
    static const size_t BLOCK_SIZE = 4096;
    static const unsigned char END_OF_BUFFER = 0xff;
    
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
                last_byte_index = (int)fread(buffer + BLOCK_SIZE + 2, sizeof(unsigned char), BLOCK_SIZE, f);
                buffer[last_byte_index] = Buffer::END_OF_BUFFER;
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
    
    Buffer( void ) {
        buffer[BLOCK_SIZE] = Buffer::END_OF_BUFFER;
        buffer[BLOCK_SIZE + BLOCK_SIZE + 1] = Buffer::END_OF_BUFFER;
        beg = end = 0;
        f = NULL;
        is_open = false;
    }
    
    void open( const char *fname ) {
        if(is_open) {
            /* TODO: handle error */
        }
        
        f = fopen(fname, "rb");
        if(f != NULL) {
            int last_byte_index;
            last_byte_index = (int)fread(buffer, sizeof(unsigned char), BLOCK_SIZE, f);
            buffer[last_byte_index] = Buffer::END_OF_BUFFER;
            is_open = true;
            saw_EOF = false;
        }
        else {
            /* TODO: handle error */
        }
    }
    
    void close( void ) {
        if(is_open == false) {
            /* TODO: handle error */
        }
        
        if(f != NULL) {
            fclose(f);
            f = NULL;
            is_open = false;
        }
    }
    
    bool has_next( void ) {
        if(is_open && (saw_EOF == false))
            return true;
            
        return false;
    }
    
    unsigned char next_byte( void ) {
        unsigned char byte = buffer[end];
        step();
        
        return byte;
    }
};

/* test */
int main( void ) {
    Buffer io;
    io.open("buffer.cpp");
    while(io.has_next()) {
        putchar(io.next_byte());
    }
    io.close();
    return 0;
}
