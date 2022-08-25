/*
 date 20220823
 time 23:17
*/
#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

class mySort
{
private:
    int *data;
    int *copyData;
    int size;
    void merge(int start, int mid, int end);
public:
    mySort(int *arr, int len);
    void selectSort();
    void bubbleSort();
    void insertSort();
    void mergeSort(int left, int right);
    void quickSort_v1(int left, int right);
    void quickSort_v2(int left, int right);
    void quickSort_v3(int left, int right);
    void printData();
    ~mySort();
};

//二叉树前序遍历框架
//基准值选最右边元素
//左边小于基准值，右边大于等于基准值，相等的值不一定在一起
void mySort::quickSort_v1(int left, int right) {
    //base case
    if (left >= right) return;
        
    //选取基准值
    int pivot = data[right];
    int leftIdx = left - 1;
    for (int i = left; i < right; ++i)
    {
        if (data[i] < pivot)        //小值往前放
        {
            swap(data[++leftIdx], data[i]);
        }
    }
    swap(data[++leftIdx], data[right]);    //将基准值放到分界点

    quickSort_v1(left, leftIdx-1);
    quickSort_v1(leftIdx+1, right);
}

//基准值选最右边元素
//左边小于基准值，中间等于基准值，右边大于基准值
void mySort::quickSort_v2(int left, int right) {
    if (left >= right) return;

    int pivot = data[right];
    int leftIdx = left - 1;     //左边界，刚开始索引不在数组范围内
    int rightIdx = right;       //右边界，因为最右边元素已经作为基准值，后续该索引变化时会跳过最右边元素

    int i = left;
    while (i < rightIdx)    //循环退出的条件是i等于rightIdx，即遍历数组的索引i与右边界索引重合
    {
        if (data[i] < pivot)    //当元素值小于基准值时
        {
            swap(data[++leftIdx], data[i++]);   //小值放到左边界，左边界右移，i右移
        }
        if (data[i] == pivot) {++i;}    //当元素值等于基准值时，左右边界索引不动，i自增
        if (data[i] > pivot)            //当元素值大于基准值时，
        {
            swap(data[--rightIdx], data[i]);    //大值放到右边界
            //右边界左移，i不动，因为从右边界换过来的值还没有检查，需在下一轮中检查其于基准值的关系
        }        
    }
    //将基准值放到分界点，分界点是rightIdx
    swap(data[right], data[rightIdx]);

    quickSort_v2(left, leftIdx);
    quickSort_v2(rightIdx+1, right);    //分界点rightIdx存放的是基准值，所以右边区域是从rightIdx+1开始
}

//基准值随机选取，避免最右边元素为最大或最小造成时间复杂度上升
//左边小于基准值，中间等于基准值，右边大于基准值
void mySort::quickSort_v3(int left, int right) { 
    if(left >= right)  return;
    srand((unsigned)time(nullptr));     //定义随机数种子
    int randNum = rand() % (right - left + 1) + left; //在[left right]闭区间上生成一个随机数
    swap(data[randNum], data[right]);   //将选出的元素放到最右边

    int pivot = data[right];
    int leftIdx = left - 1;
    int rightIdx = right;
    int i = left;
    while (i < rightIdx)
    {
        if (data[i] < pivot)
        {
            swap(data[++leftIdx], data[i++]);
        }
        if (data[i] == pivot)
        {
            ++i;
        }
        if (data[i] > pivot)
        {
            swap(data[--rightIdx], data[i]);
        }
    }
    swap(data[rightIdx], data[right]);

    quickSort_v3(left, leftIdx);
    quickSort_v3(rightIdx+1, right);    
}


void mySort::insertSort() {
    int tmp, j;
    for (int i = 1; i < size; ++i)
    {
        tmp = data[i];
        //大值往后移
        for (j = i; j > 0 && data[j-1] > tmp; --j)
        {
            data[j] = data[j-1];
        }
        data[j] = tmp;
    }
}

void mySort::bubbleSort() {
    for (int i = size-1; i > 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (data[j] > data[j+1]) swap(data[j], data[j+1]);
        }
    }
    
    // for (int i = 0; i < size-1; ++i)
    // {
    //     for (int j = 0; j < size-1-i; ++j)
    //     {
    //         if (data[j] > data[j+1]) swap(data[j], data[j+1]);
    //     }
    // }
}

void mySort::selectSort() {
    int minIdx;
    for (int i = 0; i < size-1; ++i)    //n个数只需n-1趟
    {
        minIdx = i;
        for (int j = i+1; j < size; ++j)
        {
            // if (data[minIdx] > data[j]) minIdx = j;
            minIdx = data[minIdx] > data[j] ? j : minIdx;
        }
        swap(data[minIdx], data[i]);
    }
}

mySort::~mySort() {
    delete []data;
    delete []copyData;
}

mySort::mySort(int *arr, int len) {
    size = len;
    data = new int[len];
    copyData = new int[len];
    for (int i = 0; i < len; ++i)
    {
        data[i] = arr[i];
    }
}

//二叉树后续遍历框架
void mySort::mergeSort(int left, int right) {
    if (left == right) return;
    //算术运算符的优先级大于右移运算符，所以一定要加括号，改变运算顺序
    int mid = left + ((right-left)>>1);
    mergeSort(left, mid);
    mergeSort(mid+1, right);

    merge(left, mid, right);
}


void mySort::merge(int left, int mid, int right) {
    for (int i = left; i <= right; ++i)
    {
        copyData[i] = data[i];
    }

    int leftIdx = left, rightIdx = mid+1;
    for (int i = left; i <= right; ++i)
    {
        if ((leftIdx <= mid && copyData[leftIdx] < copyData[rightIdx]) || rightIdx > right)
        {
            data[i] = copyData[leftIdx++];
        } else {
            data[i] = copyData[rightIdx++];
        }
    }
}

void mySort::printData() {
    for (int i = 0; i < size; ++i)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = {4,6,1,6,3,9,10,6,8,5};
    int len = sizeof(arr)/ sizeof(arr[0]);
    mySort ms(arr, len);
    // ms.mergeSort(0, len-1);
    // ms.selectSort();
    // ms.bubbleSort();
    // ms.insertSort();
    // ms.quickSort_v1(0, len-1);
    // ms.quickSort_v2(0, len-1);
    ms.quickSort_v3(0, len-1);
    ms.printData();

    system("pause");
    return 0;
}
