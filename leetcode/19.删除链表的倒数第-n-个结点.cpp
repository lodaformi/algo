/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
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
//预备知识，倒数第k个节点，如果知道链表长度为N，则该节点为正数N-k+1
//例如链表有5个节点，倒数第2个节点，正数为第4个节点
//链表还要考虑最后节点指向nullptr的情况，nullptr可以看成一个特殊的节点
//当ptr1指针从第一个节点开始移动k步，第二次移到到nullptr时，移动的距离为N-k-1，以5个节点的链表为例，移动距离为3，不是4
//为了统一表示，在链表的前面在加上一个头结点，使头结点指向第一个节点

//使用双指针，指针1先前进k步，之后，指针1和指针2同时前进，
//指针1前进到nullptr时，前进了n-k步，此时指针2也前进了n-k步
//此时指针2指向倒数k的位置
private:
    ListNode* findFromEnd(ListNode* head, int k) {
        ListNode* ptr1 = head;
        for (int i=0; i<k; i++) {
            ptr1 = ptr1->next;
        }

        ListNode* ptr2 = head;
        while (ptr1 != nullptr) {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        return ptr2;
    }
//目的是要删除指定位置的节点，拿到该节点的前驱更方便操作
//所以要找到倒数第n+1个节点，就是该节点的前驱。这样解释其实是有点疑惑的，
//因为进入到findFromEnd函数后，指针1要先移动n+1，多移动了一步，第二次移动到最后就会少移动一步，那么指针2也同样的少移动一步，正好指向指定位置的前驱节点，符合我意。
//注意：这里传入的是新建的头结点，具体理由看上面注释，
//另外一个理由：当传入的链表只有一个节点时，只能删除这个头结点，那么移动n+1就要移动两次，传入新建的头结点正好移动两次。若传入原来的头结点则报错。
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr) return head;
        ListNode* newHead = new ListNode;
        newHead->next = head;

        ListNode* ptr = findFromEnd(newHead, n+1);

        ptr->next = ptr->next->next;

        return newHead->next;
    }


};
// @lc code=end

