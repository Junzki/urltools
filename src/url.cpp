// url.cpp -- Implements class url_t.
//

#include <cstdlib>
#include <cstring>
#include "url.h"

using stun::url_t;
using stun::authority_t;


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

        else if (url_t::scheme_separator == c)
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
    auto* const ret = static_cast<char*>(malloc(target_size));
    if (nullptr == ret)
        throw("cannot allocate memory");

    memset(ret, '\0', target_size);

    memcpy(ret, *origin, target_size - 1);
    auto scheme = string(ret);

    free(ret);

    *origin += i;  // move pointer.
    if (3 <= strlen(*origin))
        *origin += 3;   // Remove leading "://"

    return scheme;
}


char*
extract_tail(char** i, const char sep)
{
    auto* const pch = strchr(*i, sep);
    if (nullptr == pch) return pch;

    const auto size = strlen(pch + 1);

    auto* const target = new char[size + 1];
    memset(target, '\0', size + 1);

    strcpy(target, pch + 1);
    memset(pch, '\0', size);  // erase #frag part.

    return target;
}



string
get_frag(char** i)
{
    auto* const separated = extract_tail(i, url_t::frag_separator);
    if (nullptr == separated) return "";

    auto ret = string(separated);
    delete[](separated);

    return ret;
}


authority_t*
get_authority(char** i)
{
    auto* pch = strchr(*i, '@');
    if (nullptr == pch) return nullptr;

    const auto size = pch - *i;
    auto* separated = new char[size + 1];
    if (nullptr == separated)
        throw("cannot allocate memory");

    memset(separated, '\0', size + 1);
    memcpy(separated, *i, size);

    auto* info = new authority_t();
    if (nullptr == info)
        throw("cannot allocate memory");

    info->parse(separated);
    delete[](separated);

    *i = pch + 1;

    return info;
}


string
get_hostname(char** i)
{
    auto* pch = strchr(*i, '/');
    if (nullptr == pch)
        return string(*i);

    if (*i == pch)
        return "";

    const auto size = pch - *i;

    auto* separated = new char[size + 1];
    if (nullptr == separated)
        throw("cannot allocate memory");

    memset(separated, '\0', size + 1);
    memcpy(separated, *i, size);

    *i = pch + 1;

    return string(separated);
}


url_t url_t::parse(const char* i)
{
    const auto size = strlen(i);
    if (0 == size) throw("empty url");

    auto* rawurl = new char[size + 1];
    memset(rawurl, '\0', size + 1);

    // Copy explicitly.
    strcpy(rawurl, i);

    url_t url;
    url.fragment = get_frag(&rawurl);
    url.raw_query = extract_tail(&rawurl, query_separator);
    url.user = get_authority(&rawurl);


    delete[](rawurl);
    return url;
}


string
url_t::to_string() const
{
    return this->raw_path;
}
