template<class T>
class binaryTree : public bTree<T> {
    friend void printTree(const binaryTree &t, T flag);
    private:
        struct Node {                          //二叉树的结点类
            Node  *left , *right ;               
            T data;                         
            Node() : left(nullptr), right(nullptr) { }
            Node(T item, Node *L = nullptr, Node * R =nullptr) : data(item), left(L), right(R) { }
            ~Node() {} 
        };
        Node *root;

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
        void clear() ;
        bool isEmpty() const{return root == nullptr;}
        int size() const;
        T Root(T flag) const;
        T lchild(T x, T flag) const;
        T rchild(T x, T flag) const; 
        void delLeft(T x) ;
        void delRight(T x);
        void preOrder() const;
        void midOrder() const;
        void postOrder() const;
        void levelOrder() const;
        void createTree(T flag);
}; 