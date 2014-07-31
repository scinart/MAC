#include <cstddef>
//new segment tree.
//debug switchs
//#define DEBUG_QUERY_AID 0x01;
//#define DEBUG_UPDATE_AID 0x02;

template<typename T,typename V>
class IMarktype
{
protected:
    T v;
public:
    virtual operator bool()=0;//if mark exists
    virtual void clear()=0;// clear mark
    virtual IMarktype& merge(const IMarktype& parent)=0;//merge two marks; merge parent to child when pushDown.
    // ;; a.k.a. child.mark.merge(father.mark);
    virtual V withValue(const V& oldValue)=0;//return value of merging mark and value; aka. the value with mark applied.
    virtual ~IMarktype(){};
    const T get()const{return v;}
};

class IntMark : public IMarktype<int,int>
{
/*
mark 为区间加减，value为最大值。
*/
public:
    IntMark(){v=0;}
    IntMark(int i){v=i;}
    operator bool(){return v;}
    void clear(){v=0;}
    IMarktype<int,int>& merge(const IMarktype<int,int>& parent){v+=parent.get(); return *this;}
    int withValue(const int& oldValue){return v+oldValue;}
    static bool MERGABLE;
    static bool OK_WITH_BOSS_WHEN_SET_MARK;
};
bool IntMark::MERGABLE = true;
bool IntMark::OK_WITH_BOSS_WHEN_SET_MARK = true;

class PairMark : public IMarktype<int,pair<int,int> >
{
/*
mark 为区间加减，value为<最大值，最小值>。
*/
public:
    PairMark(){v=0;}
    PairMark(int i){v=i;}
    operator bool(){return v;}
    void clear(){v=0;}
    void merge(const IMarktype<int,pair<int,int> >& rhs){v+=rhs.get();}
    PII withValue(const pair<int,int>& oldValue){return pair<int,int>(v+oldValue.first,v+oldValue.second);}
    static bool MERGABLE;
};
bool PairMark::MERGABLE = true;


class SetMark : public IMarktype<sc, ssc>
{
public:
    SetMark(){v=0;}
    SetMark(sc i){v=i;}
    operator bool(){return v;}
    void clear(){v=0;}
    IMarktype<sc, ssc>& merge(const IMarktype<sc,ssc>& parent){v=parent.get(); return *this;}
    ssc withValue(const ssc& oldValue){ssc a;a.insert(v);return a;}
    static bool MERGABLE;
    static bool OK_WITH_BOSS_WHEN_SET_MARK;
};
bool SetMark::MERGABLE = true;
bool SetMark::OK_WITH_BOSS_WHEN_SET_MARK = false;


template<typename T, typename Marktype>
class SegmentTree
{//zero indexed left close right open tree.
    typedef T (*fnmerge)(const T& a,const T& b);
    typedef T (*fninit)(int l);
public:
    struct Node
    {
        int l;
        int r;
        Marktype mark;
        T value;
        void setNode(int l_, int r_,const T& value_){l=l_;r=r_;value=value_;}
    };

    //¡important! Node[l,r) stores in the in-order index(zero indexed) of nedo.
    Node* nedo; //Nedo is Node
    fnmerge merge; //how two nodes merge
    fninit init; //init(0) is first segment's value, etc.

    SegmentTree(size_t N,
                fninit init_,
                fnmerge merge_):query_head(indexof(0,N))
    { //length of Segment.
        nedo = new Node[2*N-1];
        merge = merge_;
        init = init_;
        build_aid(0,N);
    }
    ~SegmentTree(){ delete[] nedo; }
    inline int indexof(int l,int r)
    {//Scinart way, my way.
        return (l-1+r)-((r-l==1)?0:((l+r)&1));
    }
    T query(int l,int r)
    {
        return query_aid(query_head,l,r);
    }
    void update(int l,int r,Marktype mark)
    {
        update_aid(query_head, l, r, mark);
    }
private:
    const int query_head;
    void build_aid(int l,int r)
    {//uses init
        if(l+1<r)
        {//if not elementary
            build_aid(l,(l+r)/2);
            build_aid((l+r)/2,r);
            nedo[indexof(l,r)].setNode(l,
                                       r,
                                       merge(nedo[indexof(l,(l+r)/2)].value,
                                             nedo[indexof((l+r)/2,r)].value));
        }
        else
        {
            nedo[indexof(l,r)].setNode(l,r,init(l));
        }
    }
    void pushDown(int which_node)
    {
        /*if this node is marked then pushDown and clear the mark.*/
        Marktype& mark = nedo[which_node].mark;
        if(mark)
        {
            int l=nedo[which_node].l;
            int r=nedo[which_node].r;
            if(r-l>1)
            {//not leaf, push down Mark;
                if(Marktype::MERGABLE)
                {
                    (nedo[indexof(l,(l+r)/2)]).mark.merge(mark);
                    (nedo[indexof((l+r)/2,r)]).mark.merge(mark);
                }
                else
                {
                    pushDown(indexof(l,(l+r)/2));
                    pushDown(indexof((l+r)/2,r));
                    (nedo[indexof(l,(l+r)/2)]).mark = mark;
                    (nedo[indexof((l+r)/2,r)]).mark = mark;
                }

            }
            nedo[which_node].value = mark.withValue(nedo[which_node].value);
            nedo[which_node].mark.clear();
        }
    }
    T query_aid(int which_node, int l,int r)
    {
        pushDown(which_node);
        int lbound = nedo[which_node].l;
        int rbound = nedo[which_node].r;
#ifdef DEBUG_QUERY_AID
        printf("query_aid [%d..%d) in [%d..%d).\n",l,r, lbound, rbound);
#endif
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            return nedo[which_node].value;
        }
        else
        {
            T ans;
            int mid = (lbound+rbound)/2;
            if(l<mid)
            {
                ans = query_aid(indexof(lbound,mid),l,r);
                if(r>mid)
                {
                    ans = merge(ans,query_aid(indexof(mid,rbound),l,r));
                }
            }
            else
            {
                ans = query_aid(indexof(mid,rbound),l,r);
            }
            return ans;
        }
    }
    void update_aid(int which_node, int l,int r,const Marktype& mark)
    {
        int lbound = nedo[which_node].l;
        int rbound = nedo[which_node].r;
#ifdef DEBUG_UPDATE_AID
        printf("updating [%d..%d) in [%d..%d) with mark %d\n",l,r, lbound, rbound, mark.get());
#endif
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            nedo[which_node].mark.merge(mark);
        }
        else
        {
            if(Marktype::OK_WITH_BOSS_WHEN_SET_MARK)
            {
                //nothing
            }
            else
            {
                pushDown(which_node);
            }
            int mid = (lbound+rbound)/2;
            if(l<mid)
            {
                update_aid(indexof(lbound,mid),l,r,mark);
                if(r>mid)
                {
                    update_aid(indexof(mid,rbound),l,r,mark);
                }
            }
            else
            {
                update_aid(indexof(mid,rbound),l,r,mark);
            }
            // this roll back is required.
            pushDown(indexof(lbound, mid));
            pushDown(indexof(mid, rbound));
            nedo[which_node].value = merge(nedo[indexof(lbound,mid)].value, nedo[indexof(mid, rbound)].value);
        }
#ifdef DEBUG_UPDATE_AID
#endif
    }

};

int init_(int){return 0;}
int merge_(const int& a,const int& b){return max(a,b);}
