/*
 * @lc app=leetcode.cn id=958 lang=cpp
 *
 * [958] 二叉树的完全性检验
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
class Solution {
public:
    //二叉树层序遍历框架，在弹出一个节点时，对其左右孩子进行判断
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr) return true;
        queue<TreeNode*> que;
        TreeNode *tmp, *l, *r;
        bool isLeaf = false;

        que.push(root);
        while (!que.empty())
        {
            tmp = que.front();
            que.pop();
            l = tmp->left;
            r = tmp->right;
            if (
                //如果左子树为空，且右子树不为空，返回false
                (l == nullptr && r != nullptr)
                ||
                //如果遇到过叶子结点，但自身节点却有孩子（有左无右或者左右都有，无左有右的情况上一个条件已经包括）
                (isLeaf && (l != nullptr || r != nullptr)) 
            )
            {
                return false;
            }
            if (l) que.push(l);
            if (r) que.push(r);
            //如果左右孩子不双全，将叶子结点标志设为true
            //有左无右，无左无右，不包括无左有右的情况，这种情况上面if中已经做了判断
            if (l == nullptr || r == nullptr)
            {
                isLeaf = true;
            }
        }
        return true;
    }
};
// @lc code=end

