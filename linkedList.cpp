#include <iostream>
using namespace std;

struct Node
{
    int payload;
    Node* link;
};
int listLength = 0;
Node* accessPointer  = nullptr;

void insertNode(int data)
{
    Node* temp  = new Node();
    temp->payload = data;
    
    if (listLength == 0)
    {
        temp->link = nullptr;
        accessPointer = temp;
        listLength++;
        
    }
    else
    {
        Node* tempIterator = accessPointer;
        
        while (tempIterator->link != nullptr)
        {
            tempIterator = tempIterator->link;
        }
        tempIterator->link = temp;
        temp->link = nullptr;
        listLength++;
    }

}

void insertHeadNode(int data)
{
    Node* temp = new Node();
    temp->payload = data;
    temp->link = accessPointer;
    accessPointer = temp;
    listLength++;
}
void insertNode(int data, int position)
{
    if (position < 1 || position > listLength + 1)
    {
        cout << "\nError in the entered position... \n";

    }
    else
    {
        if (position == listLength+1 ) //Inserting the tail node
        {
            insertNode(data);
        }
        else if (position == 1) // Inserting the head node in the list
        {
            insertHeadNode(data);
        }
        else //Inserting the node at any other general position
        {
            Node* temp  = new Node();
            temp->payload = data;
            Node* tempIterator = accessPointer;
            int ctr = 1;
            while (ctr != position-1)
            {
                tempIterator = tempIterator->link;
                ctr++;
            }
           temp->link = tempIterator->link;
           tempIterator->link = temp;
            listLength++;
        }
    }

}

void printList()
{
    if (listLength == 0)
    {
        cout << "The given list in empty";
    }
    else
    {
        
    Node* temp = accessPointer;
    
    bool firstNode = true;
    while (true)
    {
       if (!firstNode)
        {
            cout << " -> ";

        }  
        cout << temp->payload  ;
       
        firstNode = false;
        if (temp->link == nullptr)
        {
            break;
            
        }
        else
        {
            temp = temp->link;
        }
    }
    }
    cout << endl;
}

void deleteNode(int position)
{
    if (position < 1 || position > listLength || listLength == 0)
    {
        cout << "Error....." << endl;
    }
    else 
    {
        listLength--;
        int ctr = 1;
        Node* temp = accessPointer;
        Node* prevTemp;
        while (ctr != position)
        {
            prevTemp = temp;
            temp = temp->link;
            ctr++;
        }
        if (position == 1)
        {
            accessPointer = temp->link;

        }
        else 
        {
        prevTemp->link = temp->link;

        }
  
        delete temp;
        temp = nullptr;
    }
}

void flushList()
{
    
    int staticLength = listLength;
   if (listLength == 0)
   {
    cout << "List is empty \n";
   }
   else{
 for (int i= 1;i<=staticLength;i++)
    {
        deleteNode(1);
    }
}
   }

void reverseList() 
{
    if (listLength != 0 && listLength != 1)
    {
        
        int listCopy[listLength];
        int ctr = listLength;
        Node* temp = accessPointer;
        while (true)
        {
            listCopy[ctr-1] = temp->payload;
            if (temp->link == nullptr)
            {
                break;
            }
             temp = temp->link;
            ctr--;

        }
        ctr = listLength;
        flushList();
    for (int i = 0;i<ctr;i++)
    {
        insertNode(listCopy[i]);
    }
    
    } 
}
   
int main()
{
    bool flag = true;
 while (flag)
 {
    cout << endl;

    printList();
    
    cout << endl;
    cout << "1)Insert Node \n";
    cout << "2)Delete Node \n";
    cout << "3)Flush List \n";
    cout << "4)Reverse List \n";
    
    cout << "0)Exit \n";
    int choice;
    int data, position;

    cin >> choice;
    switch(choice)
    {
        case 1:
        cout << "Enter the data:" << endl;
        cin >> data;
        cout << "Enter the position to insert data at: " << endl;
        cin >> position;
        insertNode(data,position);
        break;
        
        case 2:
        cout << "Enter the position to delete the node at: " << endl;
        cin >> position;
        deleteNode(position);
        break;

        case 3:
        cout << "Flushing List... \n";
        flushList();
        break;
        
        case 4:
        reverseList();
        break;


        case 0:
        cout << "Flushing List... \n";
        flushList();
        cout << "Exiting.....";
        flag = false;
        break;

        default:
        cout << "Choose the correct option...";

    }
 }
}