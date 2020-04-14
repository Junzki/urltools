// url.h -- Defines the url_t type.
//

#ifndef STUN_URL_H_
#define STUN_URL_H_

#include <iostream>
#include <utility>

using std::string;

namespace stun {

    template<typename T>
    T parse(const string& in)
    {
        return T::parse(in);
    };

    class user_info {
    public:
        user_info(string user, string password = "")
                : user_name_(std::move(user)), password_(std::move(password)) {}

        user_info() = default;

        static user_info parse(const string&);

        inline string user_name() const { return this->user_name_; }
        inline string password() const { return this->password_; }
        inline bool password_set() const { return ! this->password_.empty(); }

        string to_string() const;

    private:
        string user_name_;
        string password_;
    };

    // A URL represents a parsed URL (technically, a URI reference).
    //
    // The general form represented is:
    //
    //	[scheme:][//[userinfo@]host][/]path[?query][#fragment]
    //
    // URLs that do not start with a slash after the scheme are interpreted as:
    //
    //	scheme:opaque[?query][#fragment]
    //
    class url_t {
    public:
        url_t() = default;

        static url_t parse(const char*);
        static url_t parse(const string& i) { return parse(i.c_str()); };
        
        string to_string() const;

        string scheme;
        user_info* user = nullptr;

        string opaque;
        string host;
        string path;
        string raw_path;
        char*  raw_query = nullptr;
        string fragment;
    };


}


#endif // !STUN_URL_H_
