#include <iostream>
#include <vector>
using namespace std;


/*
depending on the rotation , this is how the coloring would be done
ll or rr : gp and p 
lr or rl : gp and child

*/

#define red 1
#define black 2

Node * NULL_POINTER = new Node(0);


struct Node
{
    int value; 
    Node * left;
    Node * right;
    Node * parent;
    int color;
    Node(int data)
    {
        data = value;
        left = nullptr;
        right = nullptr;
        parent = NULL_POINTER;
        color = red; // all newly inserted nodes are assumed to be red in color
    }
};


int children (Node *& current)
{
    if (!current->left & !current->right)
        return 0;
    else if (current->left && current->right)
        return 2;
    else
        return 1;
}

void recolor (Node * current)
{
    if (current->color == red)
        current->color = black;
    else 
        current->color = red;
}


Node * sibling (Node *& current)
{
    if (current->parent == NULL_POINTER)
        return NULL_POINTER;
    Node * parent_node = current->parent;
    if (children(parent_node) != 2)
        return NULL_POINTER;
    if (parent_node->left == current)
        return parent_node->right;
    else 
        return parent_node->left;
}
Node * grandparent (Node *& current)
{
    if (current->parent == NULL_POINTER)
        return NULL_POINTER;
    else 
        return current->parent->parent;
}


Node * uncle (Node *& current)
{
    if (grandparent(current) == NULL_POINTER)
        return NULL_POINTER;

    Node * grandparent_node = grandparent(current);

    if (children(grandparent_node) != 2)
        return NULL_POINTER;
    
    if (grandparent_node->left == current->parent)
        return grandparent_node->right;
    else 
        return grandparent_node->left;
}

bool isRootNode (Node * current)
{
    if (current == NULL_POINTER)
        return false;
    if (current->parent == NULL_POINTER)
        return true;
    else 
        return false;
}

void insertToRBTree(Node *& root , Node *& newNode)
{
    if (!root)
    {
        root = newNode; // inserting the node
        if (newNode->parent != NULL_POINTER && newNode->parent->color == red)
        {
            // conflict
            // red red relation found 
            // that is both the parent and the child are red in color 
            if (uncle(newNode) == NULL_POINTER || uncle(newNode)->color == black)
            {

            }
            else // red in color 
            {
                // re color both the parent and the uncle
                recolor(newNode->parent);
                recolor(uncle(newNode));
                
                if (!isRootNode(grandparent(newNode)))
                    recolor(grandparent(newNode));

            }
        }
        return;
    }
    if (root->value == newNode->value) return;
    newNode->parent = root;
    if (newNode->value < root->value)
        insertToRBTree(root->left , newNode);
    else 
        insertToRBTree(root->right , newNode);
}

int main()
{

    Node * root = nullptr;
    std::vector<int> dataset = {8 , 3 , 6 , 1 , 9 };
    for (int value : dataset)
    {
        Node * newNode = new Node(value);
        if (!root) // root is empty 
            newNode->color = black;
        insertToRBTree(root , newNode);
    }
    return 0;
}
