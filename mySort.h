#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

template <class elemType>
class mySort
{
private:
    int size;
    elemType *arr;
    elemType *copy;
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
        if (arr == nullptr || size < 2)  return;
        
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
        if (arr == nullptr || size < 2)  return;

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
        if (arr == nullptr || size < 2)  return;
        for (int i = 1; i < size; ++i)
        {
            int j;
            elemType k=arr[i];
            //逆序把前面值大的元素往后移
            for (j = i; j  > 0 && arr[j-1] > k; --j)
            {
                arr[j] = arr[j-1];
            }
            arr[j] = k;
        }
        
    }

    void makeCopy() {
        copy = new elemType[size];
    }

    //归并排序，递归实现
    void mergeSort(int left, int right) {
        if (arr == nullptr || size < 2)  return;
        //二叉树后序遍历
        if (left >= right) return;
        makeCopy();
        int mid = left + ((right - left) >> 1);
        mergeSort(left, mid);
        mergeSort(mid+1, right);   

        merge(left, mid, right);
    }



    void merge(int left, int mid, int right) {
        for (int i = left; i <= right; ++i)
            copy[i] = arr[i];
        
        int aIdx = left;
        int bIdx = mid+1;
        for (int i = left; i <= right; ++i)
        {
            //如果bIdx越界，则直接把aIdx的数据加入到arr中
            //如果都没越界，且copy[aIdx] <= copy[bIdx]，则把aIdx的数据加入到arr中
            //注意等号的处理
            if (bIdx > right || aIdx <= mid && copy[aIdx] <= copy[bIdx])
            {
                arr[i] = copy[aIdx++];
            } else {
                arr[i] = copy[bIdx++];
            }

            // if (aIdx > mid || bIdx <= right && copy[bIdx] < copy[aIdx]) arr[i] = copy[bIdx++];
            // else arr[i] = copy[bIdx++];
        }
    }

    //快速排序
    //二叉树前序遍历框架
    void quickSort_V1(int left, int right) {
        if (arr == nullptr || size < 2)  return;

        if (left >= right)  return;
        elemType pivot = arr[right];     //以最右边的值作为基准
        int left_idx = left - 1;          //定义左区域指针

        //索引不取到right，因为right已经作为基准值了
        for (int i = left; i < right; ++i)
        {
            //将小于pivot的值放到前面
            if (arr[i] < pivot)
            {
                swap(arr[i], arr[++left_idx]);
            }
        }
        //将基准点放到”中间“
        swap(arr[++left_idx], arr[right]); 
        //递归遍历左边
        if (left < left_idx-1) quickSort_V1(left, left_idx-1);
        //递归遍历右边
        if (left_idx+1 < right) quickSort_V1(left_idx+1, right);
    }

    //将小于pivot的值放到左边，等于pivot的值放中间，大于pivot的值放右边
    void quickSort_V2(int left, int right) {
        if (arr == nullptr || size < 2)  return;

        if (left >= right)  return;
        srand((unsigned)time(nullptr));
        //在left,right之间随机选取一个值，放到最右边，可以一定程度上避免基准值选取不合理的情况
        int ran = (rand()  % (right - left + 1)) + left;
        // cout << "rand " <<  ran <<endl;
        swap(arr[ran], arr[right]);
        
        elemType pivot = arr[right];     //以最右边的值作为基准
        int left_idx = left - 1;          //定义左区域指针
        int right_idx = right;    //定义右区域指针
        int i=left;
        while (i < right_idx)
        {
            if (arr[i] < pivot)
            {
                swap(arr[i++], arr[++left_idx]);
            } else if (arr[i] > pivot) {
                //从右边换过来的数未检查，所以i要保持不动
                swap(arr[i], arr[--right_idx]);
            }  else
            {
                ++i;
            }
        }
        //将基准值放到右边区域的最左边
        swap(arr[right_idx], arr[right]);
        
        //递归遍历左边
        if (left < left_idx) quickSort_V2(left, left_idx);
        //递归遍历右边
        //因为右边区域最左边是基准值，所以right_idx需加一
        if (right_idx < right) quickSort_V2(right_idx+1, right);
    }

    void printArr() {
        for (int i = 0; i < size; ++i)
        {
            cout << arr[i]  << " ";
        }
        cout << endl;
    }
};


