// nkoj2105
// Time-stamp: <2014-05-23 15:48:54 scinart>

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
    virtual IMarktype& merge(const IMarktype& rhs)=0;//merge two marks;
    virtual V withValue(const V& oldValue)=0;//return value of merging mark and value;
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
    IMarktype<int,int>& merge(const IMarktype<int,int>& rhs){v+=rhs.get(); return *this;}
    int withValue(const int& oldValue){return v+oldValue;}
    static bool MERGABLE;
};
bool IntMark::MERGABLE = true;

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

typedef SegmentTree<int,IntMark> STII;


#define REP(i, n) for (int  i=0; i<(n); ++i)
#define FOR(i, b, e) for (int i=(b); i<(e); ++i)
#if __cplusplus >= 201103L
    #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
#else
  #ifndef __STRICT_ANSI__
    #define EACH(it,A) for (typeof(A.begin()) it=A.begin(); it!=A.end(); ++it)
  #else
    #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
  #endif
#endif

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

template <typename T> inline T abs1(T a) {return a < 0 ? -a : a;}
template <typename T> inline T max1(T a, T b) { return a > b ? a : b; }
template <typename T> inline T max1(T a, T b, T c) { return max1(max1(a, b), c); }
template <typename T> inline T max1(T a, T b, T c, T d) { return max1(max1(a, b, c), d); }
template <typename T> inline T max1(T a, T b, T c, T d, T e) { return max1(max1(a, b, c, d), e); }
template <typename T> inline T min1(T a, T b) { return a < b ? a : b; }
template <typename T> inline T min1(T a, T b, T c) { return min1(min1(a, b), c); }
template <typename T> inline T min1(T a, T b, T c, T d) { return min1(min1(a, b, c), d); }
template <typename T> inline T min1(T a, T b, T c, T d, T e) { return min1(min1(a, b, c, d), e); }

template <typename T> inline int RD(T& x){return 0;}
template <> inline int RD<char>(char& c){return scanf(" %c",&c);}
template <> inline int RD<int>(int& c){return scanf(" %d",&c);}
template <> inline int RD<uint>(uint& c){return scanf(" %u",&c);}
template <> inline int RD<LL>(LL& c){return scanf(" %lld",&c);}
template <> inline int RD<ULL>(ULL& c){return scanf(" %llu",&c);}
template <> inline int RD<float>(float& c){return scanf(" %f",&c);}
template <> inline int RD<double>(double& c){return scanf(" %lf",&c);}
template <typename T, typename U> inline int RD(T& a, U& b){return RD(a),RD(b);}
template <typename T, typename U, typename V> inline int RD(T& a, U& b, V& c){return RD(a),RD(b),RD(c);}
template <typename T, typename U, typename V, typename W>
inline int RD(T& a, U& b, V& c,W& d){return RD(a),RD(b),RD(c),RD(d);}
template <typename T, typename U, typename V, typename W, typename X>
inline int RD(T& a, U& b, V& c,W& d,X& e){return RD(a),RD(b),RD(c),RD(d),RD(e);}

class RECT
{
public:
    int x1,y1,x2,y2;
    RECT(int a,int b,int c,int d):x1(a),y1(b),x2(c),y2(d){}
    void show(){printf("%d %d %d %d\n",x1,y1,x2,y2);};
};
bool rectx1lt(const RECT& a, const RECT& b){return a.x1<b.x1;}
bool rectx2lt(const RECT& a, const RECT& b){return a.x2<b.x2;}
int main()
{
    int N,a,b,c,d;

    RD(N);
    MII mx,my;
    VI input;
    input.reserve(4*N);
    REP(i,N)
    {
        RD(a,b,c,d);
        input.push_back(a);
        input.push_back(b);
        input.push_back(c);
        input.push_back(d);
        mx[a]=0,mx[c]=0;
        my[b]=0,my[d]=0;
    }

    int xmax=0;
    EACH(it,mx)
        it->second=xmax++;
    int ymax=0;
    EACH(it,my)
        it->second=ymax++;

    vector<RECT> vrl;
    vector<RECT> vrr;
    vrl.reserve(N);
    vrr.reserve(N);
    EACH(it,input)
    {
        int aa=mx[*it++];
        int bb=my[*it++];
        int cc=mx[*it++];
        int dd=my[*it];
        // vrl.push_back(RECT(mx[*it++],my[*it++],mx[*it++],my[*it]));
        // 5q2k5aSE6KKrQWxwaGFyZOaJk+S6hu+8jOiiq3N3ZWV0a2FuZ+WWt+S6huOAgg==
        vrl.push_back(RECT(aa,bb,cc,dd));
    }
    vrr = vrl;

    sort(vrl.begin(), vrl.end(), rectx1lt);
    sort(vrr.begin(), vrr.end(), rectx2lt);

    // EACH(it,vrl)
    //     it->show();
    // EACH(it,vrr)
    //     it->show();

    STII treey(ymax,init_,merge_);

    int mmax=INT_MIN;
    int mcount=0;

    vector<RECT>::iterator itl=vrl.begin(),itr=vrr.begin();

    REP(i,xmax)
    {
#define UPMAX do{if(qmax>mmax) mmax=qmax,mcount=1; else if (qmax==mmax) mcount++;}while(0)
        while(itl!=vrl.end() && itl->x1==i)
        {
            treey.update(itl->y1, itl->y2+1,1);
            int qmax=treey.query(itl->y1,itl->y2+1);
            //printf("qmax is %d\n", qmax);
            UPMAX;
            itl++;
        }
        while(itr!=vrr.end() && itr->x2==i)
        {
            treey.update(itr->y1,itr->y2+1,-1);
            itr++;
        }
    }

    printf("%d %d\n",mmax, mcount);
    return 0;
}

