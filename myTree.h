template <class T>
class myTree
{
public:
    virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
    virtual int size() = 0;
    virtual T root(T flag) const = 0;
    virtual T parent(T x, T flag) const = 0;
    virtual T child(T x, int i, T flag) const = 0;
    virtual void remove(T x, int i) = 0;
    virtual void traverse() const = 0;
    virtual ~myTree() {}
};

