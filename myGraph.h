template <class TypeOfVer, class TypeOfEdge>
class myGraph
{
protected:
    int Vers, Edges;
public:
    virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0;
    virtual void remove(TypeOfVer x, TypeOfVer y) = 0;
    virtual bool exist(TypeOfVer x, TypeOfVer y) const = 0;
    virtual ~myGraph() {}
    int numOfVer() const {return Vers;}
    int numOfEdge() const {return Edges;}
};

