#include <iostream>
using namespace std;

struct Node
{
int data;
Node * nextNode;
Node * prevNode;
};

class List
{
	public: 
	int listLength;
	Node * head;
	Node * itr;
	List ()
	{
	// Setting up the constructor
		cout << "hello from the main constrcutor" << endl;
		listLength = 0;
		head = nullptr;
		itr = head;
	
	}
	void print()
	{
		if (listLength == 0)
		{
			cout << "the list is empty" << endl;
			return;
		}

		itr = head;
		while  (itr->prevNode != nullptr)
		{
			itr = itr->prevNode;
		}
		cout << itr->data << " ";
		while (itr->nextNode != nullptr)
		{
			itr = itr->nextNode;
			cout << itr->data << " ";
		}
			
		cout << endl;	
	}
	void addToRight(Node * newNode)
	{
		if (head == nullptr)
		{
		head = newNode;
		listLength = listLength + 1;
		return;	
		}
		itr = head;
		while (itr->nextNode != nullptr)
		{
			itr = itr->nextNode;
		}	
		itr->nextNode = newNode;
		newNode->prevNode = itr;
		listLength = listLength +1;

	}
	
	void addToLeft(Node * newNode)
	{
	
		if (head == nullptr)
		{
		head = newNode;
		listLength = listLength +1;
		return;
		}
		itr = head;
		while (itr->prevNode != nullptr)
		{
		itr= itr->prevNode;
		}
		itr->prevNode = newNode;
		newNode->nextNode = itr;
		listLength = listLength +1;
	}
	
void add (int payload , char position) // wrapper class
	{
	Node * tempNode = new Node();
	tempNode->data = payload;
	tempNode->prevNode = nullptr;
	tempNode->nextNode = nullptr;

	if (position == 'l' || position == 'L')
		{
			addToLeft(tempNode);
		}
	if (position == 'r' || position == 'R')
		{
			addToRight(tempNode);
		}
	}
int length()
{
	return listLength;
}

};


int main()
{
	cout << "this is from the main function" << endl;
	
	// we init the list class
	List list;
	list.print();
	list.add(4 , 'r') ; // we add '4' to the left of the list
	list.add(27 , 'r') ; // we add '27' to the right of the list
	list.print();
	list.add(141 , 'l');
	list.print();
	list.add(78 , 'l');
	list.add(49 , 'l');
	list.add(3232 , 'R');
	list.add(909 , 'r');
	list.print();


	return 0; // return from the main
}
