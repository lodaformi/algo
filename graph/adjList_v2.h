#include "myGraph.h"
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

template<class TypeOfVer, class TypeOfEdge>
class adjList: public myGraph<TypeOfVer, TypeOfEdge>
{
private:
    struct edgeNode
    {
        TypeOfVer end;
        TypeOfEdge weight;
        edgeNode* next;
        edgeNode(TypeOfVer e, TypeOfEdge w, edgeNode *n=nullptr):end(e), weight(w), next(n) {}
    };

    struct verNode
    {
        TypeOfVer ver;
        edgeNode *head;
        verNode(edgeNode *h=nullptr):head(h) {}
    };
    struct EulerNode
    {
        TypeOfVer ver;
        EulerNode *next;
        EulerNode(TypeOfVer v, EulerNode *n=nullptr): ver(v), next(n) {}
    };
    
    verNode *verList;
    int myFind(TypeOfVer x) const;
    void dfs(TypeOfVer start, bool visited[]) const;
    verNode* clone();
    //注意这里beg和end使用的是指针引用，也就是说指针的返回值要带回到上层函数中
    void eulerCircuit(TypeOfVer start, EulerNode *&beg, EulerNode *&end);
public:
    void eulerCircuit(TypeOfVer start);
    void dfs(TypeOfVer start);
    void dfs_stack(TypeOfVer start);
    void bfs(TypeOfVer start);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    void printGraph();
    adjList(const TypeOfVer vList[], int size);
    ~adjList();
};

template<class TypeOfVer, class TypeOfEdge>
typename adjList<TypeOfVer, TypeOfEdge>::verNode* adjList<TypeOfVer, TypeOfEdge>::clone() {
    verNode *tmp = new verNode[this->Vers];
    edgeNode *ptr;
    for (int i = 0; i < this->Vers; ++i)
    {
        tmp[i].ver = verList[i].ver;        //复制顶点

        ptr = verList[i].head;
        while (ptr != nullptr)  //复制该顶点的单链表
        {
            //头插，这clone之后形成的图，每个顶点的单链表顺序与原图中的顺序是反的
            tmp[i].head = new edgeNode(ptr->end, ptr->weight, tmp[i].head);
            ptr = ptr->next;
        }
    }
    return tmp;
}

template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::eulerCircuit(TypeOfVer start, EulerNode *&beg, EulerNode *&end) {
    int startIdx = myFind(start);
    TypeOfVer nextVer;
    beg = end = new EulerNode(start);
    //做一次dfs深度优先遍历，但不能回溯
    while (verList[startIdx].head != nullptr)
    {
        nextVer = verList[startIdx].head->end;

        //将路径保存到链表当中，尾插
        end->next = new EulerNode(nextVer);
        end = end->next;

        //删除图中已经被找过的路径，无向图中边会存储两次，所以删两次
        remove(start, nextVer);
        remove(nextVer, start);

        //更新下一次循环需要用到的条件，就不存在回溯的情况
        //下面两条语句不能合并
        //必须更新start，因为下一次remove是已nextVer为起点
        start=nextVer;
        startIdx = myFind(start);
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

    //三：检查这段路径上的顶点是否还存在未被访问的边，若有则与已经形成的路径进行拼接
    tptr = beg;

    //路径拼接时要删除一个节点，所以while站在前一个节点判断
    while (tptr->next != nullptr) {
        u = myFind(tptr->next->ver);
        if (verList[u].head != nullptr)
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
    delete []verList;
    verList = cloneGraph;

    //五：输出最终的欧拉回路，输出的同时将节点删除
    tptr = beg;
    cout << "EulerCircuit is : " ;
    while (beg != nullptr)
    {
        cout << beg->ver << " -> ";
        tptr = beg;
        beg = beg->next;
        delete tptr;
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

template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::dfs_stack(TypeOfVer start) {
    TypeOfVer node;
    edgeNode *ptr;
    unordered_set<TypeOfVer> visited;
    stack<TypeOfVer> manual_stack;
    
    cout << "dfs_stack is: ";
    manual_stack.push(start);
    visited.emplace(start);

    cout << start << " ";
    while (!manual_stack.empty())
    {
        node = manual_stack.top();
        manual_stack.pop();
        //不在弹出栈的时候访问元素，因为当一个顶点有多个邻居时会多次入栈、出栈
        // cout << node << " ";

        ptr = verList[myFind(node)].head;
        while (ptr != nullptr)
        {
            //如果visited中不存在邻居顶点，则访问该邻居
            if (visited.find(ptr->end) == visited.end())
            {
                //必须把该顶点重新入栈，可以实现回溯
                manual_stack.push(node);
                //将邻居入栈
                manual_stack.push(ptr->end);
                //在入栈的时候访问
                cout << ptr->end << " ";
                //更新访问标记
                visited.emplace(ptr->end);
                break;  //只访问该顶点的一个邻居
            }
            ptr = ptr->next;
        }
    }
    cout << endl;
}

// width first search
template<class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::bfs(TypeOfVer start) {
    TypeOfVer currentVer;
    edgeNode *ptr;
    int u = myFind(start);

    bool visited[this->Vers] = {false};     
    queue<TypeOfVer> que;

    que.push(start);
    visited[u] = true;

    cout << "bfs is: ";
    while (!que.empty())
    {
        currentVer = que.front();
        que.pop();
        cout << currentVer << " ";      //打印出队元素

        u = myFind(currentVer);
        ptr = verList[u].head;
        //这样写不对，在碰到一个false后，直接退出了while循环，后续的元素都无法判断
        // while (ptr != nullptr && visited[myFind(ptr->end)] == false)
        // {
        //     que.push(ptr->end);
        //     ptr = ptr->next;
        // }

        while (ptr != nullptr)
        {
            if (visited[myFind(ptr->end)] == false)
            {
                que.push(ptr->end);
                visited[myFind(ptr->end)]=true;     //入队的时候，设置访问标记为true
            }
            ptr = ptr->next;
        }
    }
    cout << endl;
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
    //如果不是第一个节点，删除节点须站在前一个节点上，所以判断是ptr->next
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