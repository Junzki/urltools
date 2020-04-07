// urltools.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#ifndef STUN_URLTOOLS_H_
#define STUN_URLTOOLS_H_

#include <iostream>

// TODO: Reference additional headers your program requires here.
namespace stun {
    using std::string;

    string urlencode(const string&);
    string urldecode(const string&);
}

#endif // !STUN_URLTOOLS_H_