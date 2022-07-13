#include "list.h"
#include <iostream>
using namespace std;

template <class elemType>
class seqList: public list<elemType>
{
private:
    elemType *data;
    int maxSize;
    int currentLength;
    void doubleSpace();

public:
    seqList(int initSize = 10) ;

    ~seqList() {delete [] data; }

    //清除
    void clear();
    //长度
    int length() const;
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

template <class elemType>
void seqList<elemType>::doubleSpace() {
    //保存原来空间指针
    elemType *tmp = data;
    //申请double空间
    maxSize *= 2;
    data = new elemType[maxSize];
    //拷贝原来数据
    for (int i = 0; i < currentLength; ++i)
    {
        data[i] = tmp[i];
    }
    //释放原来的空间
    delete []tmp;
}

template <class elemType>
seqList<elemType>::seqList(int initSize) {
    data = new elemType[initSize];
    maxSize = initSize;
    currentLength = 0;
}

template <class elemType>
void seqList<elemType>::clear() { currentLength = 0; }   

template <class elemType>
int seqList<elemType>::length() const {return currentLength;}

template <class elemType>
void seqList<elemType>::insert(int i, const elemType &x) {
    //判断是否满员，如果满了，扩大数组空间
    if (currentLength == maxSize) {
        doubleSpace();
    } 

    //逆序移动元素，腾出i位置
    //注意边界的判断，j不能取到i，因为下面有j-1。j==i时退出了for循环，此时正好腾出i位置
    for (int j = currentLength; j>i; --j){
        data[j] = data[j-1];
    }
    
    data[i] = x;
    ++currentLength;
}

//删除
template <class elemType>
void seqList<elemType>::remove(int i) {
    //先判断是否为空
    if (currentLength == 0) {
        return;
    }

    //正序移动元素，填补i的空位
    //注意边界的判断，下面有j+1，所以currentLength-1
    for (int j = i;  j < currentLength-1; ++j)
    {
        data[j] = data[j+1];
    }
    --currentLength;
}
    
//搜索
template <class elemType>
int seqList<elemType>::search(const elemType &x) const {
    // for (int j = 0; j < currentLength; j++)
    // {
    //     if (data[j] == x) return j;
    // }
    // return -1;

    int i;
    for (int i = 0; i < currentLength && data[i] != x; ++i);
    if (i == currentLength)
    {
        return -1;  //没找到
    }else {
        return i;
    }   
}

//访问
template <class elemType>
elemType seqList<elemType>::visit(int i) const {
    return data[i];
}

//遍历
template <class elemType>
void seqList<elemType>::traverse() const {
    for (int i = 0; i < currentLength; ++i)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}
