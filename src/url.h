//
// Created by Andrija Juriša on 2020/4/9.
//

#ifndef STUN_URL_H_
#define STUN_URL_H_

#include <iostream>
#include <utility>

using std::string;

namespace stun {
    class user_info {
    public:
        user_info(string user, string password = "")
                : _user_name(std::move(user)), _password(std::move(password))
        {
            if (!password.empty())
                this->_password_set = false;
        }

        user_info parse(const string& i);

        inline string user_name() { return this->_user_name; }
        inline string password() { return this->_password; }

        string to_string();

    private:
        string _user_name;
        string _password;
        bool _password_set = false;
    };

    class url {
    public:
        url() = default;

        url parse(const string& i);
        string to_string();

        string scheme;
        user_info* user = nullptr;

        string opaque;
        string host;
        string path;
        string raw_path;
        string raw_query;
        string fragment;
    };
}


#endif // !STUN_URL_H_
