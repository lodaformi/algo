/*
 date 20220823
 time 23:17
*/
#include <iostream>
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
    void mergeSort(int left, int right);
    void selectSort();
    void bubbleSort();
    void insertSort();
    void printData();
    ~mySort();
};

void mySort::insertSort() {
    int tmp;
    for (int i = 0; i < size; ++i)
    {
        tmp = data[i+1];
        for (int j = i+1; j > 0 && data[j] < tmp ; --j)
        {
            data[j] = data[j-1];
        }
        
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
            if (data[minIdx] > data[j]) minIdx = j;
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
    int arr[] = {4,2,1,6,3,9,8,5};
    int len = sizeof(arr)/ sizeof(arr[0]);
    mySort ms(arr, len);
    // ms.mergeSort(0, len-1);
    // ms.selectSort();
    ms.bubbleSort();
    ms.printData();

    system("pause");
    return 0;
}
