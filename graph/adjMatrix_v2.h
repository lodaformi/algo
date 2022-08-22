#include "myGraph.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjMatrix : public myGraph<TypeOfVer, TypeOfEdge>
{
private:
    struct eulerNode
    {
        TypeOfVer ver;
        eulerNode *next;
        eulerNode(TypeOfVer v, eulerNode *n=nullptr) : ver(v), next(n) {}
    };
    
    TypeOfVer *verList;
    TypeOfEdge **edgeList;
    TypeOfEdge noEdge;
    int myFind(TypeOfVer x) const;
    void dfs_digui(TypeOfVer start, bool visited[]);
    void eulerCircuit(TypeOfVer start, eulerNode *&beg, eulerNode *&end);
    TypeOfEdge** clone();
public:
    void eulerCircuit(TypeOfVer start);
    void bfs(TypeOfVer start);
    void dfs_digui(TypeOfVer start);
    void dfs_stack(TypeOfVer start);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    void printGraph();
    adjMatrix(const TypeOfVer *arr, int size, const TypeOfEdge noEdgeFlag);
    ~adjMatrix();
};

template <class TypeOfVer, class TypeOfEdge>
TypeOfEdge** adjMatrix<TypeOfVer, TypeOfEdge>::clone() {
    TypeOfEdge **tmp = new TypeOfEdge*[this->Vers];
    
    for (int row = 0; row < this->Vers; ++row)
    {
        tmp[row] = new TypeOfEdge{this->Vers};
        for (int col = 0; col < this->Vers; ++col)
        {
            tmp[row][col] = edgeList[row][col];
        }
    }
    return tmp;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer, TypeOfEdge>::eulerCircuit(TypeOfVer start, eulerNode *&beg, eulerNode *&end) {
    beg = end = new eulerNode(start);

    int u = myFind(start);
    //从起点出发，做一次dfs，访问过的边就删除，但不能回溯（所以不能递归调用）
    for (int col = 0; col < this->Vers; ++col)
    {
        if (edgeList[u][col] != noEdge)
        {
            //将顶点尾插到单链表中
            end->next = new eulerNode(verList[col]);
            end = end->next;

            //删除访问过的边，在无向图，边要删两次
            remove(start, verList[col]);
            remove(verList[col], start);

            //更新下一次需要用的条件
            //上面remove中用到了变量start，更新start
            start = verList[col];
            //edgeList中用到了u，更新u
            u = myFind(start);
            //更新u之后，二维数组中更换了行，所以列所以也要从0开始
            col=0;
        }
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer, TypeOfEdge>::eulerCircuit(TypeOfVer start) {
    //判断度数，必须全是偶数
    int degree;
    for (int row = 0; row < this->Vers; ++row)
    {
        degree = 0;
        for (int col = 0; col < this->Vers; ++col)
        {
            if (edgeList[row][col] != noEdge)
            {
                ++degree;
            }
        }
        if (degree == 0 || degree %2 != 0)
        {
            cout << "eulerCircuit doesn't exist!" << endl;
            return;
        }
    }
    
    //clone原图
    TypeOfEdge **cloneGraph = clone();

    //从一个顶点出发找一条路径，保存到单链表中
    eulerNode *beg, *end, *tbeg, *tend, *ptr, *tmp;
    int idx;
    eulerCircuit(start, beg, end);

    //判断上述路径中是否存在顶点还有边未访问到，若有，则从这个有边的顶点出发再找一段路径，拼接到原来的路径中
    ptr = beg;
    while (ptr->next != nullptr)    //因后面要拼接，删除一个顶点，所以站在前一个节点进行判断
    {
        idx = myFind(ptr->next->ver);
        for (int col = 0; col < this->Vers; ++col)
        {
            if (edgeList[idx][col] != noEdge)
            {
                eulerCircuit(ptr->next->ver, tbeg, tend);

                tmp = ptr->next;
                tend->next = tmp->next;
                ptr->next = tbeg;
                delete tmp;
            }
        }
        ptr = ptr->next;
    }
    
    //删除旧图，恢复原图
    for (int i = 0; i < this->Vers; ++i)
    {
        delete[] edgeList[i];
    }
    delete[] edgeList;
    
    edgeList = cloneGraph;
    
    //输出欧拉路径，同时将链表删除
    ptr = beg;
    cout << "eulerCircuit is: ";
    while (beg != nullptr)
    {
        cout << beg->ver << "-> ";
        ptr = beg;
        beg = beg->next;
        delete ptr;
    }
    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer, TypeOfEdge>::printGraph() {
    for (int i = 0; i < this->Vers; i++)
    {
        for (int j = 0; j < this->Vers; ++j)
        {
            cout << edgeList[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer, TypeOfEdge>::dfs_digui(TypeOfVer start) {
    cout << "dfs_digui is: ";
    bool visited[this->Vers] = {false};
    dfs_digui(start, visited);
    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer, TypeOfEdge>::dfs_digui(TypeOfVer start, bool visited[]) {
    cout << start << " ";
    visited[myFind(start)] = true;

    int currentNodeIdx = myFind(start);
    for (int i = 0; i < this->Vers; ++i)
    {
        if (edgeList[currentNodeIdx][i] != noEdge && visited[i] == false)
        {
            dfs_digui(verList[i], visited);
        }
    }
}

//元素在入栈的时候访问
template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer, TypeOfEdge>::dfs_stack(TypeOfVer start) {
    cout << "dfs_stack is: ";
    TypeOfVer currentNode;
    int currentNodeIdx = myFind(start);
    stack<TypeOfVer> manual_stack;    
    bool visited[this->Vers] = {false};  

    manual_stack.push(start);       //将起点入栈
    cout << start << " ";           //元素入栈的时候访问
    visited[currentNodeIdx] = true;     //更新访问标记

    while (!manual_stack.empty())  //如果栈不为空
    {
        currentNode = manual_stack.top();       //栈顶元素出栈
        manual_stack.pop();
        currentNodeIdx = myFind(currentNode);
        for (int i = 0; i < this->Vers; ++i)        //访问出栈元素的邻居
        {
            if (edgeList[currentNodeIdx][i] != noEdge && visited[i] == false)
            {
                manual_stack.push(currentNode);     //将栈顶元素重新入栈，实现回溯
                manual_stack.push(verList[i]);      //将邻居入栈
                cout << verList[i] << " ";
                visited[i] = true;                  //更新访问标记
                break;                              //只访问一个未被访问过的邻居
            }
        }
    }
    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer, TypeOfEdge>::bfs(TypeOfVer start) {
    TypeOfVer currentNode;
    int currentNodeIdx = myFind(start);

    queue<TypeOfVer> que;               //队列
    bool visited[this->Vers] = {false}; //访问标记
    
    que.push(start);                    //起点进队
    visited[currentNodeIdx] = true;     //更新起点访问标记

    cout << "bfs is: ";
    while (!que.empty())            //队列不为空
    {
        currentNode = que.front();  //队头元素出队
        que.pop();
        cout << currentNode << " ";     //出队的时候访问元素

        currentNodeIdx = myFind(currentNode);
        for (int i = 0; i < this->Vers; ++i)        //访问出队元素的邻居
        {
            //如果两者之间存在边，且邻居没有被访问过
            if (edgeList[currentNodeIdx][i] != noEdge && visited[i] == false)
            {
                que.push(verList[i]);           //邻居入队
                visited[i] = true;              //入队的时候，设置访问标记为true
            }
        }
    }
    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
int adjMatrix<TypeOfVer, TypeOfEdge>::myFind(TypeOfVer x) const{
    for (int i = 0; i < this->Vers; ++i)
    {
        if (verList[i] == x)
        {
            return i;
        }
    }
    return -1;    //不存在返回-1
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int u = myFind(x), v=myFind(y);
    edgeList[u][v] = w;
    ++this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrix<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u = myFind(x), v=myFind(y);
    return edgeList[u][v] != noEdge ? true : false;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrix<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    if (!exist(x,y)) return;

    int u = myFind(x), v=myFind(y);
    edgeList[u][v] = noEdge;
    --this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
adjMatrix<TypeOfVer, TypeOfEdge>::adjMatrix(const TypeOfVer *arr, int size, const TypeOfEdge noEdgeFlag) {
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

// 为什么在析构时会报错？？？？
template <class TypeOfVer, class TypeOfEdge>
adjMatrix<TypeOfVer, TypeOfEdge>::~adjMatrix() {
    // cout << "auto call deconstructor function" << endl;
    delete[] verList;
    // cout << "this->vers is : " << this->Vers << endl;
    for (int i = 0; i < this->Vers; ++i)
    {
        delete[] edgeList[i];
    }
    delete[] edgeList;
}