#pragma once

// Enumarated Type specifying all of the Tokens
enum TokenType {
    ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

class Token
{
private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

public:

    // Default to initialize to the ERROR TokenType
    Token();

    // Initialize to a specific TokenType
    Token(TokenType t);

    // Set to a specific TokenType
    void setToType(TokenType t);

    // Set to a OPERATOR TokenType with specific operator value
    void setToOperator(char c);

    // Set to a VALUE TokenType with a specific numeric value
    void setToValue(int v);

    // return true if the Current Token is of the given TokenType
    bool equalsType(TokenType t);

    // return true if the Current Token is of the OPERATOR TokenType
    //     and contains the given operator character
    bool equalsOperator(char c);

    // Return the Operator for the current Token
    //   verify the current Token is of the OPERATOR TokenType
    char getOperator();

    // Return the Value for the current Token
    //   verify the current token is of the value TokenType
    int getValue();
};
