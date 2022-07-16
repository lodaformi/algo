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
    seqQueue(int initSize=100);
    bool isEmpty() {return front == rear;}
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() {return data[front+1];}
    ~seqQueue();
};

template <class elemType>
seqQueue<elemType>::seqQueue(int initSize) {
    maxSize = initSize;
    data = new elemType[initSize];
    front=rear=0;
    currentSize=initSize;
}

template <class elemType>
seqQueue<elemType>::~seqQueue() {
    delete []data;
    front=rear=0;
    currentSize=0;
}

template <class elemType>
void seqQueue<elemType>::doubleSpace() {
    elemType *tmp = data;
    maxSize *= 2;
    data = new elemType[maxSize];
    for (int i = 0; i < currentSize; i++)
    {
        data[i] = tmp[i];
    }
    delete []tmp;
}


template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x) {
    // if (currentSize == maxSize)
    // {
    //     doubleSpace();
    // }
    // data[++rear] = x;
    // ++currentSize;

    if(currentSize == maxSize - 1) 
        doubleSpace();

    int hole = ++rear;
    for(; hole > 1 && x > data[hole / 2]; hole /= 2)
        data[hole] = data[hole / 2];
    data[hole] = x;
    ++currentSize;
}

// template <class elemType>
// void priorityQueue<elemType>::enQueue( const elemType & x ) {
//     if(currentSize == maxSize - 1) 
//         doubleSpace();

//     int hole = ++currentSize;
//     for(; hole > 1 && x < data[hole / 2]; hole /= 2)
//         data[hole] = data[hole / 2];
//     data[hole] = x;
// } 

// template <class elemType>
// elemType seqQueue<elemType>::deQueue() {
//     --currentSize;
//     return data[++front];
// }

template <class elemType>
elemType seqQueue<elemType>::deQueue() { 
    elemType maxItem;
    maxItem = data[1];
    data[1] = data[rear--];
    // 从1号下标开始向下过滤
    percolateDown(1);
    --currentSize;
    return maxItem;
} 

template <class elemType>
void seqQueue<elemType>::percolateDown(int hole) { 
    int child;
    elemType tmp = data[hole];

    for(; hole * 2 <= currentSize; hole = child) { 
        child = hole * 2;
        if (child != currentSize && data[child + 1] > data[child])
            child++;
        if( data[child] > tmp )   
            data[hole] = data[child];
        else break;
    }
    data[hole] = tmp;
}