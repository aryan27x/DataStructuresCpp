#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node
{
    int payload;
    int exponent;
    float coefficient;
    Node * next;
};

void display (Node *& head)
{
    if (!head)
    {
        cout << "The given linked list is empty ! " << endl;
        return;
    }
    cout << "This is the content of the linked list :  "<< endl;
    Node * itr = head;
    while (itr)
    {
        cout << itr->payload ;
        itr = itr->next;
        if (itr)
            cout << " -> ";
    }
    cout << endl;
}

void removeLoopFromLL(Node * head)
{
    Node * fast = head;  Node * slow = head;
    Node * slow_prev = nullptr;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow_prev = slow;
        slow = slow->next;
        if (fast == slow) //loop found 
        {   fast = head; // init fast to head
            while (slow != fast) // single step till equal
            {
                slow_prev = slow;
                slow = slow->next;
                fast = fast->next;
            }
            slow_prev->next = nullptr; // removing the loop 
        }
    }
}

Node * findIntersectionOfLL(Node *& head1 , Node*& head2)
{
    Node * itr1 = head1; Node * itr2 = head2;
    int l1 = 0; int l2 = 0;
    while (itr1) { l1++; itr1 = itr1->next;} // find the length of ll1
    while (itr2) { l2++; itr1 = itr2->next;} // find the length of ll2
    itr1 = head1; itr2 = head2; // reinstate the iterators 
    if (l1 > l2)
    {   int diff = l1 - l2; while(diff--) {itr1 = itr1->next;}  }
    else
    {   int diff = l2 - l1; while(diff--) {itr2 = itr2->next;}  }
    while (itr1)
    {
        if (itr1 == itr2) return itr1; // found the intersection
        itr1 = itr1->next;
        itr2 = itr2->next;
    }
    return nullptr;
}


Node * recursionReverse(Node * current)
{
    if (!current || !current->next) // just dealing with the base case
        return current;
   
    Node * newHead = recursionReverse(current->next); // iterating to the end

    current->next->next = current; // reversing the link
    current->next = nullptr; // setting up for the end of the new ll 

    return newHead;
}

Node * add(Node * poly1 , Node * poly2)
{
    Node * dummyHead = new Node;
    Node * answer_itr = dummyHead;
    while (poly1 && poly2)
    {
        Node * newNode = new Node;
        if (poly1->exponent > poly2->exponent)
        {
            newNode->exponent = poly1->exponent; newNode->coefficient = poly1->exponent;
            poly1 = poly1->next;
        }
        else if (poly2->exponent > poly1->exponent)
        {
            newNode->exponent = poly2->exponent; newNode->coefficient = poly2->exponent;
            poly2 = poly2->next;  
        }
        else // means that both of the exp are equal , add up the coeffs
        {
            newNode->exponent = poly1->exponent; // could also use poly2
            newNode->coefficient = poly1->coefficient + poly2->coefficient;
            poly1 = poly1->next; poly2 = poly2->next;
        }
        answer_itr->next = newNode; answer_itr = newNode;
    }
    while (poly1)
    {
        Node * newNode = new Node;
        newNode->coefficient = poly1->coefficient; newNode->exponent = poly1->exponent;
        answer_itr->next = newNode; answer_itr = newNode;
        poly1 = poly1->next;
    }
    while (poly2)
    {
        Node * newNode = new Node;
        newNode->coefficient = poly2->coefficient; newNode->exponent = poly2->exponent;
        answer_itr->next = newNode; answer_itr = newNode;
        poly2 = poly2->next;
    }
    return dummyHead->next;
}


Node * reverse(Node *& head)
{
    Node * current = head;
    Node * next = head->next;
    Node * prev = nullptr;
    while (current)
    {
        current->next = prev;
        prev = current;
        current = next;
        if (next)
            next = next->next;
    }
    return prev;
}

void reverseSublist(Node *& head , int p1 , int p2)
{
    if (p1 > p2) { int temp = p1 ; p1 = p2 ; p2 = temp;}
    Node * itr1 = head; p1--; Node * itr2 = head; p2--;
    Node * itr1_prev = nullptr; // prev to itr1 
    Node * itr2_next = nullptr; // next to it2
    while (p1--) { itr1_prev = itr1; itr1  = itr1->next; }
    while (p2--) { itr2 = itr2->next; } itr2_next = itr2->next;
    // now we just need to pluck the end of the sublist
    itr2->next = nullptr;
    if (!itr1_prev) // this means that this is swapping starting from the head
        head = reverse(itr1);
    else // this means that this is normal swapping
        itr1_prev->next = reverse(itr1);
    Node * tail = head; // iterate to find the null of the current ll 
    while (tail->next) tail = tail->next;
    tail->next = itr2_next; // link both the lls together
}



void swapPair(Node *& head , int p1 , int p2)
{

    std::cout << "this is the value of p1 : " << p1 << std::endl;
    std::cout << "this is the vlue of p2 : " << p2 << std::endl;
    Node * first = head;
    Node * first_prev = nullptr;
    Node * second = head;
    Node * second_prev = nullptr;

    p1--; p2--;
    while (p1--)
    {
        first_prev = first;
        first = first->next;
    }
    while (p2--)
    {
        second_prev = second;
        second = second->next;
    }

    


    Node * temp = first->next;
    first->next = second->next;
    second->next = temp;
    second_prev->next = first;
    first_prev->next = second;
}

void reverseSublistInGroup(Node *& head , int size , int ll_length)
{
    int start = 1;
    int end = start + size - 1;
    while (end <= ll_length)
    {
        reverseSublist(head , start , end);
        start = end + 1;
        end = start + size - 1;
    }
}


Node * multiply (Node *& first , Node *& second)
{
    Node * dummyNode = new Node;
    Node * itr = dummyNode;
    Node * outer = first;
    while (outer)
    {
        Node * inner = second;
        while (inner)
        {
            Node * newNode = new Node;
            newNode->coefficient = outer->coefficient * inner->coefficient;
            newNode->exponent = outer->exponent + inner->exponent;
            itr->next = newNode;
            itr = newNode;
            inner = inner->next;
        } 
        outer = outer->next;
    }
    // simplifying to combine terms with the same power
    itr = dummyNode->next;
    while (itr && itr->next)
    {
        if (itr->exponent == itr->next->exponent)
        {
            itr->coefficient += itr->next->coefficient;
            Node * buffer = itr->next;
            itr->next = itr->next->next;
            delete buffer;
        }
        else 
            itr = itr->next;
    }
    return dummyNode->next;
}


Node * rotate(Node *& head , int rotateValue , int ll_size)
{   
    if (rotateValue >= ll_size) rotateValue = rotateValue % ll_size;
    if (rotateValue == 0)
        return head;
    int copy = rotateValue;
    Node * itr = head;  
    Node * prev = nullptr;
    while (copy--)
    {
        prev = itr;
        itr = itr->next;
    }
    Node * tail = head;
    while(tail->next) tail = tail->next;
    tail->next = head;
    prev->next = nullptr;
    head = itr;
    return head;
}


Node * getMiddle (Node *& head)
{
    Node * slow = head;
    Node * fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}


Node * sortAndMerge(Node *& head1 , Node *& head2)
{
    Node * dummyHead = new Node;
    Node * head = dummyHead;

    Node * itr1 = head1;
    Node * itr2 = head2;

    while (itr1 && itr2)
    {
        if (itr1->payload < itr2->payload)
        {
            Node * newNode = new Node;
            newNode->payload = itr1->payload;
            head->next = newNode;
            itr1 = itr1->next;
        }
        else
        {
            Node * newNode = new Node;
            newNode->payload = itr2->payload;
            head->next = newNode;
            itr2 = itr2->next;
        }
    }

    while (itr1)
    {
            Node * newNode = new Node;
            newNode->payload = itr1->payload;
            head->next = newNode;
            itr1 = itr1->next;
    }
    while (itr2)
    {
            Node * newNode = new Node;
            newNode->payload = itr2->payload;
            head->next = newNode;
            itr2 = itr2->next;
    }
    return dummyHead->next;
}



// Node * sortAndMerge(Node *first, Node *second) {
  
//     // If either list is empty, return the other list
//     if (first == nullptr) return second;
//     if (second == nullptr) return first;

//     // Pick the smaller value between first and second nodes
//     if (first->payload < second->payload) 
    
//     {

//         // Recursively merge the rest of the lists and
//         // link the result to the current node
//         first->next = sortAndMerge(first->next, second);
//         return first;
//     }
//     else {
//         // Recursively merge the rest of the lists
//         // and link the result to the current node
//         second->next = sortAndMerge(first, second->next);
//         return second;
//     }
// }


void sortInserted (Node *& head , Node *& currentNode)
{
    if (!head)
    {
        head = currentNode;
        return ;
    }
    else
    {
        Node * itr = head;
        Node * prev = nullptr;

        while (itr && currentNode->payload > itr->payload)
        {
            prev = itr;
            itr = itr->next;
        }
        if (!prev)
        {
            currentNode->next = head;
            head = currentNode;
        }
        else 
        {
            prev->next = currentNode;
            currentNode->next = itr;
        }
    }

}
Node * insertionSort(Node *& head)
{

    if (!head)
        return nullptr;
    
    Node * sortedListHead = nullptr;

    Node * itr = head;
    while (itr)
    {
        Node * currentNode = itr;
        itr = itr->next;
        currentNode->next = nullptr;
        sortInserted(sortedListHead , currentNode);
    }

    return sortedListHead;
}
Node * mergeSort(Node *& head)
{
    if (head == nullptr || head->next == nullptr)
        return head;
    
    Node * left = head;
    Node * middle = getMiddle(head);
    Node * right = middle->next;
    middle->next = nullptr;

    left = mergeSort(left);
    right = mergeSort(right);
    return sortAndMerge(left , right);
    
}



int main()
{
    int n = 10;
    Node * head = nullptr;
    Node * tail = nullptr;

    for (int i = 0 ; i < n ; i++)
    {
        Node * newNode = new Node;
        newNode->payload = rand() % 10;
        newNode->next = nullptr;

        if (!head)
        {
                head = newNode;
                tail = newNode;
        }
        else
        {
                tail->next = newNode;
                tail = newNode;
        }


    }

    display(head);
    
    head = insertionSort(head);
    display(head);
    return 0;
}
