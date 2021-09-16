#include "Island.h"
#pragma warning(disable : 4996)

class ArchipelagoExpedition
{
private:
    // Create the Data Members for the Archipelago Network here
    Island* Expedition;
    int NumIsland;
    FileList File;
    MyQueue IslandQueue;
    MyStack Path;

public:

    // Use a constructor to initialize the Data Members for your expedition
    ArchipelagoExpedition()
    {// setting dynamic array to size 10
        NumIsland = 10; 
        Expedition = new Island[NumIsland];
    }
    ~ArchipelagoExpedition()
    {
        delete[] Expedition;
    }
     
    // The main loop for reading in input
    void processCommandLoop(FILE* inFile)
    {
        char  buffer[300];
        char* input;

        input = fgets(buffer, 300, inFile);   // get a line of input

        // loop until all lines are read from the input
        while (input != NULL)
        {
            // process each line of input using the strtok functions 
            char* command;
            command = strtok(input, " \n\t");

            printf("*%s*\n", command);

            if (command == NULL)
                printf("Blank Line\n");

            else if (strcmp(command, "q") == 0)
                exit(1);

            else if (strcmp(command, "?") == 0)
                showCommands();

            else if (strcmp(command, "t") == 0)
                doTravel();

            else if (strcmp(command, "r") == 0)
                doResize();

            else if (strcmp(command, "i") == 0)
                doInsert();

            else if (strcmp(command, "d") == 0)
                doDelete();

            else if (strcmp(command, "l") == 0)
                doList();

            else if (strcmp(command, "f") == 0)
                doFile();

            else if (strcmp(command, "#") == 0)
                ;

            else
                printf("Command is not known: %s\n", command);

            input = fgets(buffer, 300, inFile);   // get the next line of input

        }
    }

    void showCommands()
    {
        printf("The commands for this project are:\n");
        printf("  q \n");
        printf("  ? \n");
        printf("  # \n");
        printf("  t <int1> <int2> \n");
        printf("  r <int> \n");
        printf("  i <int1> <int2> \n");
        printf("  d <int1> <int2> \n");
        printf("  l \n");
        printf("  f <filename> \n");
    }

    void doTravel()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok(NULL, " \n\t");

        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL, " \n\t");


        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }


        printf("Performing the Travel Command from %d to %d\n", val1, val2);

        MyStack Path = breadthFirstSearch(val1, val2);

        if(!Path.isEmpty())//checks if the path is empty 
        {
            printf("shortest path from %d to %d: ",val1,val2);
            Path.PrintListOrder();//call to print order for path
        }

    }

    void doResize()
    {//resize function
        int val1 = 0;
   
        char* Next = strtok(NULL, " \r\n\t");

        if (Next == NULL)//checks if value is entered 
        {
            printf("Integer value expected\n");
            return;
        }

        val1 = atoi(Next);

        delete[] Expedition;

        NumIsland = val1;
        Expedition = new Island[NumIsland];

        for (int i = 0; i < val1; i++) //make new sized array
        {
            Expedition[i].SetNum(i + 1);
            Expedition[i].SetVisited(false);
        }

        printf("Performing the Resize Command with %d\n", val1);


    }

    void doInsert()
    {
        int v1 = 0;
        int v2 = 0;

       
        char* Next = strtok(NULL, " \r\n\t");

        if (Next == NULL)//cehcks if value was entered
        {
            printf("Integer value expected\n");
            return;
        }

        v1 = atoi(Next);

        if (v1 == 0 && strcmp(Next, "0") == 0)//checks to make sure value entered is not 0s
        {
            printf("Integer value expected\n");
            return;
        }

       
        Next = strtok(NULL, " \r\n\t");

        if (Next == NULL)//cehcks if value was entered
        {
            printf("Integer value expected\n");
            return;
        }

        v2 = atoi(Next);

        if (v2 == 0 && strcmp(Next, "0") == 0)//checks to make sure value entered is not 0s
        {
            printf("Integer value expected\n");
            return;
        }

        if(v1==v2)//checks if values entered are not the same
        {
            printf("Can not add ferry ride to self\n");
            return;
        }

        if (v1 <= NumIsland && v2 <= NumIsland) 
        {

            printf("Performing the Insert Command for %d\n", v1);

            Expedition[v1 - 1].GetAdjac()->Insert(v2);
            Expedition[v2 - 1].SetPrevLocal(v1);

        }

        else
        {
            printf("Invalid value for island\n");
        }
    }

    void doDelete()
    {//delete function
        int v1 = 0;
        int v2 = 0;

        char* Next = strtok(NULL, " \r\n\t");

        if (Next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }

        v1 = atoi(Next);

        if (v1 == 0 && strcmp(Next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        Next = strtok(NULL, " \r\n\t");

        if (Next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }

        v2 = atoi(Next);

        if (v2 == 0 && strcmp(Next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        if ((v2 > NumIsland) || (v1 > NumIsland))
        {
            printf("Invalid value for island\n");
            return;
        }

        printf("Performing the Delete Command for %d\n", v1);

        Expedition[v1 - 1].GetAdjac()->Remove(v2);

    }

    void doList()
    {//prints adjacency list
        printf("Displaying the adjacency list:\n");

        for (int i = 0; i < NumIsland; i++) 
        {

            if (Expedition[i].GetSize() == 0)
            {
                printf("%d -->", i + 1);
                printf("\n");
            }

            else 
            {
                printf("%d -->  ", i + 1);
                Expedition[i].GetAdjac()->PrintList();
                printf("\n");
            }

        }

    }

    void doFile()
    {
        // get a filename from the input
        char* fname = strtok(NULL, " \r\n\t");
        if (fname == NULL)
        {
            printf("Filename expected\n");
            return;
        }

        printf("Performing the File command with file: %s\n", fname);

        // next steps:  (if any step fails: print an error message and return ) 
        //  1. verify the file name is not currently in use
        //  2. open the file using fopen creating a new instance of FILE*
        //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
        //  4. close the file when processCommandLoop() returns

        if (File.isExists(fname)) {
            printf("File is already in use\n");
            return;
        }

        FILE* FileName;
        FileName = fopen(fname, "r");

        if (FileName == NULL) {
            printf("File is already in use\n");
            return;
        }

        File.AddFile(fname);

        processCommandLoop(FileName);

        fclose(FileName);
        File.DeleteFile(fname);
    }

    MyStack breadthFirstSearch(int x, int y)
    {
       
        MyStack Adjac;
        MyQueue IslandQue;

        for (int i = 0; i < NumIsland; i++) 
        {
            Expedition[i].SetVisited(false);
            Expedition[i].SetPrevLocal(-1);
        }

        IslandQue.Enqueue(x);


        if (!bfs(y, IslandQue))
        {
            printf("You can NOT get from island %d to island %d \n",x,y);
            return Adjac;
        }
        else 
        {
            
            printf("You can get from island %d to island %d \n", x, y);
          
            int CurrIsland = y;

            Adjac.Push(CurrIsland);

            do 
            {
                CurrIsland = Expedition[CurrIsland - 1].GetPrevLocal();
                Adjac.Push(CurrIsland);

            } while (CurrIsland != x);
            
            return Adjac;

        }


    }

    bool bfs(int b, MyQueue& IslandQue)
    {

        while (!IslandQue.isEmpty()) 
        {
            int a = IslandQue.Peak();
            IslandQue.Dequeue();

            for (int i = 0; i < Expedition[a - 1].GetAdjac()->GetListLeng(); i++) 
            {
                int c = Expedition[a - 1].GetAdjac()->GetNthElem(i);

                if (!Expedition[c - 1].GetVisited()) 
                {
                    Expedition[c - 1].SetVisited(true);
                    Expedition[c - 1].SetPrevLocal(a);

                    if (c == b) 
                    {
                        return true;
                    }
                    IslandQue.Enqueue(c);
                }
            }
        }
        return false;
    }
};

int main(int argc, char** argv)
{
    // set up the varqiable inFile to read from standard input
    FILE* inFile = stdin;

    // set up the data needed for the island adjcency list
    ArchipelagoExpedition islandData;

    // call the method that reads and parses the input
    islandData.showCommands();
    printf("\nEnter commands at blank line\n");
    printf("    (No prompts are given because of f command)\n");
    islandData.processCommandLoop(inFile);

    printf("Goodbye\n");
    return 0;
}