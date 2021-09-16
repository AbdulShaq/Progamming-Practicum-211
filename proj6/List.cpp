#include "Island.h"

//FileList
FileList::FileList()
{//constructor
    Head = NULL;
}

bool FileList::isExists(char* File)
{//checks if file infomation exists
    FileNode* node = Head;

    while (node != NULL) 
    {
        if (strcmp(node->FileName, File) == 0)
        {
            return true;
        }
        node = node->Next;
    }
    return false;
}

void FileList::AddFile(char* File)
{//adds file node information
    FileNode* curr = Head;
    FileNode* newHd = new FileNode;
    newHd->FileName = File;

    while (curr != NULL)
    {
        if (curr->Next == NULL)
        {
            curr->Next = newHd;
            return;
        }

        curr = curr->Next;
    }

    Head = newHd;
}

void FileList::DeleteFile(const char* File)
{//deletes file node information
    FileNode* curr = Head;
    FileNode* prev = curr;

    if (Head->FileName == File) 
    {
        Head = Head->Next;
        delete prev;
        return;
    }

    while (curr != NULL) 
    {
        if (curr->FileName == File) 
        {
            prev->Next = curr->Next;
            delete curr;
            return;
        }
        curr = curr->Next;
    }
}

//Node

Node::Node(int Val)
{//constructor 
    Island = Val;
    Next = NULL;
}

Node::Node(int Val, Node* N)
{//sets island and next node
    Island = Val;
    Next = N;
}

int Node::GetIsland()
{//returns island
    return Island;
}

Node* Node::GetNext()
{//returns next node
    return Next;
}

void Node::SetIsland(int Val)
{//set island
    Island = Val;
}

void Node::SetNext(Node* N)
{//set next node
    Next = N;
}

//MyList

MyList::MyList()
{//constructor
    Head = NULL;
}

void MyList::SetHead(Node* hd)
{//sets the head
    Head = hd;
}

Node* MyList::GetHead()
{//returns head node
    return Head;
}

void MyList::Insert(int Val)
{//inserts node with island into list
    Node* tmp = new Node(Val, NULL);
    Node* curr = Head;
    Node* prev = NULL;

    while (curr != NULL) 
    {
        if (curr->GetIsland() == Val) 
        {
            printf("Ferry ride already added!\n");
            return;
        }

        prev = curr;
        curr = curr->GetNext();
    }

    if (prev == NULL) 
    {
        Head = tmp;
    }
    else 
    {
        prev->SetNext(tmp);
    }

}

void MyList::Remove(int Val)
{//removes an island from a node in the list
    Node* curr = Head;
    Node* prev = NULL;

    while (curr != NULL && curr->GetIsland() != Val) 
    {
        prev = curr;
        curr = curr->GetNext();
    }

    if (curr == NULL) 
    {
        printf("Ferry ride does not exist\n");
        return;
    }
    
    if (prev == NULL) 
    {
        prev = curr->GetNext();
        delete curr;
        Head = prev;
    }

    else 
    {
        prev->SetNext(curr->GetNext());
        delete curr;
    }
}

int MyList::GetListLeng()
{//returns the length of the list
    int total = 0;
    Node* tmp = Head;

    while (tmp != NULL) 
    {
        total++;
        tmp = tmp->GetNext();
    }

    return total;
}

int MyList::GetNthElem(int n)
{//returns the island at Nth place in list
    int count = 0;
    Node* tmp = Head;

    while (tmp != NULL && count != n) {
        count++;
        tmp = tmp->GetNext();
    }

    if (tmp == NULL)
    {
        return -999;
    }

    else 
    {
        return tmp->GetIsland();
    }

}

void MyList::PrintList()
{//prints island in list order
    Node* tmp = Head;

    while (tmp != NULL) 
    {
        printf("%d  ", tmp->GetIsland());
        tmp = tmp->GetNext();
    }
}

void MyList::PrintListOrder()
{//prints the list in order of path
    Node* tmp = Head;

    while (tmp != NULL) 
    {
        printf("%d", tmp->GetIsland());

        if (tmp->GetNext() != NULL)
        {
            printf(" - ");
        }

        tmp = tmp->GetNext();
    }
    printf("\n");
}

void MyList::RemoveList()
{//removes all nodes in a list
    Node* tmp;

    while (Head != NULL) 
    {
        tmp = Head;
        Head = Head->GetNext();
        delete tmp;
    }
}

bool MyList::isEmpty()
{//checks if list is empty
    if (Head == NULL) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

//Island

Island::Island()
{//Island constructor
    adjac = new MyList;
    Num = 0;
    PrevLocal = -1;
    visited = false;
}

MyList* Island::GetAdjac()
{//returns list of adjacent islands
    return adjac;
}

bool Island::GetVisited()
{//returns whether an island is visited
    return visited;
}

void Island::SetVisited(bool TF)
{//sets wheter an island is visited or not
    visited = TF;
}

int Island::GetPrevLocal()
{//returns previous island
    return PrevLocal;
}

void Island::SetPrevLocal(int i1)
{//sets previous island visited
   PrevLocal = i1;
}

void Island::SetNum(int num)
{//returns island number
    Num = num;
}

int Island::GetSize()
{//returns number of islands
    return GetAdjac()->GetListLeng();
}

//MyQueue

MyQueue::MyQueue()
{
}

void MyQueue::Enqueue(int Val)
{//adds island from queue
    Node* curr = new Node(Val);
    Node* tmp = GetHead();

    if (GetHead() == NULL) 
    {
        SetHead(curr);
        return;
    }

    while (tmp->GetNext() != NULL) 
    {
        tmp = tmp->GetNext();
    }

    tmp->SetNext(curr);

    return;
}

void MyQueue::Dequeue()
{//remvoes island from queue
    Node* tmp = GetHead();

    SetHead(GetHead()->GetNext());

    delete tmp;
}

int MyQueue::Peak()
{//checks if list is empty then returns head island
    if (!isEmpty()) 
    {
        return GetHead()->GetIsland();
    }
    return -999;
}

//MyStack

MyStack::MyStack()
{
}

void MyStack::Push(int Val)
{//pushes node onto stack
    Node* curr = new Node(Val);

    if (GetHead() == NULL) 
    {
        SetHead(curr);
    }

    else 
    {
        curr->SetNext(GetHead());
        SetHead(curr);
    }
}


void MyStack::Pop()
{//pops top of stack
    Node* tmp = GetHead();

    SetHead(GetHead()->GetNext());

    delete tmp;
}

int MyStack::Top()
{//finds and retuns top of stack
    Node* curr = GetHead();

    while (curr->GetNext() != NULL) 
    {
        curr = curr->GetNext();
    }

    return curr->GetIsland();
}

