#include "myGraph.h"
#include <iostream>
using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjMatrix : public myGraph<TypeOfVer, TypeOfEdge>
{
private:
    TypeOfVer *verList;
    TypeOfEdge **edgeList;
    TypeOfEdge noEdge;
    int myFind(TypeOfVer x);
public:
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    adjMatrix(TypeOfVer *arr, int size, const TypeOfEdge noEdgeFlag);
    ~adjMatrix();
};

template <class TypeOfVer, class TypeOfEdge>
adjMatrix<TypeOfVer, TypeOfEdge>::adjMatrix(TypeOfVer *arr, int size, const TypeOfEdge noEdgeFlag) {
    this->Vers = size;
    this->Edges = 0;
    noEdge =noEdgeFlag;
    verList = new TypeOfVer[size];
    for (int i = 0; i < size; ++i)
    {
        verList[i] = arr[i];
    }
    
    TypeOfEdge *tmp;
    edgeList = new TypeOfEdge*[size];  //申请行

    for (int i = 0; i < size; ++i)
    {
        edgeList[i] = new TypeOfEdge[size]; //申请列
        for (int j = 0; j < size; ++j)
        {
            edgeList[i][j] = noEdge;
        }
    }
}






