#include "TokenReader.h"

// initialize the TokenReader class to read from Standard Input
TokenReader::TokenReader()
{
    // set to read from Standard Input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
}

// Force the next getNextToken to read in a line of input
void TokenReader::clearToEoln()
{
    needline = true;
}

// Return the next Token from the input line
Token TokenReader::getNextToken()
{
    char* endCheck;

    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

    // get a new line of input from user
    if (needline)
    {
        endCheck = fgets(inputline, 300, stdin);

        if (endCheck == NULL)
        {
            printf("Error in reading");
            Token t(EOFILE);
            return t;
        }

        for (int i = 0; i < strlen(inputline); i++)
            if ('\n' == inputline[i])
                inputline[i] = ' ';
        strcat(inputline, " ");    // add a space at end to help deal with digit calculation
        needline = false;
        pos = 0;
    }

    // skip over any white space characters in the beginning of the input
    while (pos < strlen(inputline) && isspace(inputline[pos]))
    {
        pos++;
    }

    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
        needline = true;
        Token t(EOLN);
        return t;
    }

    // Get the next character from the input line
    char ch = inputline[pos]; pos++;

    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ('q' == ch || 'Q' == ch)
    {
        return Token(QUIT);
    }

    // check if "?" was entered ==> HELP Token
    if ('?' == ch)
    {
        return Token(HELP);
    }

    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if (('+' == ch) || ('-' == ch) || ('*' == ch) ||
        ('/' == ch) || ('%' == ch) || ('(' == ch) || (')' == ch))
    {
        Token t;
        t.setToOperator(ch);
        return t;
    }

    // check for a number  ==> VALUE Token
    if (isdigit(ch))
    {
        int number = int(ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
        ch = inputline[pos]; pos++;
        while (isdigit(ch))
        {
            number = number * 10 + int(ch) - int('0');
            ch = inputline[pos]; pos++;
        }
        pos--; // since number calcuation check one character after the last digit
        Token t;
        t.setToValue(number);
        return t;
    }

    // Input in not valid if code get to this part ==> ERROR Token
    return Token(ERROR);
}