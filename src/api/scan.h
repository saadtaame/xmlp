#ifndef XMLP_API_SCAN_H_
#define XMLP_API_SCAN_H_

#include "buffer.h"

class Scanner {

    friend class Buffer;

    public:

    Scanner( void );
    ~Scanner( void ) {}
};

#endif // XMLP_API_SCAN_H_
