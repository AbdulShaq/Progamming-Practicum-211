/*Abdul Shaqildi
UIC, Spring 2021
CS 211, Nasim Mobasheri*/

/*Main.c is a program to take a list of non-negative integers and store them in a dynamic array.
 then, create another dynamic array to copy the orignal one and then sort the coppy array in accending order.
 then based on the user input the program will either, 1) Do an index comparison between the 2 arrays or
 2) find a target sum in the array based on the target value given to the program.
 */
#include <stdio.h>
#include <stdlib.h>

//Function decleration
void makeArrayCopy(int fromArray[], int toArray[], int size);
void myFavoriteSort(int arr[], int size);
void indexComparison(int unsortedArray[], int sortedArray[], int size, int* counter);
int targetSum(int arr[], int size, int target, int* index1, int* index2);

//Main function
int main(int argc, char** argv)
{
    int val;
    int userInput;
    int* OrigArr;
    int* CopyArr;
    int size = 4;
    int i = 0;
    int k;
    int counter = 0;
    int Ind1 = 0, Ind2 = 0;
    OrigArr = (int*)malloc(sizeof(int) * size);

    
    /* prompt the user for input */
    printf("Enter in a list of numbers to be stored in a dynamic array.\n");
    printf("End the list with the terminal value of -999\n");

    /* loop until the user enters -999 */
    
    scanf("%d", &val);
    //Dynamically allocating the array
    while (val != -999)
    {
        if (i >= size)
        {
           
            int* tmp;
            tmp = OrigArr;

            OrigArr = (int*)malloc(sizeof(int) * size * 2);

            /* store the value into an array */

            for (k = 0; k < size; k++)
            {
                OrigArr[k] = tmp[k];
            }
            free(tmp);

            size = size * 2;
          }

        /* get next value */
        OrigArr[i] = val;
        i++;
        scanf("%d", &val);
    }

   //Making the size of the copy array match the new size of the orignal array
    CopyArr = (int*)malloc(sizeof(int) * size);

    //Call to function to fill copy array
    makeArrayCopy(OrigArr, CopyArr, i);
    
    //Call to function to sort copy array in accending order
    myFavoriteSort(CopyArr, i);
   
    /* Prompt user to enter a value to pick a task */
    printf("Enter 1 to perform index comparison, enter 2 to perform target sum.\n");
    scanf("%d", &userInput);

    while (userInput != 1 || userInput != 2)
    {
        /* If user input is 1, perform index comparison */
        if (userInput == 1) 
        {
            //Call to index comparison function 
           indexComparison(OrigArr, CopyArr, i, &counter);
           
           if (counter == 0)
           {//Output if none of the elements are in the same place
               printf("All elements change location in the sorted array.\n");
           }

           else
           {//output if there is 1 or more elements in the same place
               printf("%d values are in the same location in both arrays.\n", counter);
           }
           break;
        }

        /* If user input is 2, perform target sum */
       else if(userInput == 2) 
        {
           printf("Enter in a list of numbers to use for searching.  \n");
           printf("End the list with a terminal value of -999\n");
           scanf("%d", &val);

           while (val != -999)
           {
               //Call to target sum function then setting its return value to result
               int Result = targetSum(CopyArr, i, val, &Ind1, &Ind2);
           /* print out info about the target sum results  */
               if (Result == 1) 
               {
                   //In1 and In2 represent the 2 indices that add to the target sum
                   printf("Success! Elements at indices %d and %d add up to %d.\n", Ind1, Ind2, val);
                  
               }
               else
               {
                   printf("Target sum failed!\n"); //output if there are no 2 numbers that add up to the target sum
               }

            /* get next value */
             scanf("%d", &val);
            }
           break;
        }
        else
        {
            //continue requesting user input if not 1 or 2*
            printf("Invalid input. Enter 1 or 2.\n");
        }
        scanf("%d", &userInput);
       
    }

    


    printf("Good bye\n");
    return 0;
}


void makeArrayCopy(int fromArray[], int toArray[], int size) 
{
 //Function to take the values from the original array anf copy them into the copy array of the same size   
    int i;
        for ( i = 0; i < size; i++)
        {
            toArray[i] = fromArray[i];
        }
}

void myFavoriteSort(int arr[], int size) 
{//Function to sort the values of an array in accending order
    int i, j, temp;
    for (i = 0; i < size - 1; i++) 
    {   
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1]) {
                //swapping of values if value of j is greater than that of j+1
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            else {
                //keep the values where they are if already in the correct order
                arr[j] = arr[j];
                arr[j + 1] = arr[j + 1];
            }
        }
    }
   
}

void indexComparison(int unsortedArray[], int sortedArray[], int size, int* counter)
{//Function to compare the orginal array and the sorted copy array to see if any values stayed in the same place
    int i;
    for (i = 0; i < size ; i++)
    {
        if (unsortedArray[i] == sortedArray[i]) 
        {
            (*counter)++;//keeping count of the  values that are in the same place in both arrays
        }
        
    }
   
}

int targetSum(int arr[], int size, int target, int* index1, int* index2)
{//Function to find if there are 2 values in the array that add up to the given target number
    int i = 0;
    int j = size-1;
    while(i<j)
    { 
        int sum = arr[i] + arr[j]; // value of first and last elements in the array

            if (sum == target)// if the sum is found then return the indecies of the values
            {
                (*index1) = i;
                (*index2) = j;
                return 1;
            }
            
            else if (sum < target) //if the sum is less than the target move to the next index for i
            {
                i++;
            }

            else // if the sum is greater than the target, then move down to the perious idex for j
            {
                j--;
            }

        
    }
    return -1;
}