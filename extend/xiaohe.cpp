#include <iostream>
using namespace std;

int data[] = {5,1,2,2,4};
int size = sizeof(data) / sizeof(data[0]);
int *copyData = new int[size];
int littleSum = 0;

void merge(int left, int mid, int right) {
    for (int i = left; i <= right; ++i)
    {
        copyData[i] = data[i];
    }
    int leftIdx = left;
    int rightIdx = mid+1;

    for (int i = left; i <= right; ++i)
    {
        //值相等的时候，右边先移动，因为左边这个相等的值可能还会产生小和
        if ((leftIdx <= mid && copyData[leftIdx] < copyData[rightIdx]) || rightIdx > right)
        {
            //产生小和只有这一种情况，左边的数小，那么将右边大值的个数乘以当前左边值，计入小和中
            //左边的数大，不产生小和
            littleSum += copyData[leftIdx] * (right - rightIdx + 1);
            data[i] = copyData[leftIdx++];
        }else {
            data[i] = copyData[rightIdx++];
        }
    }
}

void xiaohe(int left, int right) {
    if (left == right) return;

    int mid = left + ((right - left)>>1);
    xiaohe(left, mid);
    xiaohe(mid+1, right);

    merge(left, mid, right);
}

void printData() {
    for (int i = 0; i < size; ++i)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

int main() {
    xiaohe(0, size-1);
    printData();
    cout << littleSum << endl;


    system("pause");
    return 0;
}