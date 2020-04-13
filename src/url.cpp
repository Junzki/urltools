// url.cpp -- Implements class url_t.
//

#include "url.h"
#include <cstdlib>
#include <cstring>

using stun::url_t;

const char scheme_separator = ':';
const char frag_separator = '#';

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

string
stun::get_frag(char** i)
{
    const auto pfrag = strchr(*i, frag_separator);
    if (nullptr == pfrag) return "";

    const auto size = strlen(pfrag + 1);

    const auto frag = new char[size + 1];
    memset(frag, '\0', size + 1);

    strcpy(frag, pfrag + 1);
    memset(pfrag, '\0', size);  // erase #frag part.

    auto ret = string(frag);
    delete[](frag);  // Free allocated memory explicitly.

    return ret;
}


url_t url_t::parse(const char* i)
{
    const auto size = strlen(i);
    if (0 == size) throw("empty url");

    auto rawurl = new char[size + 1];
    memset(rawurl, '\0', size + 1);

    // Copy explicitly.
    strcpy(rawurl, i);

    url_t url;
    url.fragment = get_frag(&rawurl);


    delete[](rawurl);
    return url;
}

