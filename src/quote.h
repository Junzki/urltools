// escape.h --
//

#pragma once

#ifndef STUN_ESCAPE_H_
#define STUN_ESCAPE_H_

#include <iostream>

// TODO: Reference additional headers your program requires here.
namespace stun {
    using std::string;

    string quote_url(const string&);
    string unquote_url(const string&);
}

#endif // !STUN_ESCAPE_H_
