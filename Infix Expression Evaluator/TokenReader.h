#pragma once
#include <cstdio>
#include <cstring>
#include <cctype>
#include "Token.h"
class TokenReader
{
private:
    char inputline[300];  // this assumes that all input lines are 300 characters or less in length
    bool needline;
    int pos;


public:

    // initialize the TokenReader class to read from Standard Input
    TokenReader();

    // Force the next getNextToken to read in a line of input
    void clearToEoln();

    // Return the next Token from the input line
    Token getNextToken();

};