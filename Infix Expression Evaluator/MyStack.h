/*Abdul Shaqildi
UIC, Spring 2021
CS 211, Nasim Mobasheri*/
#pragma once
#include <cstdio>
#include <cstring>
#include <cctype>

class MyStack {
private:
    int inUse; //keeps track of the number of places in use
    int cap;//holds the capacity number of the dynamic array
    int* arr;//dynamic array to hold 
public:

    MyStack();//initalize array, in use and capacity

    ~MyStack();//destructor

    int Top();//return the top value of stack

    int getinUse();//return the number of values in stack

    int getCap();//returns the current capacity of ther array

    void setinUse(int val);//set the number of values in use

    void setCap(int val);//set the capacity for the array

    void Push(int val);//push a value on to the stack

    void Pop();//removes the top value from the stack

    void reSize();//grows the array when full

    void Reset();//resets the whole stack

    bool isFull();//checks whether the stack is full or not

    bool isEmpty();//checks whether the stack is empty or not
};