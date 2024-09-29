#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <deque>

using namespace std;

class TreeNode
{
public:
    int payload = 0;
    TreeNode * left;
    TreeNode * right;
 
TreeNode()
{
    payload = 0;
    left = nullptr;
    right = nullptr;
}
TreeNode (int value)
{
    payload = value;
    left = nullptr; 
    right = nullptr;
}
};

// for doing level order traversal we are supposed to use a queue
// for breadth first (level order) algorithms , we should use a queue
// for depth first algorithms(inorder , preorder , postorder) we should use a stack 


void levelOrder(TreeNode * root)
{
    if (!root) return;
    std::queue<TreeNode *> main_queue;
    main_queue.push(root);
    while (!main_queue.empty())
    {
        std::cout << main_queue.front()->payload << " ";
        if (main_queue.front()->left)
            main_queue.push(main_queue.front()->left);
        if (main_queue.front()->right)
            main_queue.push(main_queue.front()->right);
        main_queue.pop();
    }
}

int height(TreeNode * current)
{
    if (!current) 
        return 0;
    int leftLength = height(current->left);
    int rightLength = height(current->right);
    return max(leftLength ,rightLength) + 1;// the +1 is to account for the current node
    // to get the height without recursion , we could use level order traversal 
}
int maxOf(int first ,int second , int third)
{
    if (first >= second && first >= third)
        return first;
    else if (second >= first && second >= third)
        return second;
    else 
        return third;
}

int diameterOfBinaryTree(TreeNode* root) 
{
    if (!root) return 0;

    int leftLength = height(root->left);
    int rightLength = height(root->right);

    int currentDiameter = leftLength + rightLength;
      
    int leftDiameter = diameterOfBinaryTree(root->left);
    int rightDiameter = diameterOfBinaryTree(root->right);

    return maxOf(leftDiameter , rightDiameter , currentDiameter);  
}


TreeNode * mirror (TreeNode * root)
{
    if (!root) return nullptr;
    // calling the mirror() recursively for the left and right sub tree
    mirror(root->left);
    mirror(root->right);
    // Swapping the left and the right children
    TreeNode * buffer = root->left;
    root->left = root->right;
    root->right = buffer;
    return root;
}


void reverseLevelOrder_recursion(queue<TreeNode *>& main_q , stack<vector<int>>& s)
{
    std::queue<TreeNode *> aux_q;
    std::vector<int> buffer;
    while (!main_q.empty())
    {
        buffer.push_back(main_q.front()->payload);
        if (main_q.front()->left)
            aux_q.push(main_q.front()->left);
        if (main_q.front()->right)
            aux_q.push(main_q.front()->right);
        main_q.pop();
    }
    s.push(buffer);
    if (!aux_q.empty())
        reverseLevelOrder_recursion(aux_q , s);
}

void reverseLevelOrder(TreeNode * root)
{
    if (!root) return;
    std::queue<TreeNode *> q;
    q.push(root);
    std::stack<std::vector<int>> s;
    reverseLevelOrder_recursion(q , s);
    while (!s.empty())
    {
        for (int current : s.top())
            std::cout << current << " ";
        std::cout << endl;
        s.pop(); 
    }
}


void inOrderTraversal(TreeNode *& current)
{
    // inorder : left , root , right
    if (!current) return; 
    inOrderTraversal(current->left);
    std::cout << current->payload << " ";
    inOrderTraversal(current->right);
}

void preOrderTraversal(TreeNode *& current)
{
    // pre order : root , left , right
    if (!current) return;
    std::cout << current->payload << " ";
    preOrderTraversal(current->left);
    preOrderTraversal(current->right);
}

void postOrderTraversal(TreeNode *& current)
{
    // post order : left , right , root
    if (!current) return;
    postOrderTraversal(current->left);
    postOrderTraversal(current->right);
    std::cout << current->payload << " ";
}

void bfs_recursion(std::queue<TreeNode*> q , vector<vector<int>>& result)
{
    std::vector<int> buffer;
    std::queue<TreeNode *> aux_q;
    while (!q.empty())
    {
        buffer.push_back(q.front()->payload);
        if (q.front()->left)
            aux_q.push(q.front()->left);
        if (q.front()->right)
            aux_q.push(q.front()->right);
        q.pop();
    }
    result.push_back(buffer);
    if (!aux_q.empty())
        bfs_recursion(aux_q , result);

}

std::vector<std::vector<int>> bfs(TreeNode *& root)
{
    std::vector<std::vector<int>> result;
    if (!root) return result;
    std::queue<TreeNode *> q;
    q.push(root);
    bfs_recursion(q , result);
    return result;
}


// for the right side view and the left side view , we would make use of the dfs algorithm

void rightSideView(TreeNode *& root)
{
    std::vector<std::vector<int>> bfs_result = bfs(root);
    for (std::vector<int> buffer : bfs_result)
        std::cout << buffer[buffer.size() - 1] << std::endl;
}

void leftSideView(TreeNode *& root)
{
    std::vector<std::vector<int>> bfs_result = bfs(root);
    for(std::vector<int> buffer : bfs_result)
        std::cout << buffer[0] << std::endl;
}

bool isSameTree(TreeNode *& root1 , TreeNode *& root2)
{
    if (!root1 && !root2) // return true if both of them are null 
        return true;
    if (!root1 || !root2) // this means that one of them is null, return false
        return false;
    
    if (root1->payload != root2->payload) // unequal values , return false
        return false;
    else // check and return the result for the left sub tree and right sub tree
        return isSameTree(root1->left , root2->left) && isSameTree(root1->right , root2->right);
}

bool isMirror(TreeNode * root1 , TreeNode * root2)
{
    if (!root1 && !root2)
        return true;
    if (!root1 || !root2) 
        return false;
    if (root1->payload != root2->payload)
        return false;
    else 
        return isMirror(root1->left , root2->right) && isMirror(root1->right , root2->left); 
}

void bfs_recursion_bV(queue<pair<TreeNode*,int>>&main_queue , vector<vector<pair<int,int>>>& results)
  {
      queue<pair<TreeNode * , int>> aux_queue;
      std::vector<pair<int , int>> buffer;
      while (!main_queue.empty())
      {
          buffer.push_back({main_queue.front().first->payload , main_queue.front().second});
          if (main_queue.front().first->left)
            aux_queue.push({main_queue.front().first->left , main_queue.front().second - 1});
          if (main_queue.front().first->right)
            aux_queue.push({main_queue.front().first->right , main_queue.front().second + 1});
          main_queue.pop();
      }
      results.push_back(buffer);
      if (!aux_queue.empty())
        bfs_recursion_bV(aux_queue , results);
  }

vector<vector<pair<int , int>>> bfs_modified_bottomView (TreeNode * root)
{
      vector<vector<pair<int ,int >>> results;
      queue<pair<TreeNode * , int>> main_queue;
      main_queue.push({root , 0});
      
      bfs_recursion_bV (main_queue , results);
      
      return results;
}

void diagonalTraversal(TreeNode * root)
{
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        TreeNode * current_node = q.front();
        while(current_node)
        {
            std::cout << current_node->payload << " ";
            if (current_node->left)
                q.push(current_node->left);
            current_node = current_node->right;
        }
        q.pop();
    }
}


void bottomView(TreeNode * root)
{
    // if there are nodes which have the same bottom relative index 
    // just print the node which comes the LAST in level order 
    // and ignore the rest of the nodes
    vector<vector<pair<int , int>>> temp = bfs_modified_bottomView (root);
    std::map <int , int> helper_map; 
        for (int i = temp.size() - 1 ; i >= 0 ; i--)
        {
            vector<pair<int , int>> current_vector = temp[i];
            for (int i = current_vector.size() - 1 ; i >= 0 ; i--)
            {
                if (helper_map.find(current_vector[i].second) == helper_map.end())
                    helper_map[current_vector[i].second] = current_vector[i].first;
            }
        }
        for (auto itr : helper_map)
            std::cout << itr.second << " ";
}

bool isBalancedTree(TreeNode * root)
{
    if (!root) return true;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    int delta = abs(leftHeight - rightHeight);

    return ((delta <= 1) && (isBalancedTree(root->left)) && (isBalancedTree(root->right)));
}


vector<vector<int>> zigZag(TreeNode * root)
{
    vector<vector<int>> result = bfs(root);
    for (int i = 1 ; i < result.size() ; i++)
    {
        // reverse every odd leveled vector
        if (i%2 != 0) 
        {
            std::vector<int> buffer;
            for (int j = result[i].size() - 1 ; j >= 0; j--)
                buffer.push_back(result[i][j]);
            result[i] = buffer;
        }
    }
    return result;
}

void topView(TreeNode * root)
{
    std::map <int , int> helper_map; // stores the relative index and the value
    std::queue<std::pair<TreeNode * , int>> main_queue;
    // the pair is as follows : <the node itself , the relative index of the node >
    main_queue.push({root , 0});
    while (!main_queue.empty())
    {
        if (helper_map.find(main_queue.front().second) == helper_map.end())
            helper_map[main_queue.front().second] = main_queue.front().first->payload;
        if (main_queue.front().first->left)
            main_queue.push({main_queue.front().first->left , main_queue.front().second - 1});
        if (main_queue.front().first->right)
            main_queue.push({main_queue.front().first->right , main_queue.front().second + 1});
        main_queue.pop();
    }
    for (auto node : helper_map)
        std::cout << node.second << " ";
}


void inOrderTraversal_iterative(TreeNode * root)
{
    TreeNode * current = root;
    stack<TreeNode *> s;
    while (true)
    {
        if (current)
        {
            s.push(current);
            current = current->left;
        }
        else 
        {
            if (s.empty()) break;
            current = s.top();
            s.pop();
            std::cout << current->payload << " ";
            current = current->right;
        }
    }
}

int main()
{
    /* this is the supposed strcuture for the tree
                4
            3       7
          1   8   5   2            
     */

    TreeNode * n00 = new TreeNode(4);
    TreeNode * n10 = new TreeNode(3);
    TreeNode * n11 = new TreeNode(7);
    TreeNode * n21 = new TreeNode(1);
    TreeNode * n22 = new TreeNode(8);
    TreeNode * n23 = new TreeNode(5);
    TreeNode * n24 = new TreeNode(2);
    
    n00->left = n10;
    n00->right = n11;
    n10->left = n21;
    n10->right = n22;
    n11->left = n23;
    n11->right = n24;

    TreeNode * root = n00;
    inOrderTraversal(root);
    inOrderTraversal_iterative(root);
    
}
