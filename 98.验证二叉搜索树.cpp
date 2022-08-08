/*
 * @lc app=leetcode.cn id=98 lang=cpp
 *
 * [98] 验证二叉搜索树
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <limits.h>
#include <stack>
#include <algorithm>
class Solution {
public:
    //方法一：中序遍历递归框架
    // static int preData = INT_MIN; 不能在类中定义static变量
    // int preData = INT_MIN;  
    //坑：-2147483648是INT_MIN int型最小值，测试用例中用-2147483648作比较，就会进入preData >= root->val的判断
    //所有这里使用long数据类型，在做比较时，int会提升为long
    long preData = LONG_MIN;
    bool isValidBST1(TreeNode* root) {
        if (root == nullptr) return true;
        bool leftIsBST = isValidBST(root->left);
        if (!leftIsBST)
        {
            return false;
        } 
        if (preData >= root->val)
        {
            return false;
        } else {
            preData = root->val;
        }
        return isValidBST(root->right);
    }

    //方法二：中序遍历迭代框架
    bool isValidBST2(TreeNode* root) {
        if(root == nullptr) return true;
        stack<TreeNode*> st;
        
        long preData = LONG_MIN;

        TreeNode *tmp = root;
        while (!st.empty() || tmp != nullptr)
        {
            if (tmp != nullptr)
            {
                st.push(tmp);
                tmp = tmp->left;
            } else {
                tmp = st.top();
                st.pop();
                if (preData >= tmp->val)
                {
                    return false;
                } else {
                    preData = tmp->val;
                }
                tmp = tmp->right;
            }
        }
        return true;        
    }

    typedef struct checkNode
    {
        bool isBST;
        int mi;
        int ma;
        checkNode(bool ib, int m, int n) :isBST(ib), mi(m), ma(n) {}
    }checkNode;
    
    checkNode* helper(TreeNode* root) {
        if (root == nullptr) return nullptr;

        checkNode *leftIsBST = helper(root->left);
        checkNode *rightIsBST = helper(root->right);
        int mi = root->val;
        int ma = root->val;
        if (leftIsBST != nullptr)
        {
            mi = min(leftIsBST->mi, mi);
            ma = max(leftIsBST->ma, ma);
        }
        if (rightIsBST != nullptr)
        {
            mi = min(rightIsBST->mi, mi);
            ma = max(rightIsBST->ma, ma);
        }
        bool curIsBST = true;
        if (leftIsBST != nullptr && (!leftIsBST->isBST || leftIsBST->ma >= root->val))
        {
            curIsBST = false;
        }
        if (rightIsBST != nullptr && (!rightIsBST->isBST || rightIsBST->mi <= root->val))
        {
            curIsBST = false;
        }
        return new checkNode(curIsBST, mi, ma);
    }

    bool isValidBST(TreeNode* root) {
        return helper(root)->isBST;
    }

};
// @lc code=end

