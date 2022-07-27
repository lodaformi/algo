#include <iostream>
#include "list.h"
using namespace std;

template <class elemType>
class sLinkList: public list<elemType>
{
private:
    typedef struct node
    {
        elemType data;
        // sLinkList<elemType> *next;
        node *next;
        node(const elemType& d, node *n=nullptr) {data=d; next=n;}
        node() : next(nullptr) {}
        ~node() {}
    }node;
    int currentLength;
    node *head;
    // elemType data2;
    // sLinkList<elemType> *next;
    //移动指针
    node* move(int i) const;
    
public:
    sLinkList() {
        head = new node; 
        currentLength = 0;
    };

    ~sLinkList() {
        clear(); 
        delete head;
    };
    //移动指针
    // sLinkList* move(int i);
    //清除
    void clear();
    //长度
    int length() const {return currentLength;};
    //插入
    void insert(int i, const elemType &x);
    //删除
    void remove(int i);
    //搜索
    int search(const elemType &x) const;
    //访问
    elemType visit(int i) const;
    //遍历
    void traverse() const;


};

// template <class elemType>
// sLinkList<elemType>* sLinkList<elemType>::move(int i) {
//     sLinkList* ptr = head;
//     for (int i = 0; i < i; i++)
//     {
//         ptr = ptr->next;
//     }
//     return ptr;
// }

template <class elemType>
typename sLinkList<elemType>::node* sLinkList<elemType>::move(int i) const{
    node* ptr = head;
    // for (int i = 0; i < i; i++)
    // {
    //     ptr = ptr->next;
    // }
    while (i-- > 0)
    {
        ptr = ptr->next;
    }
    
    return ptr;
}


// template <class elemType>
// void sLinkList<elemType>::clear() {
//     sLinkList* ptr = head;
//     for (int i = 0; i < currentLength; ++i)
//     {
//         sLinkList *tmp = ptr->next;
//         head->next = ptr->next->next;
//         delete tmp;
//     }
// }

//双指针技巧clear
template <class elemType>
void sLinkList<elemType>::clear() {
    // sLinkList *p = head;
    // sLinkList *q = head->next;
    // while (p->next != nullptr && q != nullptr)
    // {
    //     sLinkList *tmp = p;
    //     delete tmp;
    //     p = q;
    //     q = q->next;
    // }

    node *p = head->next, *q;
    head->next = nullptr;
    while (p != nullptr)
    {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

// template <class elemType>
// void sLinkList<elemType>::insert(int i, const elemType &x) {
//     sLinkList* ele = new sLinkList(x);
//     sLinkList* ptr = move(i-1);
//     ele->next = ptr->next;
//     ptr->next = ele;
//     ++currentLength;
// }

template <class elemType>
void sLinkList<elemType>::insert(int i, const elemType &x) {
    node *pos = move(i-1);
    pos->next = new node(x, pos->next);
    ++currentLength;
}



// //删除
// template <class elemType>
// void sLinkList<elemType>::remove(int i) {
//     sLinkList* ptr = move(i-1);
//     sLinkList* tmp = ptr->next;
//     ptr->next = tmp->next;
//     delete tmp;
//     --currentLength;
// }

//删除
template <class elemType>
void sLinkList<elemType>::remove(int i) {
    node* ptr = move(i-1);
    node* tmp = ptr->next;
    ptr->next = tmp->next;
    delete tmp;
    --currentLength;
}

// //搜索
// template <class elemType>
// int sLinkList<elemType>::search(const elemType &x) const {
//     sLinkList* ptr = head;
//     int i;
//     for (i = 0; ptr->next != nullptr && ptr->data2 != x; ptr = ptr->next, ++i);

//     if(ptr == nullptr) {return -1;}
//     else {return i;}
// }

//搜索
template <class elemType>
int sLinkList<elemType>::search(const elemType &x) const {
    node* ptr = head->next;
    int i = 0;
    while (ptr != nullptr && ptr->data != x)
    {
        ptr = ptr->next;
        ++i;
    }

    if(ptr == nullptr) {return -1;}
    else {return i;}
}


//访问
// elemType visit(int i) const;
template <class elemType>
elemType sLinkList<elemType>::visit(int i) const {
    // sLinkList* ptr = head;
    // for (int j = 0; i < j; ++j)
    // {
    //     ptr = ptr->next;
    // }    

    // return ptr->data2;

    return move(i)->data;
}

//遍历
template <class elemType>
void sLinkList<elemType>::traverse() const {
    node* ptr = head->next;
    while (ptr != nullptr)
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
    
    // for (int i = 0; i < currentLength; ++i)
    // {
    //     ptr = ptr->next;
    //     cout << ptr->data2 << endl;
    // }    
}