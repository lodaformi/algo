#include <iostream>
#include "myStack.h"
using namespace std;

template <class elemType>
class linkStack: public myStack<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &d, node * n=nullptr): data(d), next(n) {}
        node(): next(nullptr) {}
        ~node() {}
    };
    node *top_p;
    
public:
    linkStack() {top_p = nullptr;}
    ~linkStack();
    bool isEmpty() const {return top_p == nullptr;}
    void push(const elemType &x) {top_p = new node(x, top_p);}
    elemType pop();
    elemType top() const {return top_p->data;}
};

template <class elemType>
elemType linkStack<elemType>::pop() {
    node *tmp=top_p;
    elemType x = del->data;

    top_p=top_p->next;
    delete tmp;
    return x;
}

template <class elemType>
linkStack<elemType>::~linkStack() {
    node *tmp;
    while (top_p != nullptr)
    {
        tmp=top_p;
        top_p = top_p->next;
        delete tmp;    
    }
}