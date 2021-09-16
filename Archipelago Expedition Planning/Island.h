#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

class FileNode//file node class
{
public:
	char* FileName;
	FileNode* Next;
};

class FileList//file class
{
private:
	FileNode* Head;
public:
	FileList();

	bool isExists(char* File);//checks if file exists

	void AddFile(char* File);//add function

	void DeleteFile(const char* File);//delete function

};

class Node//node class
{
private:
	int Island;

	Node* Next;
public:
	Node(int Val);

	Node(int Val, Node* N);

	int GetIsland();//return island

	Node* GetNext();// pointer to get next node

	void SetIsland(int Val);//set the island number

	void SetNext(Node* N);//set a node as next

};

class MyList//linked list class
{
private:
	Node* Head;
public:
	MyList();

	void SetHead(Node* hd);//setting head node

	Node* GetHead();//returning node

	void Insert(int Val);//inserting node

	void Remove(int Val);//removing node

	int GetListLeng();//returns the list length

	int GetNthElem(int n);//returns the Nth element in the list

	void PrintList();//prints the list of islands

	void PrintListOrder();//prints island list in order

	void RemoveList();//removes everything from a list

	bool isEmpty();//checks if the list is empty


};

class Island //Island class
{
private:
	MyList* adjac;
	bool visited;
	int PrevLocal;
	int Num;
public:
	Island();

	MyList* GetAdjac();//gets adjacent list of island

	bool GetVisited();// checks if an island has been visited

	void SetVisited(bool TF);//sets if an island is visited

	int GetPrevLocal();//returns the previous island

	void SetPrevLocal(int i1);//set the previous island

	void SetNum(int num);//sets the number of islands

	int GetSize(); //returns the number of islands

};

class MyQueue: public MyList// Queue class
{
private:
	Node* Head;
	Node* Next;
public:
	MyQueue();

	void Enqueue(int Val);//puts nodes in order of queue

	void Dequeue();//removes a node from the queue

	int Peak();//returns head island

};

class MyStack: public MyList// Stack class
{
public:
	MyStack();

	void Push(int Val);//Push to stack

	void Pop();//Pop from stack

	int Top();//return top of stack

};
