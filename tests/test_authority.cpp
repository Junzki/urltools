// authority_t.c -- Tests for authority_t class.
//

#include <string>
#include "url.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

using std::string;
using stun::authority_t;


TEST_CASE( "Parse user_name & password", "[authority_t::parse]" )
{
    SECTION( "Parse user_name only" )
    {
        const string name_only = "user_name";

        authority_t info;
        info.parse(name_only);

        REQUIRE(name_only == info.user_name());
    }


    SECTION( "Parse user_name with password" )
    {
        const string user_name_with_password = "user_name:password";

        authority_t info;
        info.parse(user_name_with_password);

        REQUIRE("user_name" == info.user_name());
        REQUIRE("password" == info.password());
    }

    SECTION( "Parse user_name with delimiter and empty password" )
    {
        const string user_name_with_empty_password = "user_name:";

        authority_t info;
        info.parse(user_name_with_empty_password);

        REQUIRE("user_name" == info.user_name());
        REQUIRE(!info.password_set());
    }

    SECTION( "Parse password only" )
    {
        const string password_only = ":password";

        authority_t info;
        info.parse(password_only);

        REQUIRE(info.user_name().empty());
        REQUIRE("password" == info.password());
    }
}


TEST_CASE( "Format to string", "[authority_t::to_string]" )
{
    SECTION( "Format user_name only" )
    {
        const string user_name = "user_name_only";
        const auto info = authority_t(user_name);

        auto result = info.to_string();

        REQUIRE(user_name == result);
    }

    SECTION("Format password only")
    {
        const string password = "password";
        const auto info = authority_t("", password);

        auto result = info.to_string();

        REQUIRE((":" + password) == result);
    }

    SECTION("Format user_name with password")
    {
        const string user_name = "user_name";
        const string password = "password";
        const auto info = authority_t(user_name, password);

        auto result = info.to_string();

        REQUIRE((user_name + ":" + password) == result);
    }
}
