// urlcode.cpp : Defines the entry point for the application.
//

#include <cstring>
#include <cstdlib>
#include "urlcode.h"

using std::string;

inline bool
encode_required(const char c) {
    if (-1 > c)
        return true;

    return ! (isalnum(c) || c == '-' || c == '_' || c == '.');
}

char
to_hex(const char code) {
    static char alphabet[] = "0123456789abcdef";
    return alphabet[code & 0x0F];
}

char
from_hex(const char h) {
    if (isdigit(h)) {
        return h - '0';
    }

    return tolower(h) - 'a' + 0x0A;
}


string
stun::urlencode(const string& in) {
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


string
stun::urldecode(const string& in) {
    const char* body = in.c_str();
    size_t size = strlen(body);

    if (0 == size)
        return "";

    char* buf = (char*)malloc(size + 1);
    if (nullptr == buf)
        throw("cannot allocate memory");

    memset(buf, '\0', size + 1);
    char* ptr = buf;

    int i = 0;
    while (i < size) {
        char v = body[i++];
        if ('%' != v) {
            *(ptr++) = v;
            continue;
        }

        char h = from_hex(body[i++]);
        char b = from_hex(body[i++]);

        *(ptr++) = (h << 4) + b;
    }

    return string(buf);
}
