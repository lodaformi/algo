#include <iostream>
#include <string.h>
#include "adjMatrix.h"
using namespace std;

int main() {
    char ver[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    int len = strlen(ver);
    cout << "strlen " << len << endl;
    adjMatrix<char, int> am(len, ver, 0);

    am.insert('A','G',1);
    am.insert('B','C',1);
    am.insert('B','G',1);
    am.insert('C','D',1);
    am.insert('D','A',1);
    am.insert('D','F',1);
    am.insert('E','B',1);
    am.insert('E','C',1);
    am.insert('F','B',1);
    am.insert('F','E',1);
    am.insert('G','D',1);

    am.dfs('E');

    system("pause");
    return 0;
}