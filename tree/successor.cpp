/*
time : 20220809
*/

#include <iostream>
using namespace std;

typedef struct Node
{
    int data;
    Node *left;
    Node *right;
    Node *parent;
    Node(int d):data(d), left(nullptr), right(nullptr), parent(nullptr) {}
}Node;

Node *getSuccessorNode(Node *head) {
    if (head == nullptr) return head;

    //如果有右子树，则后继节点是右子树最左边的节点
    if (head->right != nullptr)
    {
        return getLeftMost(head->right);
    } else {    //无右子树
        Node *curParent = head->parent;
        //如果父节点不为空，且该节点不是父节点的左节点，则上移一个节点，父节点同时上移
        //如果父节点为空了，说明找到了根节点，这个节点是整个树的最后边节点，返回空即可
        //如果该节点是父节点的左孩子，则返回当前的父节点
        while (curParent != nullptr && curParent->left != head)
        {
            head = curParent;
            curParent = head->parent;
        }
        return curParent;
    }
}

Node *getLeftMost(Node *head) {
    while (head->left != nullptr)
    {
        head = head->left;
    }
    return head;
}
