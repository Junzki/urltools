// urltools.cpp : Defines the entry point for the application.
//

#include <sstream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include "urltools.h"

using std::uint8_t;
using std::string;

const uint8_t block_size = 4;

inline bool
encode_required(char c) {
    if (-1 > c || 255 < c)
        return true;

    return ! (isalnum(c) || c == '-' || c == '_' || c == '.');
}

char
to_hex(char code) {
    static char alphabet[] = "0123456789abcdef";
    return alphabet[code & 0x0F];
}


string
stun::urlencode(const string& in)
{
    
    const char* body = in.c_str();
    size_t size = strlen(body);
    if (0 == size)
        return "";

    size_t target_size = 3 * size + 1;
    char* buf = (char*)malloc(target_size);
    memset(buf, '\0', target_size);

    char* ptr = buf;

    for (size_t i = 0; i < size; ++i) {
        char v = body[i];

        if (! encode_required(v)) {
            *(ptr++) = v;
            continue;
        }
        
        *(ptr++) = '%';
        *(ptr++) = to_hex(v >> 4);
        *(ptr++) = to_hex(v & 0x0F);
    }

    return string(buf);
}

