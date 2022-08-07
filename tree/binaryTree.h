#include <queue>
#include <stack>
#include <unordered_map>
#include "bTree.h"
using namespace std;

template<class T>
class binaryTree : public bTree<T> {
    // friend void printTree(const binaryTree &t, T flag);
    private:
        typedef struct Node {                //�������Ľ����
            Node  *left , *right ;               
            T data;                         
            Node() : left(nullptr), right(nullptr) { }
            Node(T item, Node *L = nullptr, Node * R =nullptr) : data(item), left(L), right(R) { }
            ~Node() {} 
        }Node;
        Node *root;
        //����x�ڵ�
        Node *find(T x, Node *t ) const;
        // ͬ�����к����ݹ�������º���ʵ��
        void clear(Node *&t);
        int size(Node *t) const; 
        void preOrder(Node *t) const;
        void midOrder(Node *t) const;
        void postOrder(Node *t) const;
    public:
        // ����ն�����
        binaryTree() : root(nullptr) {}
        // ����ֻ�и����Ķ�����
        binaryTree(T x) { root = new Node(x); }
        ~binaryTree()  { clear() ; }
        //ɾ��������
        void clear() ;
        // �Ƿ�Ϊ����
        bool isEmpty() const{return root == nullptr;}
        // ���ؽڵ����
        int size() const;
        //����������ĸ��ڵ����ݣ���������ڷ���flag
        T Root(T flag) const;
        //����x�ڵ�ĸ��ڵ㣬��������ڷ���flag
        T parent(T x, T flag) const;
        // ����x�ڵ�����ӽڵ㣬������Ӳ����ڷ���flag
        T lchild(T x, T flag) const;
        // ����x�ڵ���Һ��ӽڵ㣬����Һ��Ӳ����ڷ���flag
        T rchild(T x, T flag) const; 
        // ɾ��x�ڵ��������
        void delLeft(T x) ;
        // ɾ��x�ڵ��������
        void delRight(T x);
        // ǰ�����
        void preOrder() const;
        // �������
        void midOrder() const;
        // �������
        void postOrder() const;
        //��α���
        void levelOrder() const;
        //������
        void createTree(T flag);
        // ǰ�����_����
        void preOrder_diedai() const;
        // �������_����
        void midOrder_diedai() const;
        // �������_����
        void postOrder_diedai() const;
        // �������
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

//������
template <class T>
void binaryTree<T>::createTree(T flag) {
    Node *tmp;
    T val, l_val, r_val;
    queue<Node*> que;
    cout << "��������ڵ�����ݣ�\n ";
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
            cout << "������" << tmp->data << "�����Һ���(" << flag  << "��ʾΪ��)";
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

//����x�ڵ�
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

// ����x�ڵ�����ӽڵ㣬������Ӳ����ڷ���flag
template <class T>
T binaryTree<T>::lchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == nullptr || tmp->left == nullptr)
    {
        return flag;
    }
    return tmp->left->data;
}

// ����x�ڵ���Һ��ӽڵ㣬����Һ��Ӳ����ڷ���flag
template <class T>
T binaryTree<T>::rchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == nullptr || tmp->right == nullptr)
    {
        return flag;
    }
    return tmp->right->data;
}

// ɾ��x�ڵ��������
template <class T>
void binaryTree<T>::delLeft(T x) {
    Node *tmp = find(x, root);
    if (tmp == nullptr)
    {
        return;
    }
    
    clear(tmp->left);
}
// ɾ��x�ڵ��������
template <class T>
void binaryTree<T>::delRight(T x) {
    Node *tmp = find(x, root);
    if (tmp == nullptr)
    {
        return;
    }    
    clear(tmp->right);    
}

//ɾ����tΪ����������ע�����ﴫ�����ָ����������*&t����Ҫ�޸�ָ���ֵ
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

//ɾ��������
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


//����������ĸ��ڵ����ݣ���������ڷ���flag
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

//ǰ�����
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
    cout << "\nǰ�����: ";
    preOrder(root);
    cout << endl; 
}

//�������
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
    cout << "\n�������: ";
    midOrder(root);
    cout << endl; 
}

//�������
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
    cout << "\n�������: ";
    postOrder(root);
    cout << endl; 
}

//��α���
template <class T>
void binaryTree<T>::levelOrder() const {
    cout << "\n��α����� " ;
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

//����ʵ�֣��Լ�ʵ��ջ
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
        //���ǳ�ջ��˳��ҪΪ������ң���ջ��˳��������Һ���
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

//˫ջʵ�ֺ������
template <class T>
void binaryTree<T>::postOrder_diedai() const {
    if (root == nullptr)
    {
        return;
    }

    Node* tmp;
    //��������ջ��st1���ڵ���˳��st2�����ռ���st1��ջ��Ԫ�أ�st2��ջ��˳����Ƕ������������
    stack<Node*> st1, st2;
    st1.push(root);         //���ڵ���ջ
    while (!st1.empty())    //��st1��Ϊ��
    {
        tmp = st1.top();     //��ȡջ��Ԫ��
        st1.pop();          //����ջ��Ԫ��
        st2.push(tmp);      //����Ԫ���뵽st2��
        //st1����ջtmp�����ӣ�����ջtmp���Һ���
        //����st1��ջ˳����ͷ��㡢�Һ��ӡ����ӣ�
        //��������˳����뵽st2��st2��ջ˳���������ͷ����Ϊ�������˳��
        if (tmp->left)
        {
            st1.push(tmp->left);
        }
        
        if (tmp->right)
        {
            st1.push(tmp->right);
        }
    }
    //st2ȫ��Ԫ�س�ջ
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

    //������������߽�һֱ��ջ���ڵ����Ĺ����У����ҽڵ����߽�һֱ��ջ
    //�տ�ʼջΪ�գ�!st.empty()Ϊ�٣�tmp != nullptrΪ�棬����ѭ��
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
    int curLevelNodes = 0;  //��ǰ��Ľڵ����

    //ʹ��unordered_map�洢�ڵ�������ڵĲ�
    unordered_map<Node*, int> levleMap;
    queue<Node*> que;
    levleMap.insert(pair<Node*, int>(root, 1)); //root�ڵ����ڲ���1
    que.push(root);
    while (!que.empty())
    {
        tmp = que.front();
        que.pop();
        int myLevel = levleMap.at(tmp);
        //�����ǰ�ڵ����ڵĲ��뵱ǰ��һ�£�˵����ǰ�㻹�нڵ�δ������curLevelNodes����1
        if (myLevel == curLevel)
        {
            curLevelNodes++;
        } else {
            //�����ǰ�ڵ����ڲ��뵱ǰ�㲻һ�£�˵����һ��ڵ��Ѿ������꣬����widthMax����¼�ϴ�ֵ
            //curLevel����1����ǰ��ĸ�����Ϊ1����Ϊ������һ���ڵ�
            widthMax = (curLevelNodes > widthMax ? curLevelNodes : widthMax);
            curLevel++;
            curLevelNodes=1;
        }
        if (tmp->left)
        {
            que.push(tmp->left);
            //�ڽ����������ڵ���뵽levleMapʱ����¼�ڵ����ڵĲ㣬��curLevel+1
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