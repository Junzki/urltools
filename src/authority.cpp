// authority_t.cpp -- Implements authority_t class.
// authority_t -> user_name[:password]
//

#include <sstream>
#include "url.h"
#include "quote.h"

using stun::authority_t;


//authority_t
//authority_t::parse(const string& in)
//{
//    if (0 == in.length())
//        return authority_t();
//
//    const auto found = in.find(':');
//
//    // No `password` specified.
//    if (found == string::npos)
//        return authority_t(unquote_url(in));
//
//    const auto name = unquote_url(in.substr(0, found));
//    const auto password = unquote_url(in.substr(found + 1));
//
//    return authority_t(name, password);
//}


void
authority_t::parse(const string& in)
{
    if (0 == in.length()) return;

    const auto found = in.find(':');
    // No `password` specified.
    if (found == string::npos)
    {
        this->user_name_ = unquote_url(in);
        return;
    }

    this->user_name_ = unquote_url(in.substr(0, found));
    this->password_ = unquote_url(in.substr(found + 1));
}

void
authority_t::parse(const char* in)
{
    if (nullptr == in) return;

    this->parse(string(in));
}




string
authority_t::to_string() const
{
    std::stringstream ss;
    const auto user = quote_url(this->user_name_);
    ss << user;

    if (! this->password_set())
    {
        return ss.str();
    }

    const auto password = quote_url(this->password_);
    ss << ":" << password;

    return ss.str();
}
