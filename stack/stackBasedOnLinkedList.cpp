#include <iostream>
using namespace std;

struct Node

{
	int data;
	Node * next;
};

class Stack
{
	public:
	Node * head;
	Node * itr; // we use this for printing the stack , not while insertion/deletion of elements into the stack.
	int stackLength;
	
	Stack()
	{
		head = nullptr;
		stackLength = 0;
	}
	void push(int payload)
	{
		Node * newNode = new Node();
		newNode->data = payload;
		newNode->next = nullptr;
		if (head == nullptr)
		{
			head = newNode;
			stackLength = stackLength + 1;
			return;
		}
		else
		{
		Node * nextNode = head;
	        head = newNode;
		newNode->next = nextNode;
		stackLength = stackLength + 1;
		}
		
	}
	void pop()
	{
	if (stackLength == 0)
		{
			cout << "cannot pop from an empty stack" << endl;
			return;
		}
	Node * nextNode = head->next;
	head = nextNode;
	stackLength = stackLength -1;
	}
	void display()
	{
	if (head == nullptr)
	{
		cout << "the stack is empty" << endl;
		return;
	}
	itr = head;

	while (itr != nullptr)
	{
		cout << itr->data << endl;
		itr = itr->next;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
};

int main()
{
	cout << "hello from the main function " << endl;
	Stack myStack;
	myStack.display();
	myStack.push(5);
	myStack.display();
	myStack.push(27);
	myStack.push(42);
	myStack.push(141);
	myStack.push(67);
	myStack.display();
	myStack.pop();
	myStack.pop();
	myStack.pop();
	myStack.pop();
	
	myStack.display();
	myStack.pop();
	myStack.display();
	return 0;
}

