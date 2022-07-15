#include <iostream>
#include "myQueue.h"
using namespace std;

template <class elemType>
class priorityQueue: public myQueue<elemType>
{
private:
    elemType *data;
    int maxSize;
    int front, rear;
    void doubleSpace();    
public:
    priorityQueue(int initSize=1000);
    ~priorityQueue() {delete []data;}
    bool isEmpty() {return front == rear;}
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() {return data[(front+1)%maxSize];}
    void percolateDown(int hole);
    elemType deQueue();
    void percolateDown(int hole);
};

template <class elemType>
priorityQueue<elemType>::seqQueue(int initSize) {
    data = new elemType[initSize];
    maxSize = initSize;
    front = rear = 0;
}

//注意：循环顺序队列的扩容不同于顺序表和顺序栈，
//因为队列的头尾指针顺序有可能逆序，且头指针不是从0开始，尾指针不是以maxSize结束
template <class elemType>
void priorityQueue<elemType>::doubleSpace() {
    elemType *tmp =data;
    data = new elemType[maxSize*2];
    //i从1开始，0的位置留给front
    //因为这里要用到原来的maxSize，所以在使用完之后再变为2倍
    for (int i = 1; i < maxSize; ++i)
    {
        data[i] = tmp[(front+i) % maxSize];
    }
    front = 0;          //front重新放置到0
    rear = maxSize -1;  //rear重新放置
    maxSize *= 2;
    delete []tmp;
}

// template <class elemType>
// void priorityQueue<elemType>::enQueue(const elemType &x) {
//     if ((rear+1)%maxSize == front)
//     {
//         doubleSpace();
//     }
//      rear = (rear+1)%maxSize; 
//      data[rear]=x;
// }

// template <class elemType>
// elemType priorityQueue<elemType>::deQueue() {
//     front = (front+1)%maxSize;
//     return data[front];
// }

template <class elemType>
void priorityQueue<elemType>::enQueue( const elemType & x ) {
    // if(currentSize == maxSize - 1) 
    //     doubleSpace();

    if ((rear+1)%maxSize == front)
    {
        doubleSpace();
    }

    int hole = ++currentSize;
    for(; hole > 1 && x < data[hole / 2]; hole /= 2)
        data[hole] = data[hole / 2];
    data[hole] = x;
} 

template <class elemType>
T priorityQueue<elemType>::deQueue() { 
    T minItem;
    minItem = data[1];
    data[1] = data[currentSize--];
    // 从1号下标开始向下过滤
    percolateDown(1);
    return minItem;
} 

template <class elemType>
void priorityQueue<elemType>::percolateDown(int hole) { 
    int child;
    T tmp = data[hole];

    for(; hole * 2 <= currentSize; hole = child) { 
        child = hole * 2;
        if (child != currentSize && data[child + 1] < data[child])
            child++;
        if( data[child] < tmp )   
            data[hole] = data[child];
        else break;
    }
    data[hole] = tmp;
}