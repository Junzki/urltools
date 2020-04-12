// user_info.cpp -- Implements user_info class.
// user_info -> user_name[:password]
//

#include <sstream>
#include "url.h"
#include "urlcode.h"

using stun::user_info;


user_info
user_info::parse(const string& in) {
    if (0 == in.length())
        return user_info();

    const auto found = in.find(':');

    // No `password` specified.
    if (found == string::npos)
        return user_info(urldecode(in));

    const auto name = urldecode(in.substr(0, found));
    const auto password = urldecode(in.substr(found + 1));

    return user_info(name, password);
}


string
user_info::to_string() const
{
    std::stringstream ss;
    const auto user = urlencode(this->user_name_);
    ss << user;

    if (! this->password_set())
    {
        return ss.str();
    }

    const auto password = urlencode(this->password_);
    ss << ":" << password;

    return ss.str();
}
