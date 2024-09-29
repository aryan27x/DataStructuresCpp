#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node
{

public : 
int data;
Node * left;
Node * right;
int height;
Node(int value)
{
    data = value;
    left = nullptr;
    right = nullptr;
    height = 1;
}
};


int height (Node *& current)
{
    if (!current) return 0;
    return current->height;
}

int balanceFactor(Node *& current)
{
    if (!current) return 0;
    return height(current->left) - height(current->right);
}

void updateHeight (Node *& root)
{
    if (!root) return;
    root->height = 1 + max(height(root->left) , height(root->right));
}
Node * rotateLeft (Node * current)
{

    Node * x = current->right;
    Node * buffer = x->left;
    x->left = current;
    current->right = buffer;
    updateHeight(current);
    updateHeight(x);

    return x;
}

Node * rotateRight (Node * current)
{
    Node * x = current->left;
    Node * buffer = x->right;
    x->right = current;
    current->left = buffer;
    updateHeight(current);
    updateHeight(x);
    return x;
}


Node * insertInto (Node * root , Node * newNode)
{
    if (!root)
    {
        root = newNode;
        return root;
    }
    else if (newNode->data < root->data)
        root->left = insertInto(root->left , newNode);
    else if (newNode->data > root->data)
        root->right = insertInto(root->right , newNode);
    else return root;

    root->height = 1 + max(height(root->left) , height(root->right));

    int bf = balanceFactor(root);

    if (bf > 1) // left imbalance
    {
        if (balanceFactor(root->left) == 1) // left heavy
        {
            // ll rotation
            root = rotateRight(root);
        }
        else 
        {
            // lr rotation
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }
    }
    if (bf < -1) // right imbalance
    {
        if (balanceFactor(root->right) == -1) // right heavy
        {
            // rr rotation
            root = rotateLeft(root);
        }
        else 
        {
            // rl rotation
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }
    return root;

}

void levelRec(std::queue<Node *> main_queue)
{
    std::queue<Node *> aux_queue;
    while (!main_queue.empty())
    {
        std::cout << main_queue.front()->data << " ";
        if (main_queue.front()->left)
            aux_queue.push(main_queue.front()->left);
        if (main_queue.front()->right)
            aux_queue.push(main_queue.front()->right);
        main_queue.pop();
    }
    std::cout << std::endl;
    if (!aux_queue.empty())
        levelRec(aux_queue);
}
void levelOrderTraversal(Node *& root)
{
    std::queue<Node *> main_queue;
    main_queue.push(root);

    levelRec(main_queue);
}
int main()
{
    Node * root = nullptr;
    std::vector<int> dataset = {50,45,40,35,30,25,20,15,10};
    for (int value : dataset)
    {
        Node * newNode = new Node(value);
        root = insertInto(root , newNode);
    }

    levelOrderTraversal(root);
}
