#include <iostream>
using namespace std;
struct Node
{
	int data;
	Node * next;
};

class Queue // FIFO which is first in is the first one out
{
	public:
	Node * head;
	int qLength;
	Node * itr;
	Queue() // ocmnstructor function
	{
		qLength = 0;
		head = nullptr;
		itr = head;
	}
	~Queue() // destrcutor function
	{
		delete head;
	}

	void enQueue(int payload)
	{
	 	Node * tempNode = new Node();
		tempNode->data = payload;
		tempNode->next = nullptr;
		qLength = qLength + 1;
		if (head == nullptr)
		{
		head = tempNode;
		return;
		}
		itr = head;
		while (itr->next != nullptr)
		{
			itr = itr->next;
		}
		itr->next = tempNode;
		return;

	}


	void deQueue()
	{
		if (qLength == 0)
		{
			cout << "cannot deque from an empty queue!" << endl;
			return;
		}
		Node * delNode = head;
		head = delNode->next;
		delete delNode;
		qLength = qLength - 1;
		return;
	}
	
	//just a basic printing function
	
	void print()
	{
		if (qLength == 0)
		{
			cout << "<Empty Queue> "<< endl;
			return;
		}
		itr = head;
		while (itr != nullptr)
		{
			cout << itr->data << " ";
			itr = itr->next;
		}
		cout << endl;
	}



};



int main ()
{
cout <<"hello from the main function " << endl;
//init of the queue


Queue q;
q.print();
q.enQueue(5);
q.enQueue(27);
q.print();
q.enQueue(141);
q.print();
q.deQueue();
q.print();
q.deQueue();
q.print();
q.deQueue();
q.print();
q.deQueue();
q.print();
return 0;
}
