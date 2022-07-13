#include <iostream>
#include "myStack.h"
using namespace std;

template <class elemType>
class seqStack: public myStack<elemType>
{
private:
    elemType *elem;
    int top_p;
    int maxSize;
    void doubleSpace();
   
public:
    seqStack (int initSize = 10)
    ~seqStack () {delete [] elem;}
    bool isEmpty() const { return top_p == -1;}
    void push(const elemType &x);
    elemType pop() {return elem[top_p--];}
    elemType top() {return elem[top_p]; }
};

    // void doubleSpace();
template <class elemType>
void seqStack<elemType>::doubleSpace() {
    elemType* tmp = elem;
    maxSize *= 2;
    elem = new elemType[maxSize];
    for (int i = 0; i <= top_p; ++i)
    {
        elem[i] = tmp[i];        
    }
    delete []tmp;
}

template <class elemType>
seqStack<elemType>::seqStack(int initSize) {
    elem  = new elemType[initSize];
    top_p = -1;
    maxSize = initSize;
}

template <class elemType>
void seqStack<elemType>::push(const elemType &x) {
    if (top_p == maxSzie-1)
    {
        doubleSpace();
    }
    elem[++top_p] = x;
}