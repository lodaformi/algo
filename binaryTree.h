#include <queue>
using namespace std;

template<class T>
class binaryTree : public bTree<T> {
    friend void printTree(const binaryTree &t, T flag);
    private:
        struct Node {                //二叉树的结点类
            Node  *left , *right ;               
            T data;                         
            Node() : left(nullptr), right(nullptr) { }
            Node(T item, Node *L = nullptr, Node * R =nullptr) : data(item), left(L), right(R) { }
            ~Node() {} 
        };
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
}; 

template <class T>
void printTree(const binaryTree<t> &t, T flag) {
    Node *tmp;
    queue<Node*> que;
    que.push(t);
    while (!que.empty())
    {
        tmp = que.pop();
        if (tmp->data == flag)
        {
            cout << flag << " ";
        }else {
            cout << tmp->data << " ";
        }
        if(tmp->left) que.push(tmp->left);
        if(tmp->right) que.push(tmp->right);
    }
}

//创建树
template <class T>
void binaryTree<T>::createTree(T flag) {
    Node *tmp;
    T val, l_val, r_val;
    queue<Node*> que;
    cout << "请输入跟节点的数据： ";
    cin >> val;
    root = new Node(val);
    que.push(root);
    while (!que.empty())
    {
        tmp = que.pop();
        cout << "请输入" << tmp->data << "的左右孩子(" << flag  << "表示为空";
        cin >> l_val >> r_val;
        if (l_val != flag)
        {
            que.push(tmp->left = new Node(l_val));
        }
        if (r_val != flag)
        {
            que.push(tmp->right = new Node(r_val));
        }
    }
    cout << "create completed!\n";
}

//查找x节点
template <class T>
binaryTree<T>::Node* binaryTree<T>::find(T x, binaryTree<T>::Node *t) const {
    Node *tmp;
    if (t == nullptr)
    {
        return nullptr;
    }
    if (t->data == x)
    {
        return t;
    }
    if (tmp = find(x, t->left)) {
        return tmp;
    }else {
        return find(x, t->right);
    }
}

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
}

//层次遍历
template <class T>
void binaryTree<T>::levelOrder() const {
    queue<Node*> que;
    Node *tmp;

    cout << "\n层次遍历： " ;
    que.push(root);
    while (!que.empty())
    {
        tmp = que.pop();
        cout << tmp->data << " ";
        if (tmp->left)
        {
            que.push(tmp->left);
        }
        if (tmp->right) {
            que.push(tmp->right);
        }
    }
}
