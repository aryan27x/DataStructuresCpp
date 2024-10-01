#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*

For AVL Tree , every node in the BST should be balanced
~ balance factor (bf) = height(node->left) - height(node->right)
Node is said to be balanced when balance factor (bf) of node : 
bf = [-1 , 0 , 1] 
if bf =  0   -> truly balanced
if bf =  1   -> left heavy 
if bf = -1  -> right heavy  

if (bf > 1) -> left imbalance
->   if bf(left_child) ==  1 -> left heavy =>  LL Rotation
->   if bf(left_child) == -1 -> right heavy => LR rotation 

if (bf < -1) -> right imbalance
-> if bf(right_child) == -1 -> right heavy => RR Rotation
-> if bf(right_child) ==  1 -> left heavy  => RL Rotation

LL Rotation : i) rotateRight(node)
RR Rotation : i) rotateLeft(node)
LR Rotation : i) rotateLeft(node->left)   (ii) rotateRight(node)
RL Rotation : i) rotateRight(node->right) (ii) rotateLeft(node)

For deletion from AVL Tree , we would simply delete the node as we would normally 
in a BST and then repeat the process of updating the height and finding the balance
factor and then doing the above mentioned rotations as required

*/

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
        height = 1; // this is the extra param in node of avl tree
    }
};



// Helper Functions
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


/*
the update height function would work in both the cases of insertion and deletion
*/
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
    return x; // returning the new root node
}
Node * rotateRight (Node * current)
{
    Node * x = current->left;
    Node * buffer = x->right;
    x->right = current;
    current->left = buffer;
    updateHeight(current);
    updateHeight(x);
    return x; // returning the new root node
}


Node * insertInto (Node * root , Node * newNode)
{
    // first we normally insert the node as we would in a BST
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

    // while backtracking the recursive call , we do the following
    // update the height of the node
    updateHeight(root);
    // get the balance factor of the node
    int bf = balanceFactor(root);

    if (bf > 1) // left imbalance
    {
        if (balanceFactor(root->left) == 1) // left heavy
        {
            // ll rotation
            root = rotateRight(root);
        }
        else // right heavy 
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
        else // left heavy
        {
            // rl rotation
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }
    return root;

}



void levelOrderRecursion(std::queue<Node *> main_queue)
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
        levelOrderRecursion(aux_queue);
}
void levelOrderTraversal(Node *& root)
{
    std::queue<Node *> main_queue;
    main_queue.push(root);

    levelOrderRecursion(main_queue);
}

int children (Node *& current)
{
    if (!current->left && !current->right)
        return 0;
    else if (current->left && current->right)
        return 2;
    else 
        return 1;
}

// we could use either the findSuccessor or the findPredecessor method 
// as a helper function while removing a node with two children

Node * findSuccessor (Node *& root)
{
    Node * successor = root->right;
    while (successor->left)
        successor = successor->left;
    return successor;
}
Node * findPredecessor (Node *& root) 
{
    Node * predecessor = root->left;
    while (predecessor->right)
        predecessor = predecessor->right;
    return predecessor;
}

Node * deleteFromAVLTree(Node *& root , int value)
{
    if (!root) return root; // the value is not found
    if (root->data == value) // the value if found
    {
        switch(children(root))
        {
            case 0 :
            {
                Node * buffer = root;
                root = nullptr;
                delete buffer;
                break;
            }
            case 1 :
            {
                Node * buffer = root;
                if (root->left)
                    root = root->left;
                else 
                    root = root->right;
                delete buffer;
                break;
            }
            case 2 :
            {
                Node * successor = findSuccessor(root);
                int buffer_value = successor->data;
                root = deleteFromAVLTree(root , successor->data);
                root->data = buffer_value;
                break;
            }
        }
    }
    else if (value < root->data)
        deleteFromAVLTree(root->left , value);
    else 
        deleteFromAVLTree(root->right , value);

    updateHeight(root);
    int bf = balanceFactor(root);
    
    if (bf > 1) // left imbalance
    {
        if (balanceFactor(root->left) == 1) // left heavy
        {
            // ll rotation
            root = rotateRight(root);
        }
        else // right heavy 
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
        else // left heavy 
        {
            // rl rotation
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
    }
    return root;
}
void display (std::vector<int> & dataset)
{
    std::cout << "This is the dataset being used : " << std::endl;
    for (int value : dataset)
        std::cout << value << " ";
    std::cout << std::endl;
}
int main()
{
    Node * root = nullptr;
    std::vector<int> dataset = {50,45,40,35,30,25,20,15,10};

    display(dataset);
    for (int value : dataset)
    {
        Node * newNode = new Node(value);
        root = insertInto(root , newNode);
    }

    std::cout << "This is the initial state of the avl tree: " << std::endl;
    levelOrderTraversal(root);

    std::cout << "Deleting 30 from the avl tree : " << std::endl;
    root = deleteFromAVLTree(root , 30);

    std::cout << "this is the new state of the avl tree : " << std::endl;
    levelOrderTraversal(root);

    std::cout << "Deleting 45 from the avl tree : " << std::endl;
    root = deleteFromAVLTree(root , 45);

    std::cout << "This is the new state of the avl tree : " << std::endl;
    levelOrderTraversal(root);

    return 0;
}
