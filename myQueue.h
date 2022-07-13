#include <iostream>
using namespace std;

template <class elemType>
class myQueue
{
public:
    virtual bool isEmpty() = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() = 0;
    virtual ~myQueue() {}
};

