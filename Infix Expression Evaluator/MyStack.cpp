/*Abdul Shaqildi
UIC, Spring 2021
CS 211, Nasim Mobasheri*/
#include "MyStack.h"



MyStack::MyStack()
{
    setCap(2);// initialize capacity
    setinUse(0);//initialize in use
    arr = new int[cap];//initialize array
}

MyStack::~MyStack()
{
    delete[] arr;//deletes array
}

int MyStack::Top()
{
    //checks if stack is empty then returns top value
    if (isEmpty() != true)
    {
        return arr[inUse - 1];
    }
    else
    {
        return -999;
    }
}

int MyStack::getinUse()
{//returns the number of inuse
    return inUse;
};

int MyStack::getCap()
{//returns the capacity
    return cap;
}

void MyStack::setinUse(int val)
{//sets the in use
    inUse = val;
}

void MyStack::setCap(int val)
{//sets the capacity
    cap = val;
}

void MyStack::Push(int val)
{
    //checks if stack is full
    if (isFull() == true)
    {
        reSize();//resizes stack
        arr[inUse] = val;
        inUse++;
    }
    else
    {//adds value to stack
        arr[inUse] = val;
        inUse++;
    }

}

void MyStack::Pop()
{
    if (isEmpty() != true)
    {//removes value from stack
        inUse--;
    }
}

void MyStack::reSize()
{
    cap = cap + 2;//increases cpacity by 2
   
    int* temp = new int[cap]; //creates temp array

    for (int i = 0; i < inUse; i++)
    {
        temp[i] = arr[i];//coppy info from old array
    }
    delete[] arr;
    arr = temp;//save new larger array
}

void MyStack::Reset()
{
    //resets stack
    delete[] arr;
    setCap(2);
    setinUse(0);
    arr = new int[cap];
}

bool MyStack::isFull()
{//checks if stack is full
    if (inUse == cap)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MyStack::isEmpty()
{
    //checks if stack is empty
    if (inUse < 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
