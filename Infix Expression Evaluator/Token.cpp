#include "Token.h"

Token::Token()
{
    type = ERROR;
    op = '$';
    val = -999;
}

// Initialize to a specific TokenType
Token::Token(TokenType t)
{
    type = t;
    op = '$';
    val = -999;
}

// Set to a specific TokenType
void Token::setToType(TokenType t)
{
    type = t;
    op = '$';
    val = -999;
}

// Set to a OPERATOR TokenType with specific operator value
void Token::setToOperator(char c)
{
    type = OPERATOR;
    op = c;
    val = -999;
}

// Set to a VALUE TokenType with a specific numeric value
void Token::setToValue(int v)
{
    type = VALUE;
    op = '$';
    val = v;
}

// return true if the Current Token is of the given TokenType
bool Token::equalsType(TokenType t)
{
    if (type == t)
        return true;
    else
        return false;
}

// return true if the Current Token is of the OPERATOR TokenType
//     and contains the given operator character
bool Token::equalsOperator(char c)
{
    if (type == OPERATOR && op == c)
        return true;
    else
        return false;
}

// Return the Operator for the current Token
//   verify the current Token is of the OPERATOR TokenType
char Token::getOperator()
{
    if (type == OPERATOR)
        return op;
    else
        return '$';   // using $ to indicate an error value
}

// Return the Value for the current Token
//   verify the current token is of the value TokenType
int Token::getValue()
{
    if (type == VALUE)
        return val;
    else
        return -999;  // using -999 to indicate an error value
}