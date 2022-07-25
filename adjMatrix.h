#include "myGraph.h"

template <class TypeOfVer, class TypeOfEdge>
class adjMatrix: public myGraph<TypeOfVer, TypeOfEdge>
{
private:
    TypeOfVer *ver;   //顶点集
    TypeOfEdge **edge; //二维数组
    TypeOfEdge noEdge;  //边不存在
    int find(TypeOfVer x) const;
    void dfs(int start, const bool visited[]) const;
public:
    void dfs() const;
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    adjMatrix(int Vsize, const TypeOfVer verList[], const TypeOfEdge noEdgeFlag);
    ~adjMatrix();
};

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer,TypeOfEdge>::dfs() const {
    bool *visited = new bool[Vers];
    for (int i = 0; i < Vers; ++i)
    {
        visited[i] = false;
    }

    cout << "dfs is ";
    for (int i = 0; i < Vers; ++i)
    {
        if (visited[i] == true)
        {
            continue;
        }
        dfs(i, visited);
        cout << endl;
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer,TypeOfEdge>::dfs(int start, bool visited[]) const {
    cout << start << " ";
    visited[start] = true;

    for (int col = 0; col < Vers; ++col)
    {
        if (edge[start][col] != noEdge && visited[col] == false)
        {
            dfs(col, visited);
        }
    }
}


template <class TypeOfVer, class TypeOfEdge>
adjMatrix<TypeOfVer,TypeOfEdge>::adjMatrix(int Vsize, const TypeOfVer verList[], const TypeOfEdge noEdgeFlag) {
    Vers = Vsize;
    Edges = 0;
    noEdge = noEdgeFlag;

    ver = new TypeOfVer[Vsize];
    for (int i = 0; i < Vsize; ++i)
    {
        ver[i] = verList[i];
    }

    edge = new TypeOfEdge*[Vsize];   //申请一个指针数组
    for (int i = 0; i < Vsize; ++i)
    {
        edge[i] = new TypeOfEdge[Vsize];  //申请一维数组，放到指针数组中
        for (int j = 0; j < Vsize; ++j)
        {
            edge[i][j] = noEdge;        //将二维数组所有值初始化为noEdge
        }
    }
} 

template <class TypeOfVer, class TypeOfEdge>
adjMatrix<TypeOfVer,TypeOfEdge>::~adjMatrix() {
    delete []ver;
    for (int i = 0; i < Vers; ++i)
    {
        delete[] edge[i];
    }
    delete []edge;
}

template <class TypeOfVer, class TypeOfEdge>
int adjMatrix<TypeOfVer, TypeOfEdge>::find(TypeOfVer x) const{
    for (int i = 0; i < Vers; ++i)
    {
        if (ver[i] == x)
        {
            return i;
        }
    }
    return -1;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer,TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int u = find(x);
    int v = find(y);
    edge[u][v] = w;
    ++Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer,TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    int u = find(x);
    int v = find(y);
    edge[u][v] = noEdge;
    --Edges;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrix<TypeOfVer,TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u = find(x);
    int v = find(y);
    if (edge[u][v] != noEdge)
    {
        return true;
    }else {
        return false;
    }
}