#include <iostream>
#include "list.h"
using namespace std;

template <class elemType>
class dLinkList: public list<elemType>
{
private:
    struct node
    {
        elemType data;
        node *pre, *next;
        node(const elemType& d, node *p=nullptr, node *n=nullptr) {data=d; next=n; pre=p;}
        node() : pre(nullptr), next(nullptr) {}
        ~node() {}
    };
    int currentLength;
    node *head, *tail;

    //移动指针
    node* move(int i) const;
    
public:
    dLinkList() {
        head = new node; 
        tail = new node;
        head->next = tail;
        tail->pre = head;
        currentLength = 0;
    };

    ~dLinkList() {
        clear(); 
        delete head;
        delete tail;
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

//遍历
// void traverse() const;
template <class elemType>
void dLinkList<elemType>::traverse() const {
    node *ptr = head->next;
    while (ptr != tail)
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

//访问
template <class elemType>
elemType dLinkList<elemType>::visit(int i) const {
    return move(i)->data;
}

//搜索
template <class elemType>
int dLinkList<elemType>::search(const elemType &x) const {
    int i;
    node *ptr = head->next;
    for (i = 1; ptr != nullptr && ptr->data != x; ++i, ptr=ptr->next);

    if (ptr == nullptr)
    {
        return -1;
    }else {
        return i;
    }
}

//移动指针
template <class elemType>
typename dLinkList<elemType>::node* dLinkList<elemType>::move(int i) const {
    node *ptr = head;
    while (i-- > 0)
    {
        ptr = ptr->next;
    }
    return ptr;
}

//清除
template <class elemType>
void dLinkList<elemType>::clear() {
    node *p=head->next, *q;
    head->next = nullptr;
    while (p != nullptr)
    {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

//插入
template <class elemType>
void dLinkList<elemType>::insert(int i, const elemType &x) {
    node *pos = move(i);
    
    node *tmp = new node(x, pos->pre, pos);
    pos->pre->next = tmp;
    pos->pre = tmp;
    ++currentLength;
}

//删除
template <class elemType>
void dLinkList<elemType>::remove(int i) {
    node *pos = move(i);
    pos->pre->next = pos->next;
    pos->next->pre = pos->pre;
    delete pos;
    --currentLength;
}

int main() {
    dLinkList<int> dl;
    dl.insert(1,1);

    int N;
    cin >> N;
    int people, leftOrRight;
    for (int i=2; i<=N; ++i) {
        cin >> people >> leftOrRight;

        int pos = dl.search(people);
        if (leftOrRight == 0) {
            dl.insert(pos, i);
        } else {
            dl.insert(pos+1, i);
        }
    }
    int delN, delNum;
    cin >> delN;
    for (int i=0; i<delN; ++i) {
        cin >> delNum;
        int pos = dl.search(delNum);
        if (pos != -1) {
            dl.remove(pos);
        }
    }
    dl.traverse();

    system("pause");
    return 0;
}