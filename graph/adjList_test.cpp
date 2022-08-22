#include "adjList_v2.h"
#include <iostream>
using namespace std;

int main () {
    char arr[] = {'a', 'b', 'c', 'd', 'e'};
    adjList<char, int> aList(arr, 5);
    aList.insert('a', 'b', 3);
    aList.insert('a', 'd', 6);
    aList.insert('a', 'c', 2);

    aList.insert('b', 'a', 3);
    aList.insert('b', 'c', 5);
    aList.insert('b', 'd', 100);
    aList.insert('b', 'e', 7);

    aList.insert('c', 'a', 2);
    aList.insert('c', 'b', 5);
    aList.insert('c', 'd', 4);

    aList.insert('d', 'a', 6);
    aList.insert('d', 'b', 100);
    aList.insert('d', 'c', 4);
    aList.insert('d', 'e', 1);

    aList.insert('e', 'b', 7);
    aList.insert('e', 'd', 1);

    aList.printGraph();
    cout << "------------" << endl;
    aList.bfs('b');
    aList.dfs('e');
    aList.dfs_stack('e');
    aList.dfs('c');
    aList.dfs_stack('c');

    aList.remove('b', 'e');
    aList.remove('e', 'b');
    aList.remove('b', 'd');
    aList.remove('d', 'b');
    cout << "------------" << endl;
    // cout << aList.exist('a', 'd') << endl;
    // cout << aList.exist('a', 'b') << endl;
    aList.printGraph();
    aList.dfs('c');
    aList.dfs_stack('c');
    cout << "------------" << endl;
    aList.eulerCircuit('d');

    cout << "------------" << endl;
    char arr2[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    adjList<char, int> aList2(arr2, 6);
    aList2.insert('a','b',1);
    aList2.insert('a','c',1);

    aList2.insert('b','e',1);
    aList2.insert('b','d',1);
    aList2.insert('b','c',1);
    aList2.insert('b','a',1);

    aList2.insert('c','a',1);
    aList2.insert('c','b',1);
    aList2.insert('c','e',1);
    aList2.insert('c','d',1);

    aList2.insert('d','f',1);
    aList2.insert('d','c',1);
    aList2.insert('d','b',1);
    aList2.insert('d','e',1);

    aList2.insert('e','f',1);
    aList2.insert('e','d',1);
    aList2.insert('e','b',1);
    aList2.insert('e','c',1);

    aList2.insert('f','e',1);
    aList2.insert('f','d',1);

    
    aList2.printGraph();
    aList2.eulerCircuit('b');
    cout << "------------" << endl;
    aList2.printGraph();
    system("pause");
    return 0;
}