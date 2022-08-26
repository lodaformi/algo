#include "adjMatrix_v2.h"
#include <iostream>
using namespace std;

int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};

    adjMatrix<char, int> am(arr, 5, 0);

    am.insert('a', 'b', 1);
    am.insert('a', 'c', 1);
    am.insert('a', 'd', 1);

    am.insert('b', 'a', 1);
    am.insert('b', 'e', 1);

    am.insert('c', 'a', 1);
    am.insert('c', 'e', 1);

    am.insert('d', 'a', 1);

    am.insert('e', 'b', 1);
    am.insert('e', 'c', 1);

    am.printGraph();

    am.bfs('a');
    am.dfs_stack('d');
    am.dfs_digui('d');
    cout << "---------------------------------" << endl;
    char arr2[] = {'a', 'b', 'c', 'd', 'e', 'f'};

    adjMatrix<char, int> am2(arr2, 6, 0);
    am2.insert('a', 'b', 1);
    am2.insert('a', 'c', 1);

    am2.insert('b', 'd', 1);
    am2.insert('b', 'e', 1);
    am2.insert('b', 'c', 1);
    am2.insert('b', 'a', 1);

    am2.insert('c', 'a', 1);
    am2.insert('c', 'b', 1);
    am2.insert('c', 'd', 1);
    am2.insert('c', 'e', 1);
    
    am2.insert('d', 'f', 1);
    am2.insert('d', 'e', 1);
    am2.insert('d', 'c', 1);
    am2.insert('d', 'b', 1);
    
    am2.insert('e', 'f', 1);
    am2.insert('e', 'd', 1);
    am2.insert('e', 'c', 1);
    am2.insert('e', 'b', 1);
    
    am2.insert('f', 'e', 1);
    am2.insert('f', 'd', 1);

    am2.printGraph();
    am2.eulerCircuit('c');
    am2.printGraph();

    cout <<"-------------------------" << endl;

    // 请补全代码，实现题目功能
    int n,m, start, end;
    cin >> n >> m;
    int *arr3 = new int[n];
    for(int i=0; i<n; ++i) {
        arr3[i] = i+1;
    }
    adjMatrix<int, int> am3(arr3, n, 0);

    for(int i=0; i<m; ++i) {
        cin >> start >> end;
        am3.insert(start, end, 1);
        am3.insert(end, start, 1);
    }

    am3.printGraph();
    am3.bfs_depthOne();

    system("pause");
    return 0;
}