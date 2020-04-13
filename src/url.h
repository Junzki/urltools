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

    class url_t {
    public:
        url_t() = default;

        url_t parse(const string& i);
        string to_string() const;

        string scheme;
        user_info* user = nullptr;

        string opaque;
        string host;
        string path;
        string raw_path;
        string raw_query;
        string fragment;
    };

    string get_scheme(char**);
}


#endif // !STUN_URL_H_
