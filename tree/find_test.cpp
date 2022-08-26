/*
time : 20220809

*/
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

typedef struct Node
{
    int val;
    string anno;
    Node(int v, string s): val(v), anno(s) {}
    friend ostream &operator<<(ostream &output, const Node &node);
}Node;

ostream &operator<<(ostream &output, const Node &node) {
    output << node.val << "--" << node.anno << endl;
    return output;
}


int main() {
    unordered_set<Node*> set;
    Node* a = new Node(22, "hhh");
    Node* b = new Node(55, "xxx");
    set.emplace(a);
    set.emplace(b);

    unordered_set<Node*>::iterator iter;
    for (iter=set.begin(); iter != set.end(); iter++) {
        cout << (*iter) << " ";
    }
    cout << endl;
    iter = set.find(new Node(66, "abc"));
    if (iter != set.end())
    {
        cout << **iter << endl;
    }else {
        cout << "not found" << endl;
        cout << *(set.end()) << endl;
    }
    
    system("pause");
    return 0;
}