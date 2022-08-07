#include <iostream>
#include "binaryTree.h"
using namespace std;

int main() {
    binaryTree<int> bt;
    bt.createTree(0);
    cout << "****************" << endl;
    bt.preOrder_diedai();
    bt.preOrder();
    cout << "****************" << endl;
    bt.midOrder_diedai();
    bt.midOrder();
    cout << "****************" << endl;
    bt.postOrder_diedai();
    bt.postOrder();
    cout << "****************" << endl;
    bt.levelOrder();
    cout << "****************" << endl;
    cout << "width " << bt.width()  <<endl; 

    system("pause");
    return 0;
}
