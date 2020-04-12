// url_t.c -- Tests for class url_t.
//

#include <string>
#include "url.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"


TEST_CASE( "Parse scheme", "[stun::get_scheme]" ) {
    SECTION( "Parse scheme" )
    {
        const string url = "https://github.com";
        auto input_array = const_cast<char*>(url.c_str());

        const auto expect = "https";

        const auto exact = stun::get_scheme(&input_array);

        REQUIRE(expect == exact);
    }
}
