/*
 * @lc app=leetcode.cn id=110 lang=cpp
 *
 * [110] 平衡二叉树
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
#include <math.h>
class Solution {
public:
    typedef struct checkNode
    {
        bool isBT;
        int height;
        checkNode(bool ib, int h): isBT(ib), height(h) {}
    };
    
    bool isBalanced(TreeNode* root) {
        return helper(root)->isBT;
    }

    checkNode* helper(TreeNode *root) {
        if (root == nullptr)
        {
            return new checkNode(true, 0);
        }
        checkNode *leftIsBT = helper(root->left);
        checkNode *rightIsBT = helper(root->right);

        //当前子树的高度是左右子树高度的最大值+1
        int curHeight = max(leftIsBT->height, rightIsBT->height) + 1;
        //左子树和右子树必须都是平衡二叉树，并且左右子树的高度差小于等于1
        bool curIsBT =  leftIsBT->isBT && rightIsBT->isBT && abs(leftIsBT->height - rightIsBT->height) <= 1;
        return new checkNode(curIsBT, curHeight)
    }
};
// @lc code=end

