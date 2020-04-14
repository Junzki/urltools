// url_test.h -- Defines some private functions in url.h
//
#pragma once


#ifndef STUN_URL_TEST_H_
#define STUN_URL_TEST_H_

#include <iostream>

using std::string;

char* extract_tail(char**, const char);
string get_scheme(char**);
string get_frag(char**);


#endif  // !STUN_URL_TEST_H_
