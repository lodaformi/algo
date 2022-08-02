#include <iostream>
using namespace std;

/*
一个数组中只有一个数字出现了奇数次，其他都出现了偶数次，求出现奇数次的这个数；
*/

void findOneOddNum(int arr[], int size) {
    int x=0;
    for (int i = 0; i < size; ++i)
    {
        x ^= arr[i];
    }
    cout << x << endl;
}

/*
一个数组中有两个不相等的数字出现了奇数次，其他都出现了偶数次，求出现奇数次的这两个数；
*/
void findTwoOddNum(int arr[], int size) {
    int x=0, xor2=0;    //必须初始化为0
    for (int i = 0; i < size; ++i)
    {
        x ^= arr[i];
    }

    //res = a ^ b，因为a != b，所以a ^ b != 0
    int res = x & (~x + 1);         //提取出一个数最右边的1，其他位置全是0
    cout << "res " << res << endl;
    for (int i = 0; i < size; ++i)
    {
        //用res将数组中的数分成两类，一类是该位置上是0，一类是该位置上是1,
        //0和1都可以使用
        if ((res & arr[i]) == 0)
        {
            // cout << "i = " << i << endl;
            xor2 ^= arr[i];
        }
    }

    cout << xor2 << "--" << (x ^ xor2) << endl;
}

int main() {
    int arr[] = {11,11,3,44,3};
    findOneOddNum(arr, sizeof(arr)/sizeof(arr[0]));
    
    int arr2[] = {234,234,234,11,11,99,44,44};
    findTwoOddNum(arr2, sizeof(arr2)/sizeof(arr2[0]));

    system("pause");
    return 0;
}