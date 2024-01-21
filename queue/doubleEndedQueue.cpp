#include <iostream>
using namespace std;



// creating the Node class
struct Node
{
	int data;
	Node * next;
};

class doubleEndedList
{
	public:
		int qLength;
		Node * head;
		Node * itr;
	doubleEndedList()
		{ 		// constrcutor function
			qLength = 0;
			head = nullptr;
			itr = head;
		}
		~doubleEndedList() // this is the destructor function
		{
			delete head;
		}

		void enQueue(int payload) // this is the normal enque function
		{
			qLength = qLength + 1;
			Node * newNode = new Node();
			newNode->data = payload;
			newNode->next = nullptr;
			if (head == nullptr)
			{
			head = newNode;
			return;
			}
			itr = head;
			while(itr->next != nullptr)
			{
			itr = itr->next;
			}
			itr->next = newNode;
			return;
		}
		void deQueue () // this is the normal deque function
		{
			if (qLength == 0)
			{
				cout << "cannot deque and empty queue " << endl;
				return;
			}
			Node * delNode = head;
			head =  delNode->next;
			delete delNode;
			qLength  = qLength - 1;
			return;
		}
		void print()
		{
			if (head == nullptr)
			{
				cout << "<Empty Queue>" << endl;
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
		void altEnQueue(int payload) // this enters the node in the beginning of the queue
		{
			qLength = qLength + 1;
			Node * newNode = new Node();
			newNode->data = payload;
			newNode->next = nullptr;
			
			Node * nextNode = head;
			head = newNode;
			newNode->next = nextNode;


		}


		void altDeQueue() // this deletes the node from the beginning of the queue
		{
			if (qLength == 0)
			{
			cout << "cannot alt deque from an emtpy queue" << endl;
			return;
			}
			itr = head;
			Node * prevNode = nullptr;
			while (itr->next != nullptr)
			{
			prevNode = itr;
			itr = itr->next;
			}
			prevNode->next = nullptr;
			delete itr;
			return;
			
		}

};


int main()
{
cout << "hello from the main function " << endl;
doubleEndedList dbl;
dbl.print();
dbl.enQueue(5);
dbl.enQueue(27);
dbl.enQueue(56);
dbl.print();
dbl.deQueue();
dbl.print();
dbl.altEnQueue(141);
dbl.print();
dbl.altDeQueue();
dbl.print();

return 0;
}
