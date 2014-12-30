// Time-stamp: <2014-07-22 20:33:06 scinart>
// created at 2014-07-22 19:36:17
// cf2512D.cc

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cassert>
#include <list>
#include <iomanip>
#include <cmath>
#include <deque>
#include <utility>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <climits>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <sstream>

using namespace std;

#define REP(i, n) for (int  i=0; i<(int)(n); ++i)
#define REP_1(i, n) for (int i=1; i<=(int)(n); ++i)
#define FOR(i, b, e) for (int i=(b); i<(int)(e); ++i)
#define DWN(i, b, e) for (int i=(b); i>(int)(e); --i)
#define ALL(c) c.begin(), c.end()

#ifdef __GNUC__
#if __cplusplus >= 201103L
#define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
#define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
#else
#ifdef __STRICT_ANSI__
#define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
#define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
#else
#define EACH(it,A) for (typeof(A.begin()) it=A.begin(); it!=A.end(); ++it)
#define REACH(it,A) for (typeof(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
#endif
#endif
#else
#define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
#define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
#endif
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

typedef unsigned int uint;
typedef unsigned long long ULL;
typedef long long LL;
typedef pair<int, int> PII;
typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;

bool PIIfs(const PII& a, const PII& b){return a.first<b.first || (a.first == b.first && a.second<b.second);}
bool PIIsf(const PII& a, const PII& b){return a.second<b.second || (a.second == b.second && a.first<b.first);}
bool PIIFS(const PII& a, const PII& b){return a.first>b.first || (a.first == b.first && a.second>b.second);}
bool PIISF(const PII& a, const PII& b){return a.second>b.second || (a.second == b.second && a.first>b.first);}
bool PIIfS(const PII& a, const PII& b){return a.first<b.first || (a.first == b.first && a.second>b.second);}
bool PIIsF(const PII& a, const PII& b){return a.second<b.second || (a.second == b.second && a.first>b.first);}
bool PIIFs(const PII& a, const PII& b){return a.first>b.first || (a.first == b.first && a.second<b.second);}
bool PIISf(const PII& a, const PII& b){return a.second>b.second || (a.second == b.second && a.first<b.first);}

template <typename T> inline T max(T a, T b, T c) { return max(max(a, b), c); }
template <typename T> inline T max(T a, T b, T c, T d) { return max(max(a, b, c), d); }
template <typename T> inline T max(T a, T b, T c, T d, T e) { return max(max(a, b, c, d), e); }
template <typename T> inline T min(T a, T b, T c) { return min(min(a, b), c); }
template <typename T> inline T min(T a, T b, T c, T d) { return min(min(a, b, c), d); }
template <typename T> inline T min(T a, T b, T c, T d, T e) { return min(min(a, b, c, d), e); }

template <typename T> inline istream& RD(T& x){return cin>>x;}
template <typename T, typename U> inline istream& RD(T& a, U& b){return cin>>a>>b;}
template <typename T, typename U, typename V> inline istream& RD(T& a, U& b, V& c){return cin>>a>>b>>c;}
template <typename T, typename U, typename V, typename W>
inline istream& RD(T& a, U& b, V& c,W& d){return cin>>a>>b>>c>>d;}
template <typename T, typename U, typename V, typename W, typename X>
inline istream& RD(T& a, U& b, V& c,W& d,X& e){return cin>>a>>b>>c>>d>>e;}

template <typename T>
void checkmin(T& a,const T& b){if(b<a)a=b;}
template <typename T>
void checkmax(T& a, const T& b){if(b>a)a=b;}


VI devu;
VI bro;

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
      mark 为区间加减，value为区间和。
    */
public:
    IntMark(){v=0;}
    IntMark(int i){v=i;}
    operator bool(){return v;}
    void clear(){v=0;}
    IMarktype<int,int>& merge(const IMarktype<int,int>& parent){assert(false); return *this;}
    int withValue(const int& oldValue){assert(false);return v+oldValue;}
    static bool MERGABLE;
    static bool OK_WITH_BOSS_WHEN_SET_MARK;
};
bool IntMark::MERGABLE = true;
bool IntMark::OK_WITH_BOSS_WHEN_SET_MARK = true;


template<typename T, typename Marktype>
class SegmentTree
{//zero indexed left close right open tree.
    typedef T (*fnmerge)(const T& a,const T& b);
    typedef T (*fninit)(LL l);
public:
    struct Node
    {
        LL l;
        LL r;
        Marktype mark;
        T value;
        void setNode(LL l_, LL r_,const T& value_){l=l_;r=r_;value=value_;}
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
    inline LL indexof(LL l,LL r)
    {//Scinart way, my way.
        return (l-1+r)-((r-l==1)?0:((l+r)&1));
    }
    T query(LL l,LL r)
    {
        return query_aid(query_head,l,r);
    }
    void update(LL l,LL r,Marktype mark)
    {
        update_aid(query_head, l, r, mark);
    }
private:
    const LL query_head;
    void build_aid(LL l,LL r)
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
    void pushDown(LL which_node)
    {
        /*if this node is marked then pushDown and clear the mark.*/
        Marktype& mark = nedo[which_node].mark;
        if(mark)
        {
            LL l=nedo[which_node].l;
            LL r=nedo[which_node].r;
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
    T query_aid(LL which_node, LL l,LL r)
    {
        pushDown(which_node);
        LL lbound = nedo[which_node].l;
        LL rbound = nedo[which_node].r;
#ifdef DEBUG_QUERY_AID
        prLLf("query_aid [%d..%d) in [%d..%d).\n",l,r, lbound, rbound);
#endif
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            return nedo[which_node].value;
        }
        else
        {
            T ans;
            LL mid = (lbound+rbound)/2;
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
    void update_aid(LL which_node, LL l,LL r,const Marktype& mark)
    {
        LL lbound = nedo[which_node].l;
        LL rbound = nedo[which_node].r;
#ifdef DEBUG_UPDATE_AID
        prLLf("updating [%d..%d) in [%d..%d) with mark %d\n",l,r, lbound, rbound, mark.get());
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
            LL mid = (lbound+rbound)/2;
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

LL init_devu(LL x){return devu[x];}
LL init_bro(LL x){return bro[x];}
LL merge_(const LL& a,const LL& b){return a+b;}



int devu_min;
int bro_max;

LL devu_cost(LL level, SegmentTree<LL,IntMark> & st)
{
    //increase to level;
    if(level<=devu_min) return 0;
    VI::iterator it = upper_bound(ALL(devu), level-1);
    VI::iterator be = devu.begin();
    int numit = it-be;
    return level*numit - st.query(0,numit);
}
LL bro_cost(LL level, SegmentTree<LL,IntMark>& st)
{
    //decrease to level;
    if(bro_max <= level) return 0;
    VI::iterator be = bro.begin();
    VI::iterator it = upper_bound(ALL(bro), level);
    VI::iterator en = bro.end();
    int numit = it-be;
    int numen = en-be;
    return st.query(numit, numen) - level*(numen-numit);
}

int main()
{
    std::ios::sync_with_stdio(false);

    int n,m;
    cin>>n>>m;

    devu.resize(n);
    bro.resize(m);

    devu_min = INT_MAX;
    bro_max = 0;
    REP(i,n){cin>>devu[i];checkmin(devu_min, devu[i]);}
    REP(i,m){cin>>bro[i];checkmax(bro_max, bro[i]);}

    sort(ALL(devu));
    sort(ALL(bro));



    int l=devu_min, r=bro_max; r++;


    SegmentTree<LL,IntMark> st_devu(n,init_devu,merge_);
    SegmentTree<LL,IntMark> st_bro(m,init_bro,merge_);


    while(l+1<r)
    {
        int mid=((l+r)>>1);
        // int L_cost = devu_cost((l+mid)>>1, st_devu) + bro_cost((l+mid)>>1, st_bro);
        // int R_cost = devu_cost((r+mid)>>1, st_devu) + bro_cost((r+mid)>>1, st_bro);
        int mid_cost = devu_cost(mid, st_devu) + bro_cost(mid, st_bro);
        int mid_next = devu_cost(mid+1, st_devu) + bro_cost(mid+1, st_bro);
#ifndef ONLINE_JUDGE
//        cout<<"l:"<<l<<" r:"<<r<<" LC:"<<L_cost<<" RC:"<<R_cost<<'\n';
#endif
        if(mid_cost < mid_next)
        {
            r = mid;
        }
        else if (mid_cost > mid_next)
        {
            l=mid;
        }
        else
        {
            l=mid;break;
        }
    }

    //cout<<l<<'\n';
    LL min_cost = devu_cost(l, st_devu) + bro_cost(l, st_bro);
    l--;
    checkmin(min_cost, devu_cost(l, st_devu) + bro_cost(l, st_bro));
    l++;l++;
    checkmin(min_cost, devu_cost(l, st_devu) + bro_cost(l, st_bro));
    cout<<min_cost<<'\n';
    return 0;
}
