#include "myQueue.h"

template <class elemType>
class linkQueue: public myQueue<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x, node *n=nullptr) :data(x), next(n) {}
        node(node *n=nullptr) :next(nullptr) {}
        ~node() {}
    };
    node *front, *rear;
    
public:
    linkQueue() {front = rear = nullptr;}
    ~linkQueue();
    bool isEmpty() {return front == nullptr;}
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() {return front->data;}
};

template <class elemType>
linkQueue<elemType>::~linkQueue() {
    node *ptr = front, *q;
    while (ptr != nullptr)
    {
        q = ptr->next;
        delete ptr;
        ptr = q;
    }
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x) {
    //需考虑队列为空的情况
    // if (front = nullptr)
    if (rear == nullptr)
    {
        front = rear = new node(x);
    } else {
        rear = rear->next = new node(x);
    }
}

template <class elemType>
elemType linkQueue<elemType>::deQueue() {
    node *del = front;
    elemType val = del->data;

    front = front->next;
    delete del;

    //需考虑删除最后一个节点后，队列为空的情况
    if (front == nullptr) rear = nullptr;

    return val;
}
