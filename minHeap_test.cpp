#include <iostream>
#include "seqQueue_minHeap.h"
using namespace std;

int main() {
    
    int arr[] = {3,4,5,76,1,8,1,2,3,9,6};
    int len = sizeof(arr)/sizeof(arr[0]);

    seqQueue_minHeap<int> sm(arr, len);
    sm.heapSort();

    cout << "***************" << endl;
    seqQueue_minHeap<int> sm2(10);
    for (int i = 0; i < len; ++i)
    {
        sm2.enQueue(arr[i]);
    }
    sm2.heapSort();


    system("pause");
    return 0;
}