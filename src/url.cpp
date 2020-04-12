// url.cpp -- Implements class url_t.
//

#include "url.h"
#include <cstdlib>
#include <cstring>


const char scheme_separator = ':';

string
stun::get_scheme(char** origin)
{
    const size_t size = strlen(*origin);
    size_t i = 0;
    if (0 == size) return "";

    for (i = 0; i < size; ++i)
    {
        const auto c = (*origin)[i];
        if (isalpha(c)) continue;  // do noting

        else if (scheme_separator == c)
        {
            if (0 == i) return "";  // no protocol (scheme) specified.

            break;
        }

        else if (isdigit(c) || '+' == c || '-' == c || '.' == c)
        {
            if (0 == i) return "";
        }

        else return "";
    }

    const auto target_size = i + 1;
    const auto ret = static_cast<char*>(malloc(target_size));
    if (nullptr == ret)
        throw("cannot allocate memory");

    memset(ret, '\0', target_size);

    memcpy(ret, *origin, target_size - 1);
    auto scheme = string(ret);

    free(ret);

    (*origin) += i;  // move pointer.
    return scheme;
}
