// url_test.h -- Defines some private functions in url.h
//
#pragma once


#ifndef STUN_URL_TEST_H_
#define STUN_URL_TEST_H_

#include <iostream>
#include "url.h"

using std::string;
using stun::url_t;
using stun::authority_t;

char* extract_tail(char**, const char);
string get_scheme(char**);
string get_frag(char**);

authority_t* get_authority(char**);


#endif  // !STUN_URL_TEST_H_
