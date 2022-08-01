#include <iostream>
#include "../mySort.h"
using namespace std;

//小和问题
//一个数组中，如果一个数a左边存在小于这个数的数b，则将数b计入小和，求整个数组的小和
//题解：
//转换思路：将左边小于数a，改为右边存在x个大于数a的数，记为x*a，
//归并排序在合并的时候，可以实现上述思路
//只有在左边小于右边的时候才记录小和，大于等于时右边索引移动，不产生小和
class small
{
private:
    int size;
    int *arr;
    int *copy;
    int smallRes;
public:
    small(int *a, int s) {
        smallRes = 0;
        size=s;
        arr = new int[size];
        for (int i = 0; i < size; ++i)
        {
            arr[i] = a[i];
        }
    }

    void smallSum(int left, int right) {
        if (arr == nullptr || size < 2) return;
        if (left >= right) return;
        copy = new int[size];

        int mid = left + ((right - left) >> 1);
        smallSum(left, mid);
        smallSum(mid+1, right);

        merge(left, mid, right);
    }

    void merge(int left, int mid, int right) {
        for (int i = left; i <= right; ++i)
        {
            copy[i] = arr[i];
        }

        int i=left, aIdx=left, bIdx=mid+1;
        while (aIdx <= mid && bIdx <= right)
        {
            //只有在左边小于右边的时候才记录小和，
            smallRes += copy[aIdx] < copy[bIdx] ? copy[aIdx] * (right-bIdx+1) : 0;
            //值相等时必须是右边移动，因为左边这个相等的值还可能会产生小和
            arr[i++] = copy[aIdx] < copy[bIdx] ? copy[aIdx++] : copy[bIdx++];

            // if (copy[aIdx] < copy[bIdx])
            // {
            //     //只有在左边小于右边的时候才记录小和，
            //     smallRes += copy[aIdx] * (right-bIdx+1);
            //     arr[i++] = copy[aIdx++];
            // }else{
            //     //值相等时必须是右边移动，因为左边这个相等的值还可能会产生小和
            //     arr[i++] = copy[bIdx++];
            // }
        }
        //说明bIdx已经越界
        while (aIdx <= mid)
        {
            arr[i++] = copy[aIdx++];
        }
        //说明aIdx已经越界
        while (bIdx <= right)
        {
            arr[i++] = copy[bIdx++];
        }
    }

    void printSmallRes() {
        cout << "small res : " << smallRes << endl;
    }
};


//左边的数比右边的数大，构成一个逆序对，输出数组中所有的逆序对
//既然是逆序对，那么归并排序就按照从大到小的顺序排列
//假如还是从小到大的顺序，在合并的时候，那个值小，那个移动的方式，那么在小指在右边时，小指被移走了，就不能产生逆序对了
//所以要按照从大到小的顺序，
//右边有大值，不产生逆序对；
//左边有大值，不能直接把左边的大值移走，因为右边可能还存在小指，所以要把右边遍历一遍(排除相等的值)，寻找可能的逆序对。再把左边大值移走
class reversePair
{
private:
    int size;
    int *arr;
    int *copy;
    int pairNum;
public:
    reversePair(int *a, int s) {
        pairNum = 0;
        size=s;
        arr = new int[size];
        for (int i = 0; i < size; ++i)
        {
            arr[i] = a[i];
        }
    }

    void rpFun(int left, int right) {
        if (arr == nullptr || size < 2) return;
        if (left >= right) return;
        copy = new int[size];

        int mid = left + ((right - left) >> 1);
        rpFun(left, mid);
        rpFun(mid+1, right);

        merge(left, mid, right);
    }

    //按照从大到小的顺序排列
    void merge(int left, int mid, int right) {
        for (int i = left; i <= right; ++i)
        {
            copy[i] = arr[i];
        }

        int i=left, aIdx=left, bIdx=mid+1;
        while (aIdx <= mid && bIdx <= right)
        {
            //当值相等时，左边移动，因为右边的这个相等值可能产生逆序对
            if (copy[aIdx] <= copy[bIdx])
            {
                arr[i++] = copy[bIdx++];
            }else{
                //只有在左边大于右边的时候才产生逆序对
                for (int j = bIdx; j <= right && copy[aIdx] != copy[j]; ++j)
                {
                    ++pairNum;
                    cout << copy[aIdx] << "--" << copy[j] << endl;
                }
                arr[i++] = copy[aIdx++];
            }
        }
        //说明bIdx已经越界
        while (aIdx <= mid)
        {
            arr[i++] = copy[aIdx++];
        }
        //说明aIdx已经越界
        while (bIdx <= right)
        {
            arr[i++] = copy[bIdx++];
        }
    }
    void printNum() {
        cout << "pair num is " << pairNum << endl;
    }

    void printArr() {
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i]  << " ";
    }
    cout << endl;
    }
};

int main( ) {
    int arr[] = {2,1,5,3,0};
    // int arr[] = {3,2,4,5,2,1};
    int len = sizeof(arr)/sizeof(arr[0]);
    // small s(arr, len);
    // s.smallSum(0, len-1);
    // s.printSmallRes();

    reversePair rp(arr, len);
    rp.rpFun(0,len-1);
    rp.printNum();
    rp.printArr();

    system("pause");
    return 0;
}