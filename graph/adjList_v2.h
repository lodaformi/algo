#include "myGraph.h"
#include <iostream>
#include <queue>
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
    typedef struct EulerNode
    {
        TypeOfVer ver;
        EulerNode *next;
        EulerNod(TypeOfVer v, EulerNode *n=nullptr): ver(v), next(n) {}
    }EulerNode;
    
    verNode *verList;
    int myFind(TypeOfVer x) const;
    void dfs(TypeOfVer start, bool visited[]) const;
    verNode* clone();
    void eulerCircuit(TypeOfVer start, EulerNode *beg, EulerNode *end);
public:
    void eulerCircuit(TypeOfVer start);
    void dfs(TypeOfVer start);
    void bfs(TypeOfVer start);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    void printGraph();
    adjList(const TypeOfVer vList[], int size);
    ~adjList();
};

template<class TypeOfVer, class TypeOfEdge>
verNode* adjList<TypeOfVer, TypeOfEdge>::clone() {
    verNode *tmp = new verNode[this->Vers];
    edgeNode *ptr;
    for (int i = 0; i < this->Vers; ++i)
    {
        tmp[i].ver = verList[i].ver;

        ptr = verList[i].head;
        while (ptr != nullptr)
        {
            //头插，这clone之后形成的图，每个顶点的单链表顺序与原图中的顺序是反的
            tmp[i].head = new edgeNode(ptr->end, ptr->weight, tmp[i].head);
            ptr = ptr->next;
        }
    }
    return tmp;
}

template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::eulerCircuit(TypeOfVer start, EulerNode *beg, EulerNode *end) {
    int u = myFind(start);
    beg = end = new EulerNode(start);
    edgeNode *ptr = verList[u].head;
    //做一次dfs深度优先遍历，但不能回溯
    while (ptr != nullptr)
    {
        //将路径保存到链表当中，尾插
        end->next = new EulerNode(ptr->end);
        end = end->next;

        //删除图中已经被找过的路径
        remove(start, end->ver);
        remove(end->ver, start);

        //更新下一次循环需要用到的条件，就不存在回溯的情况
        start = end->ver;
        u = myFind(start);
        ptr = verList[u].head;
    }
}

template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::eulerCircuit(TypeOfVer start) {
    //一：统计每个顶点的度数，若存在度为零或者奇数的顶点直接return
    int degree;
    edgeNode *ptr;
    for (int i = 0; i < this->Vers; ++i)
    {
        degree = 0;
        ptr = verList[i].head;
        while (ptr != nullptr)
        {
            ++degree;
            ptr = ptr->next;
        }
        if (degree == 0 || degree %2 != 0)
        {
            cout << "EulerCircuit doesn't exist!" << endl;
            return;
        }
    }
    //二：因在寻找欧拉回路的过程中要破坏图，先对原图拷贝一份，用于后续恢复
    verNode *cloneGraph = clone();

    //二：从起点开始寻找一段欧拉路径
    int u;
    EulerNode *beg, *end, *tbeg, *tend, *tptr, *del;
    eulerCircuit(start, beg, end);

    //三：检查是否这段路径上的顶点是否还存在未被访问的边，若有则与前面的路径进行拼接
    tptr = beg;

    while (tptr->next != nullptr) {
        u = myFind(tptr->next->ver);
        ptr = verList[u].head;
        if (ptr != nullptr)
        {
            eulerCircuit(verList[u].ver, tbeg, tend);
            //路径拼接
            del = tptr->next;
            tend->next = del->next;
            tptr->next = tbeg;
            delete del;
        }
        tptr = tptr->next;
    }
    //四：恢复被破坏的图
    verList = cloneGraph;

    //五：输出最终的欧拉回路
    tptr = beg;
    cout << "EulerCircuit is : " ;
    while (tptr != nullptr)
    {
        cout << tptr->ver << " -> ";
        tptr = tptr->next;
    }
    cout << endl;
}


// depth first search
template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::dfs(TypeOfVer start) {
    bool visited[this->Vers] = {false};

    // 先从起始点开始一次深度优先搜索
    cout << "dfs is: ";
    dfs(start, visited);
    cout << endl;

    //看是否存在其他联通分量
    for (int i = 0; i < this->Vers; ++i)
    {
        if (visited[i] == true) continue;
        dfs(verList[i].ver, visited);
        cout << endl;            
    }
}   

template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::dfs(TypeOfVer start, bool visited[]) const{
    int u = myFind(start);
    edgeNode *ptr = verList[u].head;
    //处理(打印)节点，并将访问标志置为true
    cout << verList[u].ver << " ";
    visited[u] = true;

    // 访问任意一个未被访问的邻居顶点
    // 如果当前顶点没有邻居，或者有邻居但是邻居都被访问过了，则回溯到上一层
    while (ptr != nullptr)
    {
        //如果邻居顶点未被访问，从这个顶点出发继续dfs
        if (visited[myFind(ptr->end)] == false)
        {
            dfs(ptr->end, visited);
        }
        ptr = ptr->next;
    }
} 

// width first search
template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::bfs(TypeOfVer start) {
    int u = myFind(start);
    bool visited[this->Vers] = {false}; 
    
    TypeOfVer currentVer= verList[u].ver;
    edgeNode *ptr;
    queue<TypeOfVer> que;
    que.push(currentVer);

    // 从出发点开始一次bfs
    cout << "bfs is: ";
    while (!que.empty())
    {
        currentVer = que.front();
        que.pop();
        u = myFind(currentVer);
        //这条判断语句要加上，具体理由见下方while循环处
        //是为了过滤重复添加的元素，这样后面的元素就不会重复输出
        if (visited[u] == true) continue;
        cout << currentVer << " ";
        visited[u]=true;

        ptr = verList[u].head;
        //这样写不对，在碰到一个false后，直接退出了while循环，后续的元素都无法判断
        // while (ptr != nullptr && visited[myFind(ptr->end)] == false)
        // {
        //     que.push(ptr->end);
        //     ptr = ptr->next;
        // }

        //要判断所有的邻居元素，在没有被访问，即false时才加入队列
        //就造成一个问题，已经在队中的元素在未弹出处理(打印)时，visited标记还是false
        //这样会添加重复的元素，特别是对于无向图而言，所以在上面弹出元素时还要再次判断标记
        //这样后面的元素就不会重复输出
        while (ptr != nullptr)
        {
            if (visited[myFind(ptr->end)] == false)
            {
                que.push(ptr->end);
            }
            ptr = ptr->next;
        }
    }
    cout << endl;

    // 为防止存在其他联通分量，检查是否存在这样的点
    for (int i = 0; i < this->Vers; ++i)
    {
        if (visited[i] == true) continue;
        currentVer= verList[i].ver;
        que.push(currentVer);

        while (!que.empty())
        {
            currentVer = que.front();
            que.pop();
            u = myFind(currentVer);
            if (visited[u] == true) continue;
            cout << currentVer << " ";
            visited[u]=true;

            ptr = verList[u].head;
            while (ptr != nullptr)
            {
                if (visited[myFind(ptr->end)] == false)
                {
                    que.push(ptr->end);
                }
                ptr = ptr->next;
            }
        }
        cout << endl;
    }
}


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