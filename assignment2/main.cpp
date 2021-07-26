/*
 * @Author       : Hao Zhang
 * @Date         : 2021-05-06 17:55:21
 * @LastEditors  : Hao Zhang
 * @LastEditTime : 2021-05-19 16:24:14
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
    int height;
    ~Node();
};

Node::Node()
{
    value = -1;
    left = nullptr;
    right = nullptr;
    height = 1;
}

Node::Node(int p_value)
{
    value = p_value;
    left = nullptr;
    right = nullptr;
    height = 1;
}

Node::~Node()
{
}

int get_height(Node *N) //to check if node is existing. height = 0 for NULL ptr
{
    if (N != NULL)
        return N->height;
    return 0;
}
//height = 1+ max(left, right)
void count_height(Node *node)
{
    node->height = 1 + max(get_height(node->left), get_height(node->right));
}

Node *rightRotate(Node *node)
{
    Node *left_node;
    Node *leftRight_node;
    left_node = node->left;
    leftRight_node = left_node->right;
    left_node->right = node;
    node->left = leftRight_node;

    count_height(node);
    count_height(left_node);

    return left_node;
}

Node *leftRotate(Node *node)
{
    Node *right_node;
    Node *rightleft_node;
    right_node = node->right;
    rightleft_node = right_node->left;
    right_node->left = node;
    node->right = rightleft_node;

    count_height(node);
    count_height(right_node);
    return right_node;
}

//left - right
int getBalance(Node *N)
{
    return get_height(N->left) - get_height(N->right);
}

Node *addNode(Node *node, int value)
{
    //recursion to set node
    if (node == NULL)
    {
        Node *n = new Node(value);
        return (n);
    }
    if (value < node->value)
        node->left = addNode(node->left, value);
    else if (value > node->value)
        node->right = addNode(node->right, value);
    else//== node->value
        return node;


    count_height(node);

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
// when a top of a node is deleted, we need to reconbine with the max node on the left
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
        //check if have child
        if (node->left == NULL || node->right == NULL)
        {
            if (node->left == NULL && node->right == NULL)//no children
            {
                node = NULL;
            }
            //one child
            else if (node->left == NULL)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }
        else// have two children
        {
            Node *temp = leftMax(node->left);
            node->value = temp->value;
            node->left = deleteNode(node->left, temp->value);
        }
    }

    count_height(node);

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

void preOrder(Node *root)//top left right
{
    if (root != NULL)
    {
        cout << root->value << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node *node)//left top right
{
    if (node != NULL)
    {
        inOrder(node->left);
        cout << node->value << " ";
        inOrder(node->right);
    }
}

void postOrder(Node *node)//left right top
{
    if (node != NULL)
    {
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
            else if (input == "POST")
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
