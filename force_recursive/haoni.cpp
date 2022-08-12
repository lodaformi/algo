#include <iostream>
#include <string>
using namespace std;

void haoni(int n, string start, string end, string aux) {
    if (n == 1)
    {
        cout << "Move " << n << " from " << start << " to " << end << endl;
        return;
    }
    haoni(n-1, start, aux, end);
    cout << "Move " << n << " from " << start << " to " << end << endl;
    haoni(n-1, aux, end, start);
}


int main() {

    haoni(4, "left", "right", "mid");
    system("pause");
    return 0;
}