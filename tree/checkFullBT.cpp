#include <iostream>
#include <algorithm>
using namespace std;

class FullBT
{
private:
    typedef struct Node {
        int data;
        Node *left;
        Node *right;
        Node (int d, Node *l=nullptr, Node *r=nullptr) :data(d), left(l), right(r) {}
    }Node;
    Node *root;
    typedef struct Info {
        int height;
        int nodes;
        Info(int h, int n):height(h), nodes(n) {}
    }Info;
public:
    FullBT() { root = nullptr; }
    FullBT(int val) {root = new Node(val);}

    //call isFull method
    bool checkFBT() {
        if (root == nullptr) return true;
        
        //满二叉树的节点个数等于2^height - 1，1左移height为表示2的n次方
        Info *allInfo = isFull();
        return allInfo->nodes == (1 << allInfo->height -1);
    }

    Info* isFull() {
        isFull(root);
    }

    Info* isFull(Node *head) {
        if(head == nullptr) return new Info(0, 0);
        Info *leftInfo = isFull(head->left);
        Info *rightInfo = isFull(head->right);
        int curHeight = max(leftInfo->height, rightInfo->height) + 1;
        int curNum = leftInfo->nodes + rightInfo->nodes + 1;

        return new Info(curHeight, curNum);
    }
};


