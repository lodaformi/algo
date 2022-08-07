#include <queue>
#include <stack>
#include <unordered_map>
#include "bTree.h"
using namespace std;

template<class T>
class binaryTree : public bTree<T> {
    // friend void printTree(const binaryTree &t, T flag);
    private:
        typedef struct Node {                //二叉树的结点类
            Node  *left , *right ;               
            T data;                         
            Node() : left(nullptr), right(nullptr) { }
            Node(T item, Node *L = nullptr, Node * R =nullptr) : data(item), left(L), right(R) { }
            ~Node() {} 
        }Node;
        Node *root;
        //查找x节点
        Node *find(T x, Node *t ) const;
        // 同名公有函数递归调用以下函数实现
        void clear(Node *&t);
        int size(Node *t) const; 
        void preOrder(Node *t) const;
        void midOrder(Node *t) const;
        void postOrder(Node *t) const;
    public:
        // 创造空二叉树
        binaryTree() : root(nullptr) {}
        // 创造只有根结点的二叉树
        binaryTree(T x) { root = new Node(x); }
        ~binaryTree()  { clear() ; }
        //删除整个树
        void clear() ;
        // 是否为空树
        bool isEmpty() const{return root == nullptr;}
        // 返回节点个数
        int size() const;
        //返回这棵树的根节点数据，如果不存在返回flag
        T Root(T flag) const;
        //返回x节点的父节点，如果不存在返回flag
        T parent(T x, T flag) const;
        // 返回x节点的左孩子节点，如果左孩子不存在返回flag
        T lchild(T x, T flag) const;
        // 返回x节点的右孩子节点，如果右孩子不存在返回flag
        T rchild(T x, T flag) const; 
        // 删除x节点的左子树
        void delLeft(T x) ;
        // 删除x节点的右子树
        void delRight(T x);
        // 前序遍历
        void preOrder() const;
        // 中序遍历
        void midOrder() const;
        // 后序遍历
        void postOrder() const;
        //层次遍历
        void levelOrder() const;
        //创建树
        void createTree(T flag);
        // 前序遍历_迭代
        void preOrder_diedai() const;
        // 中序遍历_迭代
        void midOrder_diedai() const;
        // 后序遍历_迭代
        void postOrder_diedai() const;
        // 求最大宽度
        int width() const;
}; 

// template <class T>
// void printTree(const binaryTree<T> &t, T flag) {
    // linkQueue<T> q;

    // q.enQueue(t.root->data);
    // cout << endl;
    // while (!q.isEmpty()) {
    //         char p, l, r;
    //         p = q.deQueue();
    //         l = t.lchild(p,  flag);
    //         r = t.rchild(p,  flag);
    //         cout << p << "  " << l  << "  " << r << endl;
    //         if (l != flag) q.enQueue(l);
    //         if (r != flag) q.enQueue(r);
    // }

//     Node *tmp;
//     queue<Node*> que;
//     que.push(t);
//     while (!que.empty())
//     {   
//         tmp = que.front();
//         que.pop();
//         if (tmp->data == flag)
//         {
//             cout << flag << " ";
//         }else {
//             cout << tmp->data << " ";
//         }
//         if(tmp->left) que.push(tmp->left);
//         if(tmp->right) que.push(tmp->right);
//     }
// }

//创建树
template <class T>
void binaryTree<T>::createTree(T flag) {
    Node *tmp;
    T val, l_val, r_val;
    queue<Node*> que;
    cout << "请输入根节点的数据：\n ";
    cin >> val;
    root = new Node(val);
    que.push(root);
    int n = 5;
    while (!que.empty())
    {
        tmp = que.front();
        que.pop();
        if (n)
        {
            cout << "请输入" << tmp->data << "的左右孩子(" << flag  << "表示为空)";
            cin >> l_val >> r_val;
            if (l_val != flag)
            {
                que.push(tmp->left = new Node(l_val));
            }
            if (r_val != flag)
            {
                que.push(tmp->right = new Node(r_val));
            }
            --n;
        } 
    }
    cout << "create completed!\n";
}

//查找x节点
template <class T>
typename binaryTree<T>::Node* binaryTree<T>::find(T x, binaryTree<T>::Node *t) const {
    Node *tmp;
    if (t == nullptr)
    {
        return nullptr;
    }
    if (t->data == x)
    {
        return t;
    }
    if (tmp == find(x, t->left)) {
        return tmp;
    }else {
        return find(x, t->right);
    }
}

// 返回x节点的左孩子节点，如果左孩子不存在返回flag
template <class T>
T binaryTree<T>::lchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == nullptr || tmp->left == nullptr)
    {
        return flag;
    }
    return tmp->left->data;
}

// 返回x节点的右孩子节点，如果右孩子不存在返回flag
template <class T>
T binaryTree<T>::rchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == nullptr || tmp->right == nullptr)
    {
        return flag;
    }
    return tmp->right->data;
}

// 删除x节点的左子树
template <class T>
void binaryTree<T>::delLeft(T x) {
    Node *tmp = find(x, root);
    if (tmp == nullptr)
    {
        return;
    }
    
    clear(tmp->left);
}
// 删除x节点的右子树
template <class T>
void binaryTree<T>::delRight(T x) {
    Node *tmp = find(x, root);
    if (tmp == nullptr)
    {
        return;
    }    
    clear(tmp->right);    
}

//删除以t为根的子树，注意这里传入的是指针引用类型*&t，是要修改指针的值
template <class T>
void binaryTree<T>::clear(binaryTree<T>::Node *&t) {
    if (t == nullptr)
    {
        return;
    }
    clear(t->left);
    clear(t->right);
    delete t;
    t = nullptr;
}

//删除整个树
template <class T>
void binaryTree<T>::clear() {
    clear(root);
}

template <class T>
int binaryTree<T>::size(binaryTree<T>::Node *t) const {
    if (t == nullptr)
    {
        return 0;
    }else {
        return size(t->left) + size(t->right) + 1;
    }
}

template <class T>
int binaryTree<T>::size() const {
    return size(root);
}


//返回这棵树的根节点数据，如果不存在返回flag
template <class T>
T binaryTree<T>::Root(T flag) const {
    if (root == nullptr) return flag;
    else return root->data;
}

template <class T>
T binaryTree<T>::parent(T x, T flag) const {
    return 1;
    // if (root == nullptr)  return flag;
    // Node *tmp;
    // if (root->data == x)
    // {
    //     return 1;
    // }

    // if (tmp == parent(x, t->left)) {
    //     return tmp;
    // }else {
    //     return find(x, t->right);
    // }
}

//前序遍历
template <class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node *t) const {
    if (t == nullptr)
    {
        return;
    }
    cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
}

template <class T>
void binaryTree<T>::preOrder() const {
    cout << "\n前序遍历: ";
    preOrder(root);
    cout << endl; 
}

//中序遍历
template <class T>
void binaryTree<T>::midOrder(binaryTree<T>::Node *t) const {
    if (t == nullptr)
    {
        return;
    }
    midOrder(t->left);
    cout << t->data << " ";
    midOrder(t->right);   
}

template <class T>
void binaryTree<T>::midOrder() const {
    cout << "\n中序遍历: ";
    midOrder(root);
    cout << endl; 
}

//后序遍历
template <class T>
void binaryTree<T>::postOrder(binaryTree<T>::Node *t) const {
    if (t == nullptr)
    {
        return;
    }
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << " ";
}

template <class T>
void binaryTree<T>::postOrder() const {
    cout << "\n后序遍历: ";
    postOrder(root);
    cout << endl; 
}

//层次遍历
template <class T>
void binaryTree<T>::levelOrder() const {
    cout << "\n层次遍历： " ;
    if (root == nullptr)
    {
        return;
    }
    
    Node* tmp;
    queue<Node*> que;
    que.push(root);
    while (!que.empty())
    {
        tmp = que.front();
        que.pop();
        cout << tmp->data << " ";
        if (tmp->left)
        {
            que.push(tmp->left);
        }
        if(tmp->right) {
            que.push(tmp->right);
        }
        
    }
    cout << endl;
}

//迭代实现，自己实现栈
template <class T>
void binaryTree<T>::preOrder_diedai() const {
    if (root == nullptr)
    {
        return;
    }
    Node *tmp;

    stack<Node*> st;
    st.push(root);
    while (!st.empty())
    {
        tmp = st.top();
        cout << tmp->data << " ";
        st.pop();
        //考虑出栈的顺序要为先左后右，进栈的顺序就是先右后左
        if (tmp->right)
        {
            st.push(tmp->right);
        }
        if (tmp->left)
        {
            st.push(tmp->left);
        }
    }
    cout << endl;
}

//双栈实现后序遍历
template <class T>
void binaryTree<T>::postOrder_diedai() const {
    if (root == nullptr)
    {
        return;
    }

    Node* tmp;
    //申请两个栈，st1用于调整顺序，st2用于收集从st1出栈的元素，st2出栈的顺序就是二叉树后序遍历
    stack<Node*> st1, st2;
    st1.push(root);         //根节点入栈
    while (!st1.empty())    //当st1不为空
    {
        tmp = st1.top();     //获取栈顶元素
        st1.pop();          //弹出栈顶元素
        st2.push(tmp);      //弹出元素入到st2中
        //st1先入栈tmp的左孩子，再入栈tmp的右孩子
        //这样st1出栈顺序是头结点、右孩子、左孩子，
        //以这样的顺序进入到st2，st2出栈顺序就是左右头，即为后序遍历顺序
        if (tmp->left)
        {
            st1.push(tmp->left);
        }
        
        if (tmp->right)
        {
            st1.push(tmp->right);
        }
    }
    //st2全部元素出栈
    while (!st2.empty())
    {
        tmp = st2.top();
        cout << tmp->data << " ";
        st2.pop();
    }
    cout << endl;
}

template <class T>
void binaryTree<T>::midOrder_diedai() const {
    if (root == nullptr)
    {
        return;
    }

    stack<Node*> st;
    Node* tmp = root;

    //将整棵树的左边界一直入栈，在弹出的过程中，将右节点的左边界一直入栈
    //刚开始栈为空，!st.empty()为假，tmp != nullptr为真，进入循环
    while (!st.empty() || tmp != nullptr) 
    {
        if (tmp != nullptr)
        {
            st.push(tmp);
            tmp = tmp->left;
        }else {
            tmp = st.top();
            st.pop();
            cout << tmp->data << " ";
            tmp=tmp->right;
        }
    }
    cout << endl;
}

template <class T>
int binaryTree<T>::width() const{
    if (root == nullptr)
    {
        return 0;
    }
    Node *tmp;
    int widthMax = -1;
    int curLevel = 1;
    int curLevelNodes = 0;  //当前层的节点个数

    //使用unordered_map存储节点和其所在的层
    unordered_map<Node*, int> levleMap;
    queue<Node*> que;
    levleMap.insert(pair<Node*, int>(root, 1)); //root节点所在层是1
    que.push(root);
    while (!que.empty())
    {
        tmp = que.front();
        que.pop();
        int myLevel = levleMap.at(tmp);
        //如果当前节点所在的层与当前层一致，说明当前层还有节点未遍历，curLevelNodes自增1
        if (myLevel == curLevel)
        {
            curLevelNodes++;
        } else {
            //如果当前节点所在层与当前层不一致，说明上一层节点已经遍历完，结算widthMax，记录较大值
            //curLevel自增1，当前层的个数变为1，因为自身算一个节点
            widthMax = (curLevelNodes > widthMax ? curLevelNodes : widthMax);
            curLevel++;
            curLevelNodes=1;
        }
        if (tmp->left)
        {
            que.push(tmp->left);
            //在将左右子树节点加入到levleMap时，记录节点所在的层，是curLevel+1
            levleMap.insert(pair<Node*, int>(tmp->left, curLevel+1));
        }
        if (tmp->right)
        {
            que.push(tmp->right);
            levleMap.insert(pair<Node*, int>(tmp->right, curLevel+1));
        }
    }
    return widthMax;
}