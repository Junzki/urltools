// user_info.c -- Tests for user_info class.
//

#include <string>
#include "url.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

using std::string;
using stun::user_info;


TEST_CASE( "Parse user_name & password", "[user_info::parse]" )
{
    SECTION( "Parse user_name only" )
    {
        const auto name_only = "user_name";
        auto info = user_info::parse(name_only);

        REQUIRE(name_only == info.user_name());

        auto info2 = stun::parse<user_info>(name_only);
        REQUIRE(name_only == info2.user_name());
    }


    SECTION("Parse user_name with password")
    {
        const auto user_name_with_password = "user_name:password";
        auto info = user_info::parse(user_name_with_password);

        REQUIRE("user_name" == info.user_name());
        REQUIRE("password" == info.password());
    }

    SECTION("Parse user_name with delimiter and empty password")
    {
        const auto user_name_with_empty_password = "user_name:";
        auto info = user_info::parse(user_name_with_empty_password);

        REQUIRE("user_name" == info.user_name());
        REQUIRE(!info.password_set());
    }

    SECTION("Parse password only")
    {
        const auto password_only = ":password";
        auto info = user_info::parse(password_only);

        REQUIRE(info.user_name().empty());
        REQUIRE("password" == info.password());
    }
}
