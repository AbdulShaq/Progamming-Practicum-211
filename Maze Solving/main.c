/*Abdul Shaqildi
UIC, Spring 2021
CS 211, Nasim Mobasheri*/

/*Main.c is a program to solve a maze from a given file where the first 3 lines are: maze size, starting coordinate point, and coordinate ending point. 
every line in the file after 3 (if there are more than 3) are coordinates followed by either 'c'(indicating a coin) or 'b'(indicating a block). then the
program builds the maze and tries to find a way out(if any) and let the user know how many coins were collected and the path from start to end followed.
Also if "-d" is entered when running main.c then debugmode will run and let the user see whats being pushed or popped from the stack.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This program will read the first 3 lines of input
   and prints a static 2D maze*/

   //global variable decleration
//True and False values
#define TRUE 1
#define FALSE 0
//values to mark visited and unvisted points on maze
#define VISITED 1
#define UNVISITED 0
//debugmode varbiable to let each function know if debugmode is on
int DebugMode;

typedef struct mazeStruct
{// struct for maze and dynamic arrays
    char** darr;
    int** visited;
    int xsize, ysize;
    int xstart, ystart;
    int xend, yend;
} maze;

typedef struct LinkedPath
{// struct for linked list to keep track of path followed
    int xcorr;
    int ycorr;
    struct LinkedPath* next;
}Path;

//function decleration
void init_Maze(maze* s);

int is_empty(Path* hd);

void push(Path** hd, int a,int b);

void pop(Path** hd);

Path* top(Path* hd);

void clear(Path* hd);

void showRR(Path* hd);

int main(int argc, char** argv)
{
    //struct declerations
    maze m1;
    Path* p1 = NULL;
    

    int xpos=0, ypos=0;
    int i, j;
    int a, b, coins = 0;
    char c;
    FILE* src;

    /* verify the proper number of command line arguments were given */
    if (argc > 3) {
        printf("Too many input files.\n");
        exit(-1);
    }

    //check to see if debugmode is active
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0)
        {
            DebugMode = TRUE;
        }
        else
        {
            DebugMode = FALSE;
            argv[1] = argv[i];
        }
        
    }

    /* Try to open the input file. */
    if ((src = fopen(argv[1], "r")) == NULL)
    {
        printf("Can't open input file: %s", argv[1]);
        exit(-1);
    }
    
    /* read in the size, starting and ending positions in the maze */
    if ((fscanf(src, "%d %d", &m1.xsize, &m1.ysize)) == EOF)  //check to see if end of file
    {
        printf( "Invalid data file.\n");
        exit(-1);
    }
    if ((fscanf(src, "%d %d", &m1.xstart, &m1.ystart)) == EOF)//check to see if end of file
    {
        printf( "Invalid data file.\n");
        exit(-1);
    }
    if ((fscanf(src, "%d %d", &m1.xend, &m1.yend)) == EOF)//check to see if end of file
    {
        printf("Invalid data file.\n");
        exit(-1);
    }

    if (m1.xsize <= 0 || m1.ysize <= 0) 
    {//checks if maze size is invaild and exits if it is
        printf( "Maze sizes must be greater than 0.\n");
        exit(-1);
    }
    printf("size: %d, %d\n", m1.xsize, m1.ysize);
    

    if (m1.xstart < 1 || m1.xsize < m1.xstart || m1.ystart < 1 || m1.ysize < m1.ystart)
    {//checks if start position of maze is outside of maze and exits if it is
        printf("Start/End position outside of maze range.\n");
        exit(-1);
    }
    printf("start: %d, %d\n", m1.xstart, m1.ystart);
    
    
    if (m1.xend < 1 || m1.xsize < m1.xend || m1.yend < 1 || m1.ysize < m1.yend)
    {//checks if start position of maze is outside of maze and exits if it is
        printf("Start/End position outside of maze range.\n");
        exit(-1);
    }
    printf("end: %d, %d\n", m1.xend, m1.yend);
   
    init_Maze(&m1);//initialize maze struct
   
    /* initialize the maze to empty */
    for (i = 0; i < m1.xsize + 2; i++)
    {
        for (j = 0; j < m1.ysize + 2; j++)
        {

            m1.darr[i][j] = '.';
            m1.visited[i][j] = UNVISITED; //mark all spots unvisited
    }
    }
    /* mark the borders of the maze with *'s */
    for (i = 0; i < m1.xsize + 2; i++)
    {//mark all border spots as visited so they cannot be accessed
        m1.darr[i][0] = '*';
        m1.visited[i][0] = VISITED;
        m1.darr[i][m1.ysize + 1] = '*';
        m1.visited[i][m1.ysize + 1] = VISITED;
    }
    for (i = 0; i < m1.ysize + 2; i++)
    {//mark all blocks as visited so they cannot be accessed
        m1.darr[0][i] = '*';
        m1.visited[0][i] = VISITED;
        m1.darr[m1.xsize + 1][i] = '*';
        m1.visited[m1.xsize + 1][i] = VISITED;
    }

    /* mark the starting and ending positions in the maze */
    m1.darr[m1.xstart][m1.ystart] = 's';
    m1.darr[m1.xend][m1.yend] = 'e';

    //read through the rest of file until the end
     while (fscanf(src, "%d %d %c", &a, &b, &c) != EOF)
     {
         if(a < 1 || m1.xsize < a || b < 1 || m1.ysize< b)
         {//if coordinates given outside of maze message will print and ignore points
             printf("Invalid coordinates: outside of maze range.\n");
         }
         else 
         {
             if (c == 'c')
             {//if the character is 'c' that spot will be marked as 'C' on maze for coin as long as it is not on the start or end positions
                 if (a == m1.xstart && b == m1.ystart || a == m1.xend && b == m1.yend)
                 {
                     printf("Invalid coordinates: attempting to block start/end position.\n");

                 }
                 else
                 {
                     m1.darr[a][b] = 'C';
                 }

             }
             else if (c == 'b')
             {//if the character is 'b' that spot will be marked as '*' on maze for block as long as it is not on the start or end positions
                 if (a == m1.xstart && b == m1.ystart || a == m1.xend && b == m1.yend)
                 {
                     printf("Invalid coordinates: attempting to block start/end position.\n");
                 }
                 else
                 {
                     m1.darr[a][b] = '*';
                     m1.visited[a][b] = VISITED;
                 }

             }
             else
             {// if the character given is not c or b then it is ignored and message is printed
                 printf("Invalid type: type is not recognized.\n");
             }
         }
        
     }

           /*Close the file*/
    fclose(src);
   
    /* print out the initial maze */
    for (i = 0; i < m1.xsize + 2; i++)
    {
        for (j = 0; j < m1.ysize + 2; j++)
            printf("%c", m1.darr[i][j]);
        printf("\n");
    }

    xpos = m1.xstart;//initalize the x postion as the x starting
    ypos = m1.ystart;//initalize the y postion as the y starting
    push(&p1, xpos, ypos);//push starting points to stack
    m1.visited[m1.xstart][m1.ystart] = VISITED;//mark starting position as visted
  
    while (is_empty(p1) !=TRUE)//find path while stack is not empty
    {
        Path* tophd = top(p1);//get top of stack
        if (tophd->xcorr == m1.xend && tophd->ycorr == m1.yend)
        {//if top of stack is the end coordinates exit loop
            break;
        }
        if (m1.visited[xpos + 1][ypos] == UNVISITED) //check down nieghbor
        {
            xpos = xpos + 1;//update x position
            push(&p1, xpos, ypos);//push positon to stack
            if (m1.darr[xpos][ypos] == 'C')//check for coins
            {
                coins++;
            }
            m1.visited[xpos][ypos] = VISITED;//mark as visited

        }
        else if (m1.visited[xpos][ypos+1] == UNVISITED)//check right nieghbor
        {
            ypos = ypos + 1;//update y position
            push(&p1, xpos, ypos);//push positon to stack
            if (m1.darr[xpos][ypos] == 'C')//check for coins
            {
                coins++;
            }
            m1.visited[xpos][ypos] = VISITED;//mark as visited
           
        }
        else if (m1.visited[xpos-1][ypos] == UNVISITED)//check up nieghbor
        {
            xpos = xpos - 1;//update x position
            push(&p1, xpos, ypos);//push positon to stack
            if (m1.darr[xpos][ypos] == 'C')//check for coins
            {
                coins++;
            }
            m1.visited[xpos][ypos] = VISITED;//mark as visited
           
        }
        else if (m1.visited[xpos][ypos - 1] == UNVISITED)//check left nieghbor
        {
            ypos = ypos - 1;//update y position
            push(&p1, xpos, ypos);//push positon to stack
            if (m1.darr[xpos][ypos] == 'C')//check for coins
            {
                coins++;
            }
            m1.visited[xpos][ypos] = VISITED;//mark as visited
            
        }
        else
        {
            pop(&p1);//move back if no where to go
            if (is_empty(p1)) //check if empty and then continue if it is
            {
               continue;
            }
            xpos = p1->xcorr;//set the recent x position as the current
            ypos = p1->ycorr;//set the recent y position as the current
            
        }
    }

    if(is_empty(p1) == TRUE)
    {//if no solution to maze
        printf("This maze has no solution.\n");
    }
    else
    {// if there is a solution to the maze
        printf("\n");
        printf("The maze has a solution.\n");
        printf("The amount of coins collected: %d\n",coins);//print coins collected
        printf("The path from start to end: \n");
        showRR(p1);  //print path
    }
    clear(p1);//clear entire stack
   
    
    for (i = 0; i < m1.xsize + 2; i++) //free the 2d maze array
    {
        free(m1.darr[i]);
    }
    free(m1.darr);

    for (i = 0; i < m1.xsize + 2; i++)//free the 2d visited array
    {
        free(m1.visited[i]);
    }
    free(m1.visited);
}


//function definitions

void init_Maze(maze* s)
{
    //initialize the stack, maze array, and visited array
    int y = s->ysize + 2;
    int x = s->xsize + 2;

    s->darr = (char**)malloc(sizeof(char*) * x);
    for (int i = 0; i < s->xsize + 2; i++)
    {
        s->darr[i] = (char*)malloc(sizeof(char) * y);
    }
    
    s->visited= (int**)malloc(sizeof(int*) * x);
    for (int i = 0; i < s->xsize + 2; i++)
    {
        s->visited[i] = (int*)malloc(sizeof(int) * y);
    }
}

int is_empty(Path* hd)
{//checking if the stack is empty
    if (hd == NULL)
        return TRUE;
    else
        return FALSE;
}

void push(Path** hd, int a, int b)
{   //Adding the next coordinates to the stack and if debugmode is on print whats being pushed
    if (DebugMode == TRUE)
    {
        
            Path* ptr = (Path*)malloc(sizeof(Path));
            ptr->xcorr = a;
            ptr->ycorr = b;
            ptr->next = *hd;
            *hd = ptr;
            printf("(%d,%d) pushed into the stack. \n", a, b);
        

    }
    else
    {
        Path* ptr = (Path*)malloc(sizeof(Path));
        ptr->xcorr = a;
        ptr->ycorr = b;
        ptr->next = *hd;
        *hd = ptr;
    }
}

void pop(Path** hd)
{//removing top coordinates from the stack and if debugmode is on print whats being popped
    if (DebugMode == TRUE)
    {
        if (*hd == NULL)
        {
            return;
        }
        else
        {
            Path* tmp = *hd;
            printf("(%d,%d) popped off the stack. \n", tmp->xcorr, tmp->ycorr);
            
            *hd = tmp->next;
            free(tmp);
        }

    }
    else
    {
        if (*hd == NULL)
        {
            return;
        }
        else
        {
            Path* tmp = *hd;
            *hd = tmp->next;
            free(tmp);
        }
    }
}

Path* top(Path* hd)
{//returns top head in the stack
    if (is_empty(hd) == TRUE)
    {
        return NULL;
   }
    else
    {
        return hd;
    }
}

void clear(Path* hd)
{//clears the entire stack and if debugmode is on print what is being removed
    if (DebugMode == TRUE)
    { 
        Path* curr = hd;
        Path* next;
        while (curr != NULL)
        {
            printf("(%d,%d) popped off the stack. \n", curr->xcorr, curr->ycorr);
            next = curr->next;
            free(curr);
            curr = next;
            
        }
        hd = NULL;
    }
    else
    {
        Path* curr = hd;
        Path* next;
        while (curr != NULL)
        {
            next = curr->next;
            free(curr);
            curr = next;
        }
        hd = NULL;
    }
}

void showRR(Path* hd)
{//recursively print the linkedlist in reverse order to show path followed from start to end
    if (hd == NULL)
    {
        return;
    }
    showRR(hd->next);
    printf("(%d,%d) ", hd->xcorr, hd->ycorr);
    return;
}