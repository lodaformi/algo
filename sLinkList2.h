#include <iostream>
#include "list.h"
using namespace std;

template <class elemType>
class sLinkList: public list<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType& d, node *n=nullptr) {data=d; next=n;}
        node() : next(nullptr) {}
        ~node() {}
    };
    int currentLength;
    node *head;

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

//移动指针
template <class elemType>
sLinkList<elemType>::node* sLinkList<elemType>::move(int i) const {
    node *ptr = head;
    while (i-- > 0)
    {
        ptr = ptr->next;
    }
    return ptr;
}

//清除
template <class elemType>
void sLinkList<elemType>::clear() {
    node *p = head->next, *q;
    head->next = nullptr;  //先把整个链表置空
    //循环删除后面的所有节点
    while (p != nullptr)
    {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength=0;
}

template <class elemType>
void sLinkList<elemType>::insert(int i, const elemType &x) {
    node *pre = move(i-1);
    pre->next = new node(x, pre->next);
    ++currentLength;
}

template <class elemType>
void sLinkList<elemType>::remove(int i) {
    node *pre = move(i-1);
    node *del = pre->next;
    pre->next = del->next;
    delete del;
    --currentLength;
}

//搜索
template <class elemType>
int sLinkList<elemType>::search(const elemType &x) const {
    node *ptr = head->next;
    int i;
    for (i = 1; ptr != nullptr && ptr->data != x; ++i, ptr=ptr->next);
    if (ptr == nullptr)
    {
        return -1;
    }else {
        return i;
    }
}

//访问
template <class elemType>
elemType sLinkList<elemType>::visit(int i) const {
    return move(i)->data;
}

//遍历
// void traverse() const;
template <class elemType>
void sLinkList<elemType>::traverse() const {
    node *ptr=head->next;
    while (ptr != nullptr)
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}