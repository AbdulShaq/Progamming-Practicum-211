/*Abdul Shaqildi
UIC, Spring 2021
CS 211, Nasim Mobasheri*/

/*Main.cpp is a program that will evaluate an infix expression by converting it to postfix and then evaluating. the program implements a self-made stack class, known as MyStack to help convert
* the expression to postfix, then to evaluate the program.
 */

//access to headerfiles
#include "MyStack.h"
#include "Token.h"
#include "TokenReader.h"


//function declerations
void printCommands()
{
    printf("The commands for this program are:\n\n");
    printf("q - to quit the program\n");
    printf("? - to list the accepted commands\n");
    printf("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

void processExpression(Token inputToken, TokenReader* tr);

void PopAndEval(MyStack& Val, MyStack& Oper);

int main(int argc, char* argv[])
{
    /***************************************************************/


    Token inputToken;
    TokenReader tr;

    printf("Starting Expression Evaluation Program\n\n");
    printf("Enter Expression:");


    inputToken = tr.getNextToken();

    while (inputToken.equalsType(QUIT) == false)
    {
        /* check first Token on Line of input */
        if (inputToken.equalsType(HELP))
        {
            printCommands();
            tr.clearToEoln();
        }
        else if (inputToken.equalsType(ERROR))
        {
            printf("Invalid Input - For a list of valid commands, type ?\n");
            tr.clearToEoln();
        }
        else if (inputToken.equalsType(EOLN))
        {
            printf("Blank Line - Do Nothing\n");
            /* blank line - do nothing */
        }
        else
        {
            processExpression(inputToken, &tr);
        }

        printf("\nEnter Expression: ");
        inputToken = tr.getNextToken();
    }

    printf("\nQuitting Program\n");
    return 0;
}

void processExpression(Token inputToken, TokenReader* tr)
{
    /**********************************************/
    /* Declare both stack pointers here      */
    MyStack ValStack;
    MyStack OperStack;
    /* Loop until the expression reaches its End */
    ValStack.Reset();
    OperStack.Reset();

    while (inputToken.equalsType(EOLN) == false)
    {
        /* The expression contain a VALUE */
        if (inputToken.equalsType(VALUE))
        {//when the token is a value pushed onto value stack 
            ValStack.Push(inputToken.getValue());
        }

        /* The expression contains an OPERATOR */
        else if (inputToken.equalsType(OPERATOR))
        {
            if (inputToken.getOperator() == '(')
            {
                OperStack.Push(inputToken.getOperator());
            }

            else if (inputToken.getOperator() == '+' || inputToken.getOperator() == '-')//checks if token is + or - operator
            {
                while (OperStack.isEmpty() == false && OperStack.Top() == '*' || OperStack.Top() == '/' || OperStack.Top() == '%' || OperStack.Top() == '+' || OperStack.Top() == '-')
                {
                    //call to PopAndEval function
                    PopAndEval(ValStack, OperStack);

                }

                OperStack.Push(inputToken.getOperator());
            }

            else if (inputToken.getOperator() == '*' || inputToken.getOperator() == '/' || inputToken.getOperator() == '%')//checks if token is *,/,% operator
            {
                while (OperStack.isEmpty() == false && OperStack.Top() == '*' || OperStack.Top() == '/' || OperStack.Top() == '%')
                {
                    //call to PopAndEval function
                    PopAndEval(ValStack, OperStack);

                }

                OperStack.Push(inputToken.getOperator());
            }

            else if (inputToken.getOperator() == ')') //checks if operator is ")"
            {
                while (!OperStack.isEmpty() && OperStack.Top() != '(')
                {
                    //call to PopAndEval function
                    PopAndEval(ValStack, OperStack);

                }

                if (OperStack.isEmpty())
                {
                    printf("error message 1\n");
                }
                else
                {
                    OperStack.Pop();
                }
            }
        }
        /* get next token from input */
        inputToken = tr->getNextToken();
    }

    /* The expression has reached its end */
    while (OperStack.isEmpty() == false)
    {
        //call to PopAndEval function
        PopAndEval(ValStack, OperStack);

    }

    if (ValStack.Top() != -999 && ValStack.getinUse() <= 1)
    {//if the value stack is not -999 or there is only onr value left print value
        printf("\nExpression result: %d\n", ValStack.Top());
    }
    else
    {
        printf("Invalid expression.");
    }

    ValStack.Pop();
    ValStack.Pop();

    if (ValStack.isEmpty() == false)
    {//if the value stack is not empty then print error
        printf("error message 2\n");
    }
    printf("\n");
}

void PopAndEval(MyStack& Val, MyStack& Oper)
{
    if (Val.getinUse() == 1)
    {//if there is only one value in the stack then exit
        return;
    }
    else
    {
        int op = Oper.Top();//get operator
        Oper.Pop();

        int v2 = Val.Top();//get top value 
        Val.Pop();//pop top value

        int v1 = Val.Top();//get next value
        Val.Pop();//pop value

        int v3;

        if (op == '+') {//evaluate expression when Operator is +
            v3 = v1 + v2;
        }
        else if (op == '-') {//evaluate expression when Operator is -
            v3 = v1 - v2;
        }
        else if (op == '*') {//evaluate expression when Operator is *
            v3 = v1 * v2;
        }
        else if (op == '/') {//evaluate expression when Operator is /
            v3 = v1 / v2;
        }
        else if (op == '%') {//evaluate expression when Operator is %
            v3 = v1 % v2;
        }
        else
        {//all else set v3 to -999
            v3 = -999;
        }
        //push the result value v3 to valuestack
        Val.Push(v3);
    }
}