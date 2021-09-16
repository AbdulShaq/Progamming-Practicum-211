/*Abdul Shaqildi
UIC, Spring 2021
CS 211, Nasim Mobasheri*/

/*Main.c is a program to check if the user input expression is balanced with the proper (), {}, [], <>. if the expression is not 
 balanced the program will let the user know what is missing or expected. Also if "-d" is entered when running main.c then debugmode 
 will run and let the user see whats being pushed or popped and if the dynamic array in the stack will grow and how many values were copied.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//global variable decleration
#define TRUE 1
#define FALSE 0
int DebugMode;

//struct definition 
typedef struct CharStack 
{
    char* darr; //pointer to dynamic array
    int size; // size allocated
    int inUse; // counts how many characters are on the stack and indicator of top of stack

}CharSt;

//function decleration
void init(CharSt* s);

int is_empty(CharSt* s);

void push(CharSt* s, char C, int DebugMode);

void pop(CharSt* s, int DebugMode);

int top(CharSt* s);

void clear(CharSt* s);



int main(int argc, char** argv)
{
    DebugMode = FALSE;
    for (int i = 0; i < argc; i++)
    {//checks to see if debugmode is entered
        if(strcmp(argv[i],"-d")== 0)
        {
            DebugMode = TRUE;
        }
    }
    char input[301];
    
    int index;//keep track of the character index so the warning pointer knows how far to be spaced underneath
    int balance = FALSE;//keeps track of the balance checker so it knows whether to print balanced expression or check for error 3

    char need;     /* Variables to check and keep track of whats needed, expected and entered for comparing*/
    char expect;
    char entered;

    CharSt stack;

    init(&stack);

    /* set up an infinite loop */
    while (1)
    {
        /* get line of input from standard input */
        printf("\nEnter input to check or q to quit\n");
        fgets(input, 300, stdin);

        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0')
        {
            if (input[i] == '(' || input[i] == '{' || input[i] == '[' || input[i] == '<') 
            {//pushing character to stack
                push(&stack, input[i],DebugMode);
            }

            else if (input[i] == ')' || input[i] == '}' || input[i] == ']' || input[i] == '>')
            {//checking if a closing character is entered to make the needed character the corisponding open character
                entered = input[i];

                if (input[i] == ')')
                {
                    need = '(';
                    index = i;
                }
                else if (input[i] == '}')
                {
                    need = '{';
                    index = i;
                }
                else if (input[i] == ']')
                {
                    need = '[';
                    index = i;
                }
                else if (input[i] == '>')
                {
                    need = '<';
                    index = i;
                }

                if (top(&stack) == need)
                {//popping top of stack
                    pop(&stack, DebugMode);
                }
                else
                {
                   if(is_empty(&stack) == FALSE)
                   {
                       // checking for where error 1 is occuring and flagging it
                       if (top(&stack) == '(')
                       {
                           expect = ')';
                       }
                       else if (top(&stack) == '{')
                       {
                           expect = '}';
                       }
                       else if (top(&stack) == '[')
                       {
                           expect = ']';
                       }
                       else if (top(&stack) == '<')
                       {
                           expect = '>';
                       }
                       printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
                       printf("%s", input);
                       for (int j = 0; j < index; j++)
                       {
                           printf(" ");
                       }
                       printf("^ expecting %c\n", expect);
                       balance = TRUE;
                       break;
                       
                   }
                   else
                   { // checking for where error 2 is occuring and flagging it
                       char missing;
                       if (entered == ')')
                       {
                           missing = '(';
                       }
                       else if (entered == '}')
                       {
                           missing = '{';
                       }
                       else if (entered == ']')
                       {
                           missing = '[';
                       }
                       else if (entered == '>')
                       {
                           missing = '<';
                       }
                       printf("Unbalanced expression. Error 2: missing an opening symbol\n");
                       printf("%s", input);
                       for (int j = 0; j < index; j++)
                       {
                           printf(" ");
                       }
                       printf("^ missing %c\n", missing);
                       balance = TRUE;
                       break;
                   }
                }
            }
               
            i++;
        }
        input[i] = '\0';

        /* check if user enter q or Q to quit program */
        if ((strcmp(input, "q") == 0) || (strcmp(input, "Q") == 0))
            break;
       
        /* run the algorithm to determine is input is balanced */
        if(balance == FALSE)
        {
            if(is_empty(&stack)== TRUE)
            {//when expression is balanced 
                printf("%s\n", input);
                printf("Expression is balanced\n");
               
                continue;
            }
            else
            {
                // checking for where error 3 is occuring and flagging it
                char miss;
                if (top(&stack) == '(')
                {
                    miss = ')';
                }
                else if (top(&stack) == '{')
                {
                    miss = '}';
                }
                else if (top(&stack) == '[')
                {
                    miss = ']';
                }
                else if (top(&stack) == '<')
                {
                   miss = '>';
                }
                printf("Unbalanced expression. Error 3: missing a closing symbol\n");
                printf("%s\n", input);
                for(int j = 0; j < i; j++)
                {  
                      printf(" ");   
                }
                printf("^ missing %c\n", miss);
                
                
                
            }
        }
      //reset balance and clear stack
        balance = FALSE;
           clear(&stack);
           
    }
    //free the allocated space in stacks dynamic array
    free(stack.darr);

    printf("\nGoodbye\n");
    return 0;
}

//function definitions

void init(CharSt* s)
{
    //initialize the stacks array zise and inUse tracker
    s->size = 4;
    s->darr = (char*)malloc(sizeof(char) * s->size);
    s->inUse = 0;

}

int is_empty(CharSt* s)
{//checking if the stack is empty
    if (s->inUse == 0)
        return TRUE;
    else
        return FALSE;
}

void push(CharSt* s, char C, int DebugMode)
{   //checking if in debugging mode and then adding the next character to the stack and if stack is full increasing the size
    if(DebugMode == TRUE)
    {
     if (s->inUse == s->size) {
        char* tmp;
        tmp = s->darr;
        
        int oldSize = s->size;
        int copied;
        s->darr = (char*)malloc(sizeof(char) * s->size * 2);

        int k;
        for ( k = 0; k < s->inUse; k++)
        {
            s->darr[k] = tmp[k];
            
        }
        
        copied = s->inUse;
        free(tmp);
        s->size = s->size + 4;
        printf("Stack size increased from %d to %d, a total of %d values were copied \n", oldSize, s->size,copied);
     }

    s->darr[s->inUse] = C;
    s->inUse = s->inUse + 1;
    printf("Character %c was pushed into the stack \n", C);
    }
    else
    {
     if (s->inUse == s->size)
     {
        char* tmp;
        tmp = s->darr;

        s->darr = (char*)malloc(sizeof(char) * s->size * 2);


        for (int k = 0; k < s->inUse; k++)
        {
            s->darr[k] = tmp[k];
        }
        free(tmp);

        s->size = s->size + 4;
     }

    s->darr[s->inUse] = C;
    s->inUse = s->inUse + 1;
    }
    
}

void pop(CharSt* s, int DebugMode)
{//popping top element in stack
    if (DebugMode == TRUE) 
    {
        printf("Character %c was popped from the stack \n", s->darr[s->inUse - 1]);
        s->inUse = s->inUse - 1;
    }
    else
    {
        s->inUse = s->inUse - 1;
    }
}

int top(CharSt* s)
{//returns top element in the stack
    return (s->darr[s->inUse - 1]);
}

void clear(CharSt* s)
{//clears the entire stack
    while (s->inUse != 0)
    {
        s->inUse = s->inUse - 1;
    }
   
}
