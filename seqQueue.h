#include <iostream>
#include "myQueue.h"
using namespace std;

template <class elemType>
class seqQueue : public myQueue<elemType>
{
private:
    elemType *data;
    int maxSize;
    int front, rear;
    int currentSize;
    void doubleSpace();    
public:
    seqQueue();
    ~seqQueue();
};


