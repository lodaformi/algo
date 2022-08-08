#include <iostream>
#include <limits.h>
#include <algorithm>
#include <stack>
using namespace std;

/*
判断一个二叉树是否是搜索二叉树
严格的搜索二叉树是左小右大，中序遍历是递增序列
*/


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

    //方法二：中序遍历(迭代)
    bool checkBST2(Node* head) {
        if (head == nullptr)
        {
            return true;
        }
        Node *tmp = head;
        int preData = INT_MIN;
        stack<int> st;
        while (!st.empty() || tmp != nullptr )
        {
            //左边界入栈，只至为空  
            if (tmp != nullptr)
            {
                st.push(tmp);
                tmp = tmp->left;
            } else {            
                //左边界走完后，弹出栈顶元素，弹出的同时将该元素的右孩子入栈
                //如果没有右孩子（右孩子为nullptr），则继续弹出
                //如果右孩子不为nullptr，则右孩子入栈，将右孩子的左边界一直入栈
                tmp = st.top();
                st.pop();
                if (preData >= tmp->data)
                {
                    return false;
                }else {
                    preData = tmp->data;
                }
                tmp = tmp->right;
            }
        }
        return true;
    }


    //方法三
    //使用二叉树框架
    //因为要返回三个值，所以使用一个结构体封装
    typedef struct checkNode
    {
        bool isBST;
        int min;
        int max;
        checkNode(bool ib=false, int mi=INT_MIN, int ma=INT_MAX):isBST(ib), min(mi), max(ma) {}
    }checkNode;

    //后序遍历框架
    checkNode* checkBST3(Node* head) {
        if (head == nullptr)
        {
            return nullptr;
        }
        checkNode* leftIsBST = checkBST2(head->left);
        checkNode* rightIsBST = checkBST2(head->right);
        //先把最小值和最大值设为自己，因为当一个节点没有左右子树的时候，最大值和最小值都是自己
        int mi = head->data;
        int ma = head->data;
        //记过比较后，最小值和最大值存放的就是是这个子树的最小值和最大值
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
        //左子树在不为空的情况下，左子树不是BST 或者 左子树的最大值大于等于当前节点值，设置为false
        if (leftIsBST != nullptr && (!leftIsBST->isBST || leftIsBST->max >= head->data))
        {
            isBST = false;
        }
        //右子树在不为空的情况下，右子树不是BST 或者 右子树的最小值小于等于当前节点值，设置为false
        if (rightIsBST != nullptr && (!rightIsBST->isBST || rightIsBST->min <= head->data))
        {
            isBST = false;
        }
        //返回当前子树的结果
        return new checkNode(isBST, min, max);
    }
    //调用
    void call_checkBST() {
        checkBST(root);
        checkBST2(root);
        checkBST3(root);
    }
};


int main() {


    system("pause");
    return 0;
}