template <class elemType>
class list
{    
public:
    //清除
    virtual void clear() = 0;
    //长度
    virtual int length() const = 0;
    //插入
    virtual void insert(int i, const elemType &x) = 0;
    //删除
    virtual void remove(int i) = 0;
    //搜索
    virtual int search(const elemType &x) const = 0;
    //访问
    virtual elemType visit(int i) const = 0;
    //遍历
    virtual void traverse() const = 0;
    //析构
    virtual ~list() {}
};
