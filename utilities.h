#ifndef UTILITIES_H
#define UTILITIES_H

#include <istream>
#include <iostream>

#define MSG_NO_DATA "NO_DATA"
#define MSG_BAD_QUERY "BAD_QUERY"
#define MSG_UNKNOWN_ID "UNKNOWN ID"

#define INFINITE 9000000
#define MINUS_INFINITE -9000000

void _split(const string& s, const char c, Array<string>& v);
void _right_trim(string &);
bool _all_blanks_and_tabs(const string &);

#endif