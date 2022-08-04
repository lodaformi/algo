/*
 * @lc app=leetcode.cn id=206 lang=cpp
 *
 * [206] 反转链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    //递归
    ListNode* reverseList_digui(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        
        ListNode* last = reverseList_digui(head->next);
        head->next->next = head;
        head->next = nullptr;
        return last;
    }

    //迭代
    ListNode* reverseList(ListNode* head) {
        //ptr 指针遍历整个链表
        //front 指向一个节点，可以更改这个节点的原有指向
        //back 指向front节点的后一个节点，等ptr遍历完整个链表，链表就逆序了
        ListNode* ptr, *front, *back;
        ptr = front = head;
        back = nullptr;
        while (ptr)   //ptr != nullptr
        {
            ptr = ptr->next;
            front->next = back;  //更改这个节点的指向
            back = front;       //back移动到front位置
            front = ptr;        //front移动到ptr位置
        }
        
        return back;
    }


    
};
// @lc code=end

