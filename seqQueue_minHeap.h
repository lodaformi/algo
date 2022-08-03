#include <iostream>
#include "myQueue.h"
#include <string.h>
using namespace std;

//小根堆
template <class elemType>
class seqQueue_minHeap
{
private:
    //数据从索引1位置开始，牺牲掉0位置，好记
    //左孩子为2*i，右孩子为2*i+1，父节点为i/2，heapSize与最后一个节点索引相等
    elemType* data;
    int maxSize;
    int heapSize;
    void buildStack();
    void procolateDown(int hole);
    void doubleSpace();
public:
    bool isEmpty() {return heapSize == 0;}
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() {return data[1];}
    void heapSort();
    seqQueue_minHeap(const int arr[], int initSize);
    seqQueue_minHeap(int initSize);
    ~seqQueue_minHeap();
};

template <class elemType>
void seqQueue_minHeap<elemType>::heapSort() {
    if (data == nullptr || heapSize < 2) return;

    while (!isEmpty())
    {
        cout << deQueue() << " ";
    }
    cout << endl;
}

template <class elemType>
void seqQueue_minHeap<elemType>::buildStack() {
    //从最后一个非叶节点开始调整每个子树为小根堆
    for (int i = heapSize/2; i >= 1; --i)
    {
        procolateDown(i);
    }

    //第二种构建堆的方法，边入队边调整
    // for (int i = 1; i <= heapSize; ++i)
    // {
    //     enQueue(data[i]);
    // }
}

template <class elemType>
void seqQueue_minHeap<elemType>::procolateDown(int hole) {
    int x = data[hole];
    int child;
    //如果存在孩子节点
    for (; 2*hole <= heapSize; hole = child)   {
        child = 2 * hole;
        //选取左右孩子中较小者的索引
        //如果存在右孩子，且右孩子值小，则smaller为child+1
        //如果不存在右孩子，或左孩子小，则smaller不变
        child = (child != heapSize && data[child+1] < data[child] ? child+1 : child);
        //如果左右孩子的较小者比x还小，子节点上移
        
        if (data[child] < x)
        {
            data[hole] = data[child];
        }else break; //如果左右孩子的较小者比x大，退出循环，hole就为x所在位置
    }
    //将x放到hole中
    data[hole] = x;
}

template <class elemType>
elemType seqQueue_minHeap<elemType>::deQueue() {
    elemType tmp = data[1];
    data[1] = data[heapSize--];
    procolateDown(1);
    return tmp;
}

template <class elemType>
void seqQueue_minHeap<elemType>::doubleSpace() {
    elemType *tmp = data;
    maxSize *= 2;
    data = new elemType[maxSize];
    for (int i = 1; i <= heapSize; ++i)  //索引从1开始，可以去到heapSize
    {
        data[i] = tmp[i];
    }
    delete []tmp;
}

template <class elemType>
void seqQueue_minHeap<elemType>::enQueue(const elemType &x) {
    if (heapSize == maxSize-1)  //数组满的判断，heapSize还是索引，要小于maxSize-1
    {
        doubleSpace();
    }
    int hole = ++heapSize;
    //小值往上浮，父节点下移
    for (; hole > 1 && x < data[hole/2]; hole /= 2)
    {
        data[hole] = data[hole/2];
    }
    data[hole] = x;
}

//这种构造方式，在传入整个数组后，对整个数组进行小根堆的构建
//需要注意：maxsize要比传入数组的size大1，因为堆的数组是从1开始，牺牲了0位置
template <class elemType>
seqQueue_minHeap<elemType>::seqQueue_minHeap(const int arr[], int size)
{
    maxSize = size+10;
    heapSize= size;
    data = new elemType[maxSize];
    for (int i = 0; i < size; ++i)
    {
        data[i+1] = arr[i];
    }
    buildStack();
}

//这种构建方式是，先申请空间，将数组初始化为0，后续再通过调用恩Queue()函数入队
template <class elemType>
seqQueue_minHeap<elemType>::seqQueue_minHeap(int initSize) {
    maxSize=initSize;
    heapSize=0;
    data = new elemType[maxSize];
    memset(data,0,initSize);
}

template <class elemType>
seqQueue_minHeap<elemType>::~seqQueue_minHeap()
{
    delete []data;
}
