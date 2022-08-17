#include "myGraph.h"
#include <iostream>
using namespace std;

template<class TypeOfVer, class TypeOfEdge>
class adjList: public myGraph<TypeOfVer, TypeOfEdge>
{
private:
    typedef struct edgeNode
    {
        TypeOfVer end;
        TypeOfEdge weight;
        edgeNode* next;
        edgeNode(TypeOfVer e, TypeOfEdge w, edgeNode *n=nullptr):end(e), weight(w), next(n) {}
    }edgeNode;

    typedef struct verNode
    {
        TypeOfVer ver;
        edgeNode *head;
        verNode(edgeNode *h=nullptr):head(h) {}
    }verNode;
    verNode *verList;
    // int Vers, Edges;
public:
    int myFind(TypeOfVer x) const;
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    void printGraph();
    adjList(const TypeOfVer vList[], int size);
    ~adjList();
};

template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::printGraph() {
    edgeNode *ptr;
    for (int i = 0; i < this->Vers; ++i)
    {
        ptr = verList[i].head;
        cout << verList[i].ver << "->";
        while (ptr!= nullptr)
        {
            cout << ptr->end << " " << ptr->weight << "->";
            ptr = ptr->next;
        }
        cout << endl;
    }
}

template<class TypeOfVer, class TypeOfEdge>
adjList<TypeOfVer, TypeOfEdge>::~adjList() {
    edgeNode *ptr;
    for (int i = 0; i < this->Vers; ++i)
    {
        //method one
        // ptr = verList[i].head, *tmp;
        // while (ptr != nullptr)
        // {
        //     tmp = ptr;
        //     ptr = ptr->next;
        //     delete tmp;
        //     --this->Edges;
        // }

        // optimized method 
        while ((ptr = verList[i].head) != nullptr)
        {
            verList[i].head = ptr->next;
            delete ptr;
            --this->Edges;
        }
    }
    delete []verList;
}

template<class TypeOfVer, class TypeOfEdge>
adjList<TypeOfVer, TypeOfEdge>::adjList(const TypeOfVer vList[], int size) {
    this->Vers = size;
    this->Edges = 0;
    verList = new verNode[size];
    for (int i = 0; i < size; ++i)
    {
        verList[i].ver = vList[i];
    }
}

template<class TypeOfVer, class TypeOfEdge>
int adjList<TypeOfVer, TypeOfEdge>::myFind(TypeOfVer x) const{
    for (int i = 0; i < this->Vers; ++i)
    {
        if (verList[i].ver == x)
        {
            return i;
        }
    }
    return -1;
}

//头插
template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int u = myFind(x);
    verList[u].head = new edgeNode(y, w, verList[u].head);
    ++this->Edges;
}

template<class TypeOfVer, class TypeOfEdge>
bool adjList<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u = myFind(x);
    edgeNode *ptr = verList[u].head;
    while (ptr != nullptr && ptr->end != y)
        ptr = ptr->next;

    if (ptr != nullptr)
        return true;
    return false;
}

//删除节点要找到该节点的前一个节点
//删除分两种情况，删除第一个节点和非第一个节点
template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    if (!exist(x,y)) return;
    
    int u = myFind(x);
    edgeNode *ptr = verList[u].head;
    //如果是第一个节点
    if (ptr->end == y)
    {
        verList[u].head = ptr->next;
        --this->Edges;
        delete ptr;
        return;
    }
    //如果不是第一个节点
    edgeNode *tmp;
    while (ptr->next != nullptr && ptr->next->end != y)
        ptr = ptr->next;

    if (ptr->next != nullptr)
    {
        tmp = ptr->next;
        ptr->next = tmp->next;
        --this->Edges;
        delete tmp;
    }
}