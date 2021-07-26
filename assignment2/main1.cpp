/*
 * @Author       : Hao Zhang
 * @Date         : 2021-05-07 10:06:28
 * @LastEditors  : Hao Zhang
 * @LastEditTime : 2021-05-07 10:07:56
 * @FilePath     : \assignment2\main1.cpp
 */
/*
 * @Author       : Hao Zhang
 * @Date         : 2021-05-06 17:55:21
 * @LastEditors  : Hao Zhang
 * @LastEditTime : 2021-05-07 10:06:54
 * @FilePath     : \assignment2\main.cpp
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <iterator>
#include <algorithm>
#include <fstream>
using namespace std;

class Node
{
private:
public:
    Node();
    Node(int value);
    Node *parent;
    Node *parent_right;
    Node *left;
    Node *right;
    int value;
    int hl;
    int hr;
    int height;
    ~Node();
};

Node::Node()
{
    value = -1;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    parent_right = nullptr;
    hl = 0;
    hr = 0;
    height = 1;
}

Node::Node(int p_value)
{
    value = p_value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    parent_right = nullptr;
    hl = 0;
    hr = 0;
    height = 1;
}

Node::~Node()
{
}

int get_height(Node *N)
{
    if (N != NULL)
        return N->height;
    return 0;
}

// Node *rightRotate(Node *y) 
// { 
//     Node *x = y->left; 
//     Node *T2 = x->right; 
  
//     // Perform rotation 
//     x->right = y; 
//     y->left = T2; 
  
//     // Update heights 
//     y->height = max(height(y->left), 
//                     height(y->right)) + 1; 
//     x->height = max(height(x->left), 
//                     height(x->right)) + 1; 
  
//     // Return new root 
//     return x; 
// } 

Node *rightRotate(Node *node)
{
    Node *left_node;
    Node *leftRight_node;
    left_node = node->left;
    leftRight_node = left_node->right;
    left_node->right = node;
    node->left = leftRight_node;

    node->height = max(get_height(node->left), get_height(node->right)) + 1; 
    left_node->height = max(get_height(left_node->left), get_height(left_node->right)) + 1; 

    return left_node;
}

// Node *leftRotate(Node *x) 
// { 
//     Node *y = x->right; 
//     Node *T2 = y->left; 
  
//     // Perform rotation 
//     y->left = x; 
//     x->right = T2; 
  
//     // Update heights 
//     x->height = max(height(x->left), 
//                     height(x->right)) + 1; 
//     y->height = max(height(y->left), 
//                     height(y->right)) + 1; 
  
//     // Return new root 
//     return y; 
// } 

Node *leftRotate(Node *node)
{
    Node *right_node;
    Node *rightleft_node;
    right_node = node->right;
    rightleft_node = right_node->left;
    right_node->left = node;
    node->right = rightleft_node;

    if (node->left == NULL && node->right == NULL)
    {
        node->height = 1;
    }
    else if (node->left == NULL)
    {
        node->height = node->right->height + 1;
    }
    else if (node->right == NULL)
    {
        node->height = node->left->height + 1;
    }
    else
    {
        node->height = max(node->left->height, node->right->height) + 1;
    }

    if (right_node->left == NULL && right_node->right == NULL)
    {
        right_node->height = 1;
    }
    else if (right_node->left == NULL)
    {
        right_node->height = right_node->right->height + 1;
    }
    else if (right_node->right == NULL)
    {
        right_node->height = right_node->left->height + 1;
    }
    else
    {
        right_node->height = max(right_node->left->height, right_node->right->height) + 1;
    }
    return right_node;
}

// int getBalance(Node *N) 
// { 
//     if (N != NULL) 
//         return get_height(N->left) - get_height(N->right); 
//     return 0; 
// } 

int getBalance(Node *N)
{
    int left;
    int right;
    if (N->left == NULL)
    {
        left = 0;
    }
    else
    {
        left = N->left->height;
    }

    if (N->right == NULL)
    {
        right = 0;
    }
    else
    {
        right = N->right->height;
    }
    return left - right;
}

// Node* addNode(Node* node, int value) 
// { 
//     /* 1. Perform the normal BST rotation */
//     Node * n = new Node(value);
//     if (node == NULL) 
//         return(n); 
  
//     if (value < node->value) 
//         node->left = addNode(node->left, value); 
//     else if (value > node->value) 
//         node->right = addNode(node->right, value); 
//     else // Equal values not allowed 
//         return node; 
  
//     /* 2. Update height of this ancestor node */
//     node->height = 1 + max(get_height(node->left), get_height(node->right)); 
  
//     /* 3. Get the balance factor of this 
//         ancestor node to check whether 
//         this node became unbalanced */
//     int balance = getBalance(node); 
  
//     // If this node becomes unbalanced,
//     // then there are 4 cases 
  
//     // Left Left Case 
//     if (balance > 1 && value < node->left->value) 
//         return rightRotate(node); 
  
//     // Right Right Case 
//     if (balance < -1 && value > node->right->value) 
//         return leftRotate(node); 
  
//     // Left Right Case 
//     if (balance > 1 && value > node->left->value) 
//     { 
//         node->left = leftRotate(node->left); 
//         return rightRotate(node); 
//     } 
  
//     // Right Left Case 
//     if (balance < -1 && value < node->right->value) 
//     { 
//         node->right = rightRotate(node->right); 
//         return leftRotate(node); 
//     } 
  
//     /* return the (unchanged) node pointer */
//     return node; 
// } 

Node *addNode(Node *node, int value)
{
    Node *n = new Node(value);
    if (node == NULL)
        return (n);

    if (value < node->value)
        node->left = addNode(node->left, value);
    else if (value > node->value)
        node->right = addNode(node->right, value);
    else
        return node;

    int left;
    int right;
    if (node->left == NULL)
    {
        left = 0;
    }
    else
    {
        left = node->left->height;
    }

    if (node->right == NULL)
    {
        right = 0;
    }
    else
    {
        right = node->right->height;
    }
    node->height = 1 + max(left, right);

    int balance = getBalance(node);

    if (balance > 1)
    {
        if (value < node->left->value)
        {
            return rightRotate(node);
        }
        if (value > node->left->value)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balance < -1)
    {
        if (value > node->right->value)
        {
            return leftRotate(node);
        }
        if (value < node->right->value)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

Node *leftMax(Node *node)
{
    Node *current = node;
    while (current->right != NULL)
        current = current->right;

    return current;
}

Node *deleteNode(Node *node, int value)
{
    if (node == NULL)
        return node;
    if (value < node->value)
    {
        node->left = deleteNode(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = deleteNode(node->right, value);
    }
    else
    {
        if (node->left == NULL || node->right == NULL)
        {
            if (node->left == NULL && node->right == NULL)
            {
                node = NULL;
            }
            else if (node->left == NULL)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }
        else
        {
            Node *temp = leftMax(node->left);
            node->value = temp->value;
            node->left = deleteNode(node->left, temp->value);
        }
    }

    if (node == NULL)
    {
        return node;
    }

    if (node->left == NULL && node->right == NULL)
    {
        node->height = 1;
    }
    else if (node->left == NULL)
    {
        node->height = node->right->height + 1;
    }
    else if (node->right == NULL)
    {
        node->height = node->left->height + 1;
    }
    else
    {
        node->height = max(node->left->height, node->right->height) + 1;
    }

    int balance = getBalance(node);

    if (balance > 1)
    {
        if (getBalance(node->left) >= 0)
        {
            return rightRotate(node);
        }
        if (getBalance(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balance < -1)
    {
        if (getBalance(node->right) <= 0)
        {
            return leftRotate(node);
        }
        if (getBalance(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

void preOrder(Node *root)
{
    if (root != NULL)
    {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *node)
{
    if (node != NULL)
    {
        inOrder(node->left);
        cout << node->value << " ";
        inOrder(node->right);
    }
}

void postOrder(Node* node){
	if(node!= NULL){
		postOrder(node->left);
		postOrder(node->right);
		cout << node->value << " ";
	}  
}

int main()
{

    Node *root = NULL;
    string input;
    int number;
    bool flag = true;

    string out_type = " ";
    while (flag)
    {
        cin >> input;
        if (input[0] == 'P' || input[0] == 'I')
        {
            if (input == "PRE")
            {
                if (root == NULL)
                {
                    cout << "EMPTY";
                    break;
                }
                else
                {
                    preOrder(root);
                    break;
                }
                flag = false;
            }
            else if (input == "IN")
            {
                if (root == NULL)
                {
                    cout << "EMPTY";
                    break;
                }
                else
                {
                    inOrder(root);
                    break;
                }
                flag = false;
            }
            else if (input == "POST" )
            {
                if (root == NULL)
                {
                    cout << "EMPTY";
                    break;
                }
                else
                {
                    postOrder(root);
                    break;
                }
                flag = false;
            }
        }

        if (input[0] == 'A')
        {
            number = stoi(input.substr(1));
            root = addNode(root, number);
        }
        else if (input[0] == 'D')
        {
            number = stoi(input.substr(1));
            root = deleteNode(root, number);
        }
    }
    return 0;
}
