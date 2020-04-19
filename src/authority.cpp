// user_info.cpp -- Implements user_info class.
// user_info -> user_name[:password]
//

#include <sstream>
#include "url.h"
#include "quote.h"

using stun::user_info;


user_info
user_info::parse(const string& in) {
    if (0 == in.length())
        return user_info();

    const auto found = in.find(':');

    // No `password` specified.
    if (found == string::npos)
        return user_info(unquote_url(in));

    const auto name = unquote_url(in.substr(0, found));
    const auto password = unquote_url(in.substr(found + 1));

    return user_info(name, password);
}


string
user_info::to_string() const
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
