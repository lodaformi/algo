#include <iostream>
#include <queue>
#include "myGraph.h"
using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjMatrix: public myGraph<TypeOfVer, TypeOfEdge>
{
private:
    TypeOfVer *ver;   //顶点集
    TypeOfEdge **edge; //二维数组
    TypeOfEdge noEdge;  //边不存在
    int find(TypeOfVer x) const;
    void dfs(int start, bool visited[]) const;
public:
    void dfs(TypeOfVer start) const;
    void bfs(TypeOfVer start) const;
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    adjMatrix(int Vsize, const TypeOfVer verList[], const TypeOfEdge noEdgeFlag);
    ~adjMatrix();
};

template <class TypeofVer, class TypeOfEdge>
void adjList<TypeofVer, TypeOfEdge>::bfs(TypeOfVer start) const{
    bool *visited = new bool[this->Vers];
    for (int i = 0; i < this->Vers; ++i)
    {
        visited[i] = false;
    }
    queue<int> que;
    int currentNode = find(start);
    que.push(currentNode);
    //先从start指定起点做一次bfs遍历
    while (!que.empty())
    {
        currentNode = que.front();
        que.pop();
        // if (visited[currentNode] == true) continue;
        cout << ver[currentNode] << " ";
        // visited[currentNode] = true;

        //检查与currentNode相邻的边
        for (int i = 0; i < this->Vers; ++i)
        {
            if (edge[currentNode][i] != noEdge && visited[i] == false)
            {
                que.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer,TypeOfEdge>::dfs(TypeOfVer start) const {
    bool *visited = new bool[this->Vers];
    for (int i = 0; i < this->Vers; ++i)
    {
        visited[i] = false;
    }

    //指定一个起点先遍历一遍
    cout << "dfs is ";
    int u=find(start);
    dfs(u, visited);
    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer,TypeOfEdge>::dfs(int start, bool visited[]) const {
    cout << ver[start] << " ";
    visited[start] = true;

    for (int col = 0; col < this->Vers; ++col)
    {
        if (edge[start][col] != noEdge && visited[col] == false)
        {
            dfs(col, visited);
        }
    }
}


template <class TypeOfVer, class TypeOfEdge>
adjMatrix<TypeOfVer,TypeOfEdge>::adjMatrix(int Vsize, const TypeOfVer verList[], const TypeOfEdge noEdgeFlag) {
    this->Vers = Vsize;
    this->Edges = 0;
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
    for (int i = 0; i < this->Vers; ++i)
    {
        delete[] edge[i];
    }
    delete []edge;
}

template <class TypeOfVer, class TypeOfEdge>
int adjMatrix<TypeOfVer, TypeOfEdge>::find(TypeOfVer x) const{
    for (int i = 0; i < this->Vers; ++i)
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
    int u = find(x), v = find(y);
    edge[u][v] = w;
    ++this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer,TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    int u = find(x), v = find(y);
    edge[u][v] = noEdge;
    --this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrix<TypeOfVer,TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u = find(x), v = find(y);
    return edgeList[u][v] != noEdge ? true : false;
}