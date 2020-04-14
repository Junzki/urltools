// url.cpp -- Implements class url_t.
//

#include "url.h"
#include <cstdlib>
#include <cstring>

using stun::url_t;

const char scheme_separator = ':';
const char frag_separator = '#';
const char query_separator = '?';

string
get_scheme(char** origin)
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


char*
extract_tail(char** i, const char sep)
{
    const auto pch = strchr(*i, sep);
    if (nullptr == pch) return pch;

    const auto size = strlen(pch + 1);

    const auto target = new char[size + 1];
    memset(target, '\0', size + 1);

    strcpy(target, pch + 1);
    memset(pch, '\0', size);  // erase #frag part.

    return target;
}

string
get_frag(char** i)
{
    const auto separated = extract_tail(i, frag_separator);
    if (nullptr == separated) return "";

    auto ret = string(separated);
    delete[](separated);

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
    url.raw_query = extract_tail(&rawurl, query_separator);


    delete[](rawurl);
    return url;
}

