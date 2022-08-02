#include <iostream>
using namespace std;

template <class elemType>
class myBinarySearch
{
private:
    int size;
    elemType *arr;
public:
    myBinarySearch(/* args */);
    ~myBinarySearch();
    //查找一个数，相当于从左向右第一个大于等于x的数
    void find1(elemType x) {
        int L=0, R=size-1;
        while (L <R)
        {
            // int mid = L + (R-L)/2;
            int mid = L + ((R-L) >> 1);
            if (arr[mid] < x)
            {
                L = mid + 1;            
            }else {  //arr[mid] >= x, mid可能是解
                R = mid;
            }
        }   //当L==R时退出循环

        if (arr[L] == x)
        {
            cout << "find x" << endl;
        } else {
            cout << "not find x in arr" << endl;
        }
    }

};

