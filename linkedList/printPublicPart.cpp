#include <iostream>
using namespace std;

/*
打印两个有序链表的有序部分，要求：时间复杂度为O(N)，空间复杂度为O(1)
*/

typedef struct nodeList {
    int val;
    nodeList* next;
    nodeList(int v, nodeList* n=nullptr) {val=v; next=n;}
}nodeList;

void printPublicNode(nodeList* headA, nodeList* headB) {
    if (headA == nullptr || headB == nullptr)
    {
        return;
    }
    
    nodeList *ptrA=headA, *ptrB=headB;
    //当两个链表都不为空时，小值先移动，相等一起移动，一个链表为空退出循环
    while (ptrA != nullptr && ptrB != nullptr)
    {
        if (ptrA->val < ptrB->val)
        {
            ptrA = ptrA->next;
        }else if (ptrB->val < ptrA->val)
        {
            ptrB = ptrB->next;
        }else {
            cout << ptrA->val << " ";
            ptrA = ptrA->next;
            ptrB = ptrB->next;
        }
    }
    cout << endl;    
}

void insertNode(nodeList *head, int val) {
    if (head == nullptr)
    {
        return;
    }
    nodeList *iNode = new nodeList(val);
    nodeList *ptr=head;
    ptr->next = iNode;
}

void printList(nodeList *head) {
    if (head == nullptr)
    {
        return;
    }
    nodeList *ptr = head;
    while (ptr != nullptr)
    {
        cout << ptr->val << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

int main() {
    nodeList *listA = new nodeList(3);
    insertNode(listA, 4);
    insertNode(listA->next, 5);
    insertNode(listA->next->next, 8);
    insertNode(listA->next->next->next, 9);
    printList(listA);

    nodeList *listB = new nodeList(1);
    insertNode(listB, 2);
    insertNode(listB->next, 4);
    insertNode(listB->next->next, 5);
    printList(listB);
    printPublicNode(listA, listB);

    system("pause");
    return 0;
}