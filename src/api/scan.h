#ifndef XMLP_API_SCAN_H_
#define XMLP_API_SCAN_H_

#include "buffer.h"
// TODO: list all tokens
enum TokenType {
    TOKEN_NONE = 0,
    
    /* number of tokens */
    NUM_TOKENS
};

struct Token {
    TokenType type;
    unsigned char *bytes;
    int row, col; /* inside file */  
};

class Scanner {

    friend class Buffer;

    public:
    
    Scanner( void );
    ~Scanner( void ) {}
    
    bool is_xml_char(UTF8Char);
    bool is_xml_letter(UTF8Char);
    bool is_xml_digit(UTF8Char);
    // TODO : finish list of one letter chars
    
};

#endif // XMLP_API_SCAN_H_
