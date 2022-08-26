#include <iostream>
using namespace std;

void foo(int* x, int** y) {
    // modifying x or y here will modify a or b in main
    *x = 50;
    // **y = 60;
}
 
int main() {
    int val = 42;
    int *a  = &val;
    int **b = &a;

    foo(a, b);
    cout << val << endl;
    system("pause");
    return 0;
}