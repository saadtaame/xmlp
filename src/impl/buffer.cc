#include "../api/buffer.h"

Buffer::Buffer( void ) {
    buffer[BLOCK_SIZE] = Buffer::END_OF_BUFFER;
    buffer[BLOCK_SIZE + BLOCK_SIZE + 1] = Buffer::END_OF_BUFFER;
    beg = end = 0;
    f = NULL;
    is_open = false;
}

void Buffer::open( const char *fname ) {
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

void Buffer::close( void ) {
    if(is_open == false) {
        /* TODO: handle error */
    }

    if(f != NULL) {
        fclose(f);
        f = NULL;
        is_open = false;
    }
}

bool Buffer::has_next( void ) {
    if(is_open && (saw_EOF == false))
        return true;

    return false;
}

unsigned char Buffer::next_byte( void ) {
    unsigned char byte = buffer[end];
    step();

    return byte;
}
