#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "mySort.h"
using namespace std;


int main() {
    int arr[] = {2,5,242,35,25,638,48459,608,960,3,1,5,3,4,0,8,0,8,2,0,3,4,7,2,3,6,2,4,59,76,612,1234,7,6,3,6,7,2,4,1,2,3,4,1};
    int len = sizeof(arr) / sizeof(arr[0]);
    cout << "len " << len << endl;

    cout << "quickSort v1 " << endl;
    mySort<int> ms(len, arr);
    ms.quickSort_V1(0, len-1);
    ms.printArr();
    cout << "quickSort v2 " << endl;
    mySort<int> ms2(len, arr);
    ms2.quickSort_V2(0, len-1);
    ms2.printArr();

    cout << "bubbleSort v1 " << endl;
    mySort<int> ms3(len, arr);
    ms3.bubbleSort();
    ms3.printArr();
    cout << "insertSort v1 " << endl;
    mySort<int> ms4(len, arr);
    ms4.insertSort();
    ms4.printArr();
    cout << "mergeSort v1 " << endl;
    mySort<int> ms5(len, arr);
    ms5.mergeSort(0, len-1);
    ms5.printArr();

    system("pause");
    return 0;
}