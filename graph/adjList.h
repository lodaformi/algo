#include "myGraph.h"
#include <queue>
#include <iostream> 
using namespace std;

template <class TypeOfVer, class TypeOfEdge>
class adjList : public myGraph<TypeOfVer, TypeOfEdge>
{
private:
    struct edgeNode
    {
        TypeOfVer end;
        TypeOfEdge weight;
        edgeNode *next;
        edgeNode(TypeOfVer e, TypeOfEdge w, edgeNode *n = nullptr): end(e), weight(w), next(n) {}
    };
    struct verNode
    {
        TypeOfVer ver;
        edgeNode *head;
        verNode(edgeNode *h = nullptr):head(h) {}
    };
    struct eulerNode
    {
        int nodeNum;
        eulerNode *next;
        eulerNode(int ver, eulerNode *n=nullptr):nodeNum(ver), next(n) {} 
    };
    
    verNode *verList;
    int myFind(TypeOfVer x) const;
    void dfs(int start, bool visited[]) const;
    void eulerCircuit(int start, eulerNode *&beg , eulerNode *&end);
public:
    void eulerCircuit(TypeOfVer start);
    verNode* clone() const;
    void dfs() const;
    void bfs(TypeOfVer start) const;
    adjList(int size, const TypeOfVer ver[]);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    ~adjList();
};

template <class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::eulerCircuit(TypeOfVer start) {
    int degree;
    edgeNode *p;

    //判断所有节点的度是否为偶数
    for (int i = 0; i < this->Vers; ++i)
    {
        degree = 0;
        p = verList[i].head;
        while (p != nullptr)
        {
            ++degree;
            p = p->next;
        }
        //如果该节点的度数为0或者为奇数，不存在欧拉回路，退出函数
        if (degree == 0 || degree % 2 != 0)
        {
            cout << "eulerCircuit doesn't exist." << endl;
            return;
        }
    }
    
    //存在欧拉回路
    int u=myFind(start);
    verNode *tmpList = clone();

    //欧拉回路的路径使用单链表表示
    eulerNode *beg, *end, *tp, *tb, *te, *tq;
    //先找一段路径
    eulerCircuit(u, beg, end);

    //在这段路径中寻找还有边未被访问的节点，即这个节点的邻接表单链表不为空
    while (true)
    {
        tp = beg;
        while (tp != nullptr)
        {
            if (verList[tp->next->nodeNum].head != nullptr) break;
            else tp = tp->next;                
        }
        //如果上面的while循环退出条件是tp == nullptr，则说明第一次找的欧拉回路包含了所有的边
        if (tp == nullptr) break;   //退出外层while死循环
        //如果内层while循环是break出来的，说明第一次找的路径不全，还有边未被访问到
        //则从这个起点开始找一次路径
        tq = tp->next;
        eulerCircuit(tq->nodeNum, tb, te);
        te->next = tq->next;
        tp->next = tb;
        delete tq;
    }
    
    //恢复原图
    delete []verList;
    verList = tmpList;    

    //输出欧拉回路，遍历路径的同时删除节点
    cout << "EulerCircuit is: ";
    while (beg != nullptr)
    {
        cout << verList[beg->nodeNum].ver << " ";
        tp = beg;
        beg = beg->next;
        delete tp;
    }
    cout << endl;
}


template <class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::eulerCircuit(int start, eulerNode *&beg , eulerNode *&end) {
    beg = end = new eulerNode(start);   //将起始节点放入到欧拉路径中
    int nextNode;
    while (verList[start].head != nullptr)  //当该节点还有路径没有被访问
    {   
        nextNode = verList[start].head->end;
        //经过一条边就把这条边删除，因为无向联通图的边会存储两次，所以删两次
        remove(verList[start].ver, verList[nextNode].ver);
        remove(verList[nextNode].ver, verList[start].ver);

        //深度优先遍历的变形，因为不能回溯
        start = nextNode;
        end->next = new eulerNode(start);
        end = end->next;
    }
}

template <class TypeOfVer, class TypeOfEdge>
typename adjList<TypeOfVer, TypeOfEdge>::verNode* adjList<TypeOfVer, TypeOfEdge>::clone() const {
    verNode* tmp = new verNode[this->Vers]; //申请空间
    
    edgeNode* p; 
    for (int i = 0; i < this->Vers; ++i)
    {
        tmp[i].ver = verList[i].ver;  //将顶点赋值
        p = verList[i].head;
        while (p != nullptr)          //将该顶点的单链表赋值
        {
            //头插
            tmp[i].head = new edgeNode(p->end, p->weight, tmp[i].head);
            p = p->next;
        }
    }
    return tmp;
}

template <class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::bfs(TypeOfVer start) const{
    bool *visited = new bool[this->Vers];
    for (int i = 0; i < this->Vers; ++i)
    {
        visited[i] = false;
    }
    
    edgeNode *p;
    int u = myFind(start), currentNode;
    queue<int> que;
    que.push(u);

    //先从start指定起点做一次bfs遍历
    while (!que.empty())
    {
        currentNode = que.front();
        que.pop();
        if (visited[currentNode] == true) continue;
        cout << verList[currentNode].ver <<  " ";
        visited[currentNode] = true;

        p = verList[currentNode].head;
        while (p != nullptr)
        {
            if (visited[p->end] == false) que.push(p->end);
            p = p->next;
        }
    }
    cout << endl;

    //检查是否还有其他未遍历的节点
    for (int i = 0; i < this->Vers; ++i)
    {
        if (visited[i] == true) continue;
        que.push(i);
        while (!que.empty())
        {
            currentNode = que.front();
            que.pop();
            if (visited[currentNode] == true) continue;
            cout << verList[currentNode].ver <<  " ";
            visited[currentNode] = true;

            p = verList[currentNode].head;
            while (p != nullptr)
            {
                if (visited[p->end] == false) que.push(p->end);
                p = p->next;
            }
        }
        cout << endl;
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::dfs() const{
    bool *visited = new bool[this->Vers];
    for (int i = 0; i < this->Vers; ++i)
    {
        visited[i]=false;
    }

    cout << "dfs is ";
    for (int i = 0; i < this->Vers; ++i)
    {
        if (visited[i] == true) continue;
        dfs(i, visited);
        cout << endl;
    }    
}

template <class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const {
    edgeNode *p = verList[start].head;
    cout << verList[start].ver << " ";
    visited[start] = true;

    while (p != nullptr )
    {
        if (visited[p->end] == false)
        {
            dfs(p->end, visited);
        }
        p = p->next;
    }
}

template <class TypeOfVer, class TypeOfEdge>
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

template <class TypeOfVer, class TypeOfEdge>
adjList<TypeOfVer, TypeOfEdge>::adjList(int size, const TypeOfVer ver[]) {
    this->Vers = size;
    this->Edges = 0;
    verList = new verNode[size];
    for (int i = 0; i < size; ++i)
    {
        verList[i].ver = ver[i];
    }
}

template <class TypeOfVer, class TypeOfEdge>
adjList<TypeOfVer, TypeOfEdge>::~adjList() {
    edgeNode *p;
    for (int i = 0; i < this->Vers; ++i)
    {
        while ((p = verList[i].head) != nullptr)
        {
            verList[i].head = p->next;
            delete p;
        }
    }
    delete []verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int u = myFind(x), v = myFind(y);
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++this->Edges;
}

//删除分两种情况，1.删除第一个节点 2.删除非第一个节点
template <class TypeOfVer, class TypeOfEdge>
void adjList<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    int u = myFind(x), v = myFind(y);
    edgeNode *p = verList[u].head, *q;
    if (p == nullptr) return;
    
    //如果第一个节点符合条件，则删除第一个节点，返回函数
    if (p->end == v)
    {
        verList[u].head = p->next;
        delete p;
        --this->Edges;
        return;
    }

    //如果第一个节点不符合条件，则向后寻找
    //删除某个节点是要知道该节点的前一个节点，所以判断是站在p的位置向后看一个节点
    //如果p->next为nullptr，则表示走到了链表最后一个节点都没有找到y，说明x和y之间不存在边，下面的if不会执行
    //如果p->next->data为y，表示x和y存在边，退出while循环，执行删除操作
    while (p->next != nullptr && p->next->end != v)
        p=p->next;
    //这个if判断是针对找到了y，而且没有走到最后一个节点
    if (p->next != nullptr)
    {
        q = p->next;
        p->next = q->next;
        delete q;
        --this->Edges;
    }
}

template <class TypeOfVer, class TypeOfEdge>
bool adjList<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u = myFind(x), v = myFind(y);
    edgeNode *p = verList[u].head;
    while (p != nullptr && p->end != v)
        p=p->next;

    if (p != nullptr)
        return true;
     else 
        return false;
    
}