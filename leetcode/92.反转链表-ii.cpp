/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] 反转链表 II
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
    ListNode *successor;
    ListNode* reverse_duigui(ListNode* head, int right) {
        if (right == 1) {
            successor = head->next;
            return head;
        }

        ListNode *last = reverse_duigui(head->next, right-1);
        head->next->next =  head;
        head->next = successor;
        return last;
    }

    ListNode* reverse_diedai(ListNode* head, int right) {
        ListNode *ptr, *front, *back;
        ptr = front = head;
        back = nullptr;
        while ((right--) != 0)
        {
            ptr = ptr->next;
            front->next = back;

            back = front;
            front = ptr;
        }
        head->next = ptr;
        return back;
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == 1)
        {
            // return reverse_diedai(head, right);
            return reverse_duigui(head, right);
        }
        head->next = reverseBetween(head->next, left-1, right-1);
        return head;
        
        // ListNode *ptrf, *ptr, *front, *back;
        // if (left == 1)
        // {
        //     return reverse(head, right);
        // }
        
        // ptrf = head;
        // while ((left--)!=2)
        // {   
        //     ptrf = ptrf->next;
        //     right--;
        // }

        // ptr = front = ptrf->next;
        // back = ptrf;
        // while ((right--) != 0)
        // {
        //     ptr = ptr->next;
        //     front->next = back;

        //     back = front;
        //     front = ptr;            
        // }
        // ptrf->next->next = ptr;
        // ptr->next = back;
        // return head;
    }
};
// @lc code=end

