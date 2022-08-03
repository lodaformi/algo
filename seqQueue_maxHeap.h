#include <iostream>
#include <string.h>
#include "myQueue.h"
using namespace std;

template <class elemType>
class seqQueue_maxHeap : public myQueue<elemType>
{
private:
    elemType *data;
    int maxSize;
    int heapSize;
    void doubleSpace();    
    void percolateDown(int hole);
    void preOrder(int idx);
public:
    seqQueue_maxHeap(int initSize=100);
    seqQueue_maxHeap(const elemType *items, int size); //带初值的构造函数
    bool isEmpty() {return heapSize == 0;}
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() {return data[1];}
    void buildHeap();
    ~seqQueue_maxHeap();
    void preOrder();
};

template <class elemType>
void seqQueue_maxHeap<elemType>::preOrder() {
    cout << "preorder: ";
    preOrder(1);
} 

template <class elemType>
void seqQueue_maxHeap<elemType>::preOrder(int idx) {
    if (idx > heapSize)
    {
        return;
    }
    
    cout << data[idx] << " ";
    preOrder(idx * 2);
    preOrder(idx*2 + 1);
}

//以逆向层次的次序对节点调用percolateDown
template <class elemType>
void seqQueue_maxHeap<elemType>::buildHeap() {
    //heapSize/2是最后一个非叶子节点，也就是最后一个有孩子的节点
    for (int i = heapSize/2; i >= 1; --i)
    {
        percolateDown(i);
    }
}

template <class elemType>
seqQueue_maxHeap<elemType>::seqQueue_maxHeap(const elemType *items, int size) {
    //因为数组索引从1开始，如果maxSize与size相等，则在下面的for循环中，data数组是越界的，所以maxSize要比size大一点
    maxSize = size + 10;  
    heapSize = size;
    data = new elemType[maxSize];
    for (int i = 0; i < size; ++i)
    {
        data[i+1] = items[i];
    }
    buildHeap();
}


template <class elemType>
seqQueue_maxHeap<elemType>::seqQueue_maxHeap(int initSize) {
    maxSize = initSize;
    data = new elemType[initSize];
    memset(data,0,initSize);    //初始化为0
    heapSize=0;
}

template <class elemType>
seqQueue_maxHeap<elemType>::~seqQueue_maxHeap() {
    delete []data;
}

template <class elemType>
void seqQueue_maxHeap<elemType>::doubleSpace() {
    elemType *tmp = data;
    maxSize *= 2;
    data = new elemType[maxSize];
    for (int i = 1; i <= heapSize; i++)
    {
        data[i] = tmp[i];
    }
    delete []tmp;
}

//入队操作整体方向是从最后一个节点向上找合适的位置，hole上浮，父节点下沉
template <class elemType>
void seqQueue_maxHeap<elemType>::enQueue(const elemType &x) {
    if(heapSize == maxSize - 1) //heapSize是从1开始计数 
        doubleSpace();              //如果空间满了，则扩大1倍的空间

    //为要插入的元素x申请空间(挖一个洞)，还没有存入
    int hole = ++heapSize;
    //当hole=1 或者 x不大于父节点值，则位置就是这个hole，退出循环。
    //因为一个循环中，已经将当前hole和(hole/2) parent做了比较，在hole是1的左右孩子节点时，已经跟1做了比较
    for(; hole > 1 && x > data[hole / 2]; hole /= 2)
        data[hole] = data[hole / 2];

    //自己写的代码，易懂，能达到目的，但是冗余
	// for (; hole >1 ; hole=parent) {  
	// 	int parent = hole/2;
	// 	if (x > data[parent]) {      //如果要插入的x大于父节点值，父节点下移
	// 		data[hole] = data[parent]; 
	// 	}else {                      //如果x不大于父节点值，则位置就是这个hole，退出循环
	// 		break;
	// 	}
	// }
    data[hole] = x; //将x放到hole中
}

//出队操作分3部分，1.删除第一个元素，2.将最后一个元素放到第一个位置，
//3.第一个元素下沉到合适位置
template <class elemType>
elemType seqQueue_maxHeap<elemType>::deQueue() { 
    //先保存第一个元素
    elemType maxItem = data[1];

    //将最后一个元素放到第一个位置后缩小1个空间
    data[1] = data[heapSize--];
    // 从1号下标开始向下过滤
    percolateDown(1);
    return maxItem;
} 

//hole下沉，子节点上浮
template <class elemType>
void seqQueue_maxHeap<elemType>::percolateDown(int hole) { 
    int child;
    //临时存放data[hole]
    elemType tmp = data[hole];

    // hole * 2若小于heapSize表示至少存在左孩子，对于右孩子的判断在循环内
    //hole * 2若等于heapSize表示为最后一个非叶节点
    //hole * 2若大于heapSize表示为叶节点，不进入循环
    for(; hole * 2 <= heapSize; hole = child) { 
        child = hole * 2;
        //第一个if判断是在左右孩子中寻找较大值
        //如果child != heapSize表示hole*2不是最后一个节点，说明存在右孩子，比较左右孩子的大小
        //如果child == heapSize表示hole*2是最后一个节点，不存在右孩子，判断不成立，退出if判断
        if (child != heapSize && data[child + 1] > data[child])
            child++;
        
        //如果子节点比tmp大，则子节点上浮
        if(data[child] > tmp)   
            data[hole] = data[child];
        //如果子节点比tmp小，则该hole即为tmp存放的最终位置，退出循环
        else break;
    }
    //将tmp放到hole中
    data[hole] = tmp;
}