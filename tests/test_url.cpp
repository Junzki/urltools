// url_t.c -- Tests for class url_t.
//

#include <string>
#include <cstring>
#include "test_url.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"


TEST_CASE( "Parse scheme", "[stun::get_scheme]" )
{
    SECTION( "Parse scheme" )
    {
        const string url = "https://github.com";
        auto* input_array = const_cast<char*>(url.c_str());

        const string expect = "https";
        const auto* expect_rest = "github.com";

        const auto exact = get_scheme(&input_array);

        REQUIRE(expect == exact);
        REQUIRE(0 == strcmp(expect_rest, input_array));
    }
}

TEST_CASE( "Parse #frag", "[stun::get_frag]" )
{
    SECTION( "Parse frag" )
    {
        const string with_frag = "x#y";
        auto input_array = const_cast<char*>(with_frag.c_str());

        const auto expect_frag = "y";
        const auto expect_rest = "x";

        const auto exact = get_frag(&input_array);
        REQUIRE(expect_frag == exact);
        REQUIRE(0 == strcmp(expect_rest, input_array));
    }
}

TEST_CASE( "Parse ?query", "[stun::extract_tail]" )
{
    SECTION( "Parse query" )
    {
        const string with_query = "x?y=z";
        auto* input_array = const_cast<char*>(with_query.c_str());

        const auto* const expect_query = "y=z";
        const auto* const expect_rest = "x";

        const auto* const exact = extract_tail(&input_array, '?');
        REQUIRE(0 == strcmp(expect_query, exact));
        REQUIRE(0 == strcmp(expect_rest, input_array));
    }
}


TEST_CASE( "Parse authority", "[stun::get_authority]" )
{
    SECTION( "Parse authority" )
    {
        const string with_authority = "user@hostname";
        auto* input_array = const_cast<char*>(with_authority.c_str());

        const string user_name = "user";
        const auto* const host_name = "hostname";
        const auto* const authority = get_authority(&input_array);

        REQUIRE(nullptr != authority);
        REQUIRE(user_name == authority->user_name());

        REQUIRE(0 == strcmp(host_name, input_array));
    }
}


TEST_CASE( "Parse hostname with port", "[stun::get_hostname]" )
{
    SECTION( "Parse hostname" )
    {
        const string with_hostname = "github.com:9099/junzki/urltools";
        auto* input_array = const_cast<char*>(with_hostname.c_str());

        const string expect = "github.com:9099";

        const auto exact = get_hostname(&input_array);

        REQUIRE(expect == exact);
    }
}
