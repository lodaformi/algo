/*
 * @lc app=leetcode.cn id=876 lang=cpp
 *
 * [876] 链表的中间结点
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
    ListNode* middleNode(ListNode* head) {
        if (head == nullptr) return head;
            
        ListNode *slow, *fast;
        slow = fast = head;

        //这样写，链表个数为奇数时，指向中心节点，fast指向最后一个节点
        //链表个数为偶数时，指向中心的后一个节点，fast指向nullptr
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;        

        //这样写，链表个数为奇数时，指向中心节点，fast指向最后一个节点
        //链表个数为偶数时，指向中心的前一个节点，fast不指向nullptr，注意两者的区别和题目的要求
        // while (fast->next != nullptr && fast->next->next != nullptr)
        // {
        //     slow = slow->next;
        //     fast = fast->next->next;
        // }
        
        // //如果是奇数情况，fast->next为nullptr
        // if (fast->next == nullptr)
        // {
        //     return slow;
        // } else {    
        //     //如果是偶数数情况，fast->next->next为nullptr
        //     //此时slow指向中间两个节点的前一个，题意要求是后一个节点，则slow移动后移一个
        //     return slow->next;
        // }        
    }
};
// @lc code=end

