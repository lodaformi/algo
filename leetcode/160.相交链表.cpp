/*
 * @lc app=leetcode.cn id=160 lang=cpp
 *
 * [160] 相交链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
       ListNode *ptrA=headA, *ptrB=headB;
        while (ptrA != ptrB)
        {
            //这样写，会把空指针也当成一个节点进行比较
            //问题不大，两个链表都加上了空指针节点
            if (ptrA != nullptr)
            {
                ptrA = ptrA->next;
            }else{
                ptrA = headB;
            }
            
            if (ptrB != nullptr)
            {
                ptrB = ptrB->next;
            } else {
                ptrB = headA;
            }

        //当两个链表没有交点时，一个链表移到nullptr时，指向另一个链表头
        //如此一直反复，会成死循环
            // ptrA = ptrA->next;
            // ptrB = ptrB->next;

            // if (ptrA == nullptr)
            // {
            //     ptrA = headB;
            // }
            
            // if (ptrB == nullptr)
            // {
            //     ptrB = headA;
            // }
        }
        return ptrA; 
    }
};
// @lc code=end

