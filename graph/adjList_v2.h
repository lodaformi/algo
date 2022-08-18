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
    verNode *verList;
    int myFind(TypeOfVer x) const;
    void dfs(TypeOfVer start, bool visited[]) const;
public:
    void dfs(TypeOfVer start);
    void bfs(TypeOfVer start);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    void printGraph();
    adjList(const TypeOfVer vList[], int size);
    ~adjList();
};

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