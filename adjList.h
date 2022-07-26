#include "myGraph.h"

template <class TypeOfVer, class TypeOfEdge>
class adjList : public myGraph<TypeOfVer, TypeOfEdge>
{
private:
    struct edgeNode
    {
        TypeOfVer end;
        TypeOfEdge weight;
        struct edgeNode *next;
        edgeNode(TypeOfVer e, TypeOfEdge w, struct edgeNode *n = nullptr): end(e), weight(w), next(n) {}
    };
    struct verNode
    {
        TypeOfVer ver;
        struct edgeNode *head;
        verNode(struct edgeNode *h = nullptr):head(h) {}
    };
    
    struct verNode *verList;
    int find(TypeOfVer x);
    void dfs(int start, const bool visited[]) const;
public:
    void dfs() const;
    adjList(int size, const TypeOfVer ver[]);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    ~adjList();
};

template <class TypeofVer, class TypeOfEdge>
void adjList<TypeofVer, TypeOfEdge>::dfs() const{
    bool *visited = new bool[this->Vers];
    for (int i = 0; i < this->Vers; ++i)
    {
        visited[i]=false;
    }

    cout << "dfs is ";
    for (int i = 0; i < this->Vers; ++i)
    {
        if (visited[i])
        {
            continue;
        }
        dfs(i, visited);
        cout << endl;
    }    
}

template <class TypeofVer, class TypeOfEdge>
void adjList<TypeofVer, TypeOfEdge>::dfs(int start, const bool visited[]) const {
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

template <class TypeofVer, class TypeOfEdge>
int adjList<TypeofVer, TypeOfEdge>::find(TypeOfVer x) {
    for (int i = 0; i < this->Vers; ++i)
    {
        if (verList[i].ver == x)
        {
            return i;
        }
    }
    return -1;
}



template <class TypeofVer, class TypeOfEdge>
adjList<TypeofVer, TypeOfEdge>::adjList(int size, const TypeOfVer ver[]) {
    this->Vers = size;
    this->Edges = 0;
    verList = new struct verNode[size];
    for (int i = 0; i < size; ++i)
    {
        verList[i].ver = ver[i];
    }
}

template <class TypeofVer, class TypeOfEdge>
adjList<TypeofVer, TypeOfEdge>::~adjList() {
    struct edgeNode *p;
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

template <class TypeofVer, class TypeOfEdge>
void adjList<TypeofVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int u = find(x), v = find(y);
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++this->Edges;
}

//删除分两种情况，1.删除第一个节点 2.删除非第一个节点
template <class TypeofVer, class TypeOfEdge>
void adjList<TypeofVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    int u = find(x), v = find(y);
    struct edgeNode *p = verList[u].head, *q;
    if (p == nullptr)
    {
        return;
    }
    
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
    {
        p=p->next;
    }
    //这个if判断是针对找到了y，而且没有走到最后一个节点
    if (p->next != nullptr)
    {
        q = p->next;
        p->next = q->next;
        delete q;
        --this->Edges;
    }
}

template <class TypeofVer, class TypeOfEdge>
bool adjList<TypeofVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u = find(x), v = find(y);
    struct edgeNode *p = verList[u].head;
    while (p != nullptr && p->end != v)
    {
        p=p->next;
    }
    if (p != nullptr)
    {
        return true;
    } else {
        return false;
    }
}