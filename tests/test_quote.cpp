// test_escape.c -- Tests for quote_url / unquote_url
//

#include <string>
#include "quote.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"


TEST_CASE( "URL Encode", "[stun::quote_url]" ) {
    const std::string case1 = u8"a测d试中文";
    const std::string expect1 = "a%e6%b5%8bd%e8%af%95%e4%b8%ad%e6%96%87";

    auto out = stun::quote_url(case1);
    REQUIRE( expect1 == out );
}

TEST_CASE( "URL Decode", "[stun::unquote_url]" ) {
    const std::string case1 = "a%e6%b5%8bd%e8%af%95%e4%b8%ad%e6%96%87";
    const std::string expect1 = u8"a测d试中文";

    auto out = stun::unquote_url(case1);
    REQUIRE( expect1 == out );
}
