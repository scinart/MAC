// Time-stamp: <2014-08-06 13:38:27 scinart>
// created at 2014-08-06 11:14:25
// poj2828.cc

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
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
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
typedef long long ll;
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

//从零开始 左开右闭
typedef int Valtype;
typedef int Marktype;

#ifdef ECLIPSE
const int maxn = 10;
#else
const int maxn = 200010;
#endif
Valtype VAL[2*maxn];
Valtype INPUT[maxn];
int L[2*maxn];
int R[2*maxn];
Marktype MARK[2*maxn];

/*mark为区间加减，val为区间和*/
inline void mergeMark(Marktype& son, const Marktype& father){son+=father;}
inline void setMark(Marktype& where, const Marktype& what){MARK[where]=MARK[what];}
inline Valtype mergeValVal(const Valtype& a,const Valtype& b){return a+b;}
inline const Valtype withValue(const Marktype& mark, const Valtype& val, int l, int r){return val+(r-l)*mark;}
inline void clearMark(Marktype& m){m=0;}
const bool MERGABLE = true;


/* mark为区间重置，val为最大值
inline void mergeMark(Marktype& son, const Marktype& father){son=father;}
inline void setMark(Marktype& where, const Marktype& what){MARK[where]=MARK[what];}
inline Valtype mergeValVal(const Valtype& a,const Valtype& b){return max(a,b);}
inline const Valtype withValue(const Marktype& mark, const Valtype& val, int l, int r){return mark;}
inline void clearMark(Marktype& m){m=0;}
const bool MERGABLE = true;
*/

class SegmentTree
{//zero indexed left close right open tree.
public:
    SegmentTree(size_t N):query_head(indexof(0,N))
    { //length of Segment.
        // suppose node already has its value.
        build(0,N);
    }
    Valtype query(int l,int r)
    {
        return query_aid(query_head, l,r);
    }
    void update(int l,int r,const Marktype& mark)
    {
        update_aid(query_head, l, r, mark);
    }
private:
    const int query_head;
    inline int indexof(int l,int r)
    {//Scinart way, my way.
        return (l-1+r)-((r-l==1)?0:((l+r)&1));
    }
    void build(int l,int r)
    {
        int ind = indexof(l,r);
        if(l+1<r)
        {//if not elementary
            build(l,(l+r)>>1);
            build((l+r)>>1,r);
            L[ind]=l;
            R[ind]=r;
            VAL[ind]=mergeValVal(VAL[indexof(l,(l+r)/2)],VAL[indexof((l+r)/2,r)]);
        }
        else
        {
            L[ind]=l;
            R[ind]=r;
            VAL[ind]=INPUT[l];
        }
    }
    void pushDown(int which_node)
    {
        /*if this node is marked then pushDown and clear the mark.*/
        const Marktype& mark=MARK[which_node];
        if(mark)
        {
            int l=L[which_node];
            int r=R[which_node];
            if(r-l>1)
            {//not leaf, push down Mark;
                if(MERGABLE)
                {
                    mergeMark(MARK[indexof(l,(l+r)/2)], (mark));
                    mergeMark(MARK[indexof((l+r)/2,r)], (mark));
                }
                else
                {
                    pushDown(indexof(l,(l+r)/2));
                    pushDown(indexof((l+r)/2,r));
                    setMark(MARK[indexof(l,(l+r)/2)], (mark));
                    setMark(MARK[indexof((l+r)/2,r)], (mark));
                }

            }
            VAL[which_node] = withValue(mark,VAL[which_node], l,r);
            clearMark(MARK[which_node]);
        }
    }
    Valtype query_aid(int which_node, int l,int r)
    {
        pushDown(which_node);//necessary.
        int lbound = L[which_node];
        int rbound = R[which_node];
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            return VAL[which_node];
        }
        else
        {
            Valtype ans;
            int mid = (lbound+rbound)>>1;
            if(l<mid)
            {
                ans = query_aid(indexof(lbound,mid),l,r);
                if(r>mid)
                {
                    ans = mergeValVal(ans,query_aid(indexof(mid,rbound),l,r));
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
        int lbound = L[which_node];
        int rbound = R[which_node];
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            if(MERGABLE)
            {
                mergeMark(MARK[which_node],(mark));
            }
            else
            {
                pushDown(which_node);
                mergeMark(MARK[which_node],(mark));
            }
        }
        else
        {
            pushDown(which_node);
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
            VAL[which_node] = mergeValVal(VAL[indexof(lbound,mid)], VAL[indexof(mid, rbound)]);
        }
    }
};

// 题意：一些人，相继插入到pos[i]之后  问最后的情形
//  本题的算法是利用线段树进行倒推。基本思想是拿一个N个1的序列，从最后一次插入开始倒推。
//  设当前插入的是Pos，那么找到从左边数第Pos + 1个1的位置就是最终需要插入的位置，

// 正向推导是平衡树，没想到反过来推导就成了线段树

int POS[maxn];
int iVAL[maxn];
int ANS[maxn];


template<typename T>
int upper_bound (int first, int last, const T& val, T (*fn)(int val))
{
    int it;
    int count = last-first;
    int step;
    while (count>0)
    {
        it = first; step=count/2; it+=step;
        if (!(val<(fn(it))))                 // or: if (!comp(val,*it)), for version (2)
        {
            first=++it;
            count-=step+1;
        }
        else count=step;
    }
    return first;
}
template <typename T>
int lower_bound (int first, int last, const T& val, T (*fn)(int val))
{
    int it;
    int count = last-first, step;
    while (count>0)
    {
        it = first; step=count/2;it+=step;
        if ((fn(it))<val)
        {
            first=++it;
            count-=step+1;
        }
        else count=step;
    }
    return first;
}

// 没有闭包不爽啊。
SegmentTree* pst;
// 没有闭包不爽啊。
int myfn(int val)
{
    return pst->query(0,val);//&& 没有闭包不爽啊。
}

int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif


    int n=10;
    while(scanf("%d", &n)!=EOF)
    {
        REP(i,n)
        {
            scanf("%d%d", &POS[i], &iVAL[i]);
        }
        REP(i,n)INPUT[i]=1;
        SegmentTree st(n);
        pst = &st;
        // 没有闭包不爽啊。
        ROF(i,0,n)
        {
            int lb = lower_bound(1,n+1,POS[i]+1,myfn);
            st.update(lb-1,lb,-1);
            ANS[lb-1] = iVAL[i];
        }
        REP(i,n)printf("%d ", ANS[i]);printf("\n");
    }






    return 0;
}
