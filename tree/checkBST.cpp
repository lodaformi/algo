#include <iostream>
#include <limits.h>
#include <algorithm>
using namespace std;

//严格的搜索二叉树是左小右大，中序遍历是递增序列
class bTree
{
private:
    typedef struct Node {
        int data;
        Node *left;
        Node *right;
        Node(int d, Node *l=nullptr, Node *r=nullptr):data(d), left(l), right(r) {}
        Node(Node *l=nullptr, Node *r = nullptr): left(l), right(r) {} 
    }Node;
    Node *root;
public:
    
    bTree() {root=nullptr;}
    bTree(int d) {
        root = new Node(d);
    }
    ~bTree() {}

    bool checkBST() {
        return checkBST(root);
    }

    static int previousData = INT_MIN;
    bool checkBST(Node *head) {
        if (head == nullptr)
        {
            return true;
        }
        
        bool leftIsBst = checkBST(head->left);
        if (!leftIsBst)
        {   
            return false;
        }

        if (previousData >= head->data)
        {
            return false;
        } else {
            previousData = head->data;
        }

        return rightIsBst = checkBST(head->right);
    }

    //方法二
    //使用二叉树框架
    typedef struct checkNode
    {
        bool isBST;
        int min;
        int max;
        checkNode(bool ib=false, int mi=INT_MIN, int ma=INT_MAX):isBST(ib), min(mi), max(ma) {}
    }checkNode;

    checkNode* checkBST2(Node* head) {
        if (head == nullptr)
        {
            return nullptr;
        }
        checkNode* leftIsBST = checkBST2(head->left);
        checkNode* rightIsBST = checkBST2(head->right);
        //
        int mi = head->data;
        int ma = head->data;
        if (leftIsBST != nullptr)
        {
            mi = min(leftIsBST->min, mi);
            ma = max(leftIsBST->max, ma);
        }
        if (rightIsBST != nullptr)
        {
            mi = min(rightIsBST->min, mi);
            ma = max(rightIsBST->max, ma);
        }
        
        bool isBST = true;
        if (leftIsBST != nullptr && (!leftIsBST->isBST || leftIsBST->max >= head->data))
        {
            isBST = false;
        }
        if (rightIsBST != nullptr && (!rightIsBST->isBST || rightIsBST->min <= head->data))
        {
            isBST = false;
        }
        return new checkNode(isBST, min, max);
    }
    //调用
    void call_checkBST2() {
        checkBST2(root);
    }
};








int main() {


    system("pause");
    return 0;
}