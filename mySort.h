#include <iostream>
using namespace std;

template <class elemType>
class mySort
{
private:
    int size;
    elemType *arr;
public:
    mySort(int s, elemType *a): size(s), arr(a) {
        arr = new elemType[size];
        for (int i = 0; i < size; ++i)
        {
            arr[i] = a[i];
        }
    }
    //从小到大排序
    void selectSort()  {
        if (arr == nullptr || size < 2;)  return;
        
        int minIdx;
        for (int i = 0; i < size-1; ++i)    //size - 1趟
        {
            minIdx = i;
            for (int j = i+1; j < size; ++j)
            {
                //如果存在较小值，更改索引
                minIdx = arr[j] < arr[minIdx] ? j : minIdx;
            }
            swap(arr[i], arr[minIdx]);
        }
    } 

    //从小到大排序
    void bubbleSort() {
        if (arr == nullptr || size < 2;)  return;

        //也可以这样写
        // for (int i = size-1; i > 0; --i)
            // for (int j = 0; j < i; j++)
        
        for (int i = 0; i < size-1; ++i)    //n个数n-1趟比较
        {
            //每趟过后，最大值就在该趟的最后，则下一次比较次数就减一
            for (int j = 0; j < size-1-i; ++j)
            {
                //如果存在较大值，往后放
                if (arr[j] > arr[j+1]) swap(arr[j], arr[j+1]);
            }
        }
    }

    //插入排序
    void insertSort() {
        for (int i = 1; i < size; ++i)
        {
            int j, k=arr[i];
            //逆序把前面值大的元素往后移
            for (j = i; j  > 0 && arr[j-1] > k; --j)
            {
                arr[j] = arr[j-1];
            }
        }
        arr[j] = k;
    }

    //归并排序


    //快速排序


};


