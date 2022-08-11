/*
 * @lc app=leetcode.cn id=236 lang=cpp
 *
 * [236] 二叉树的最近公共祖先
 */

// @lc code=start
/**
 * time : 20220809
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <unordered_map>
#include <unordered_set>
#include <hash_map>
#include <hash_set>
using namespace std;
class Solution {
public:
    TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
        //定义一个map，记录整棵树每个节点与父节点的对应关系，这样可以通过一个节点找到root节点
        unordered_map<TreeNode*, TreeNode*> fatherMap;
        //先把根节点自身加入到map中，根节点的父节点是自己，可以作为下面循环结束的判断条件
        fatherMap.emplace(pair<TreeNode*, TreeNode*>(root, root));
        //辅助函数，构建map
        helper(root, fatherMap);

        //定义一个set，记录p节点到root之间的父节点链
        unordered_set<TreeNode*> fatherSet;

        TreeNode *curNode = p;
        //通过循环将p节点到root之间的节点加入到set中
        while (curNode != fatherMap.at(curNode))
        {
            fatherSet.emplace(curNode);
            curNode = fatherMap.at(curNode);
        }
        //循环终止时，curNode指向了根节点，但是没有加入到set中，收到加入
        fatherSet.emplace(root);

        curNode = q;
        unordered_set<TreeNode*>::iterator iter;    //定义一个迭代器，用于接收find的结果
        //使用循环寻找q节点的父节点链上是否有在set中，如第一个找到有break
        while (curNode != fatherMap.at(curNode))
        {
            iter = fatherSet.find(curNode);
            //如果找到，则iter不等于fatherSet.end()
            if (iter != fatherSet.end())
            {
                curNode = *iter;
                break;
            }
            curNode = fatherMap.at(curNode);
        }
        //循环退出有两种情况，break出来的，和找到根节点了，两种情况均可将结果记录到curNode中
        return curNode;
    }

    void helper(TreeNode *head, unordered_map<TreeNode*, TreeNode*> &map) {
        if (head == nullptr)  return;
        map.emplace(pair<TreeNode*, TreeNode*>(head->left, head));
        map.emplace(pair<TreeNode*, TreeNode*>(head->right, head));        
        helper(head->left, map);
        helper(head->right, map);
    }

    //两个节点的分布情况有两类：
    //1：互为公共祖先
    //2：分属于不同的子树，在某一处相遇

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q)
        {
            return root;
        }
        //当p和q不在一个子树上时，这个子树返回的不是nullptr
        TreeNode *leftLCA = lowestCommonAncestor(root->left, p, q);
        TreeNode *rightLCA = lowestCommonAncestor(root->right, p, q);
        //属于第二种情况
        if (leftLCA != nullptr && rightLCA != nullptr)
        {
            return root;
        }
        //左边不为空返回左，左边为空时，不管右是不是空都返回右
        //三种情况：1.左不空 右空返回左 2.左空 右空返回右 3。左空 右不空返回右
        return leftLCA != nullptr ? leftLCA : rightLCA;        
    }

};
// @lc code=end

