// Time-stamp: <2014-08-05 23:58:59 scinart>
// created at 2014-08-05 23:18:46
// hdu1754.cc

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

const int maxn = 2000010;
Valtype VAL[maxn];
Valtype INPUT[maxn];
int L[maxn];
int R[maxn];
Marktype MARK[maxn];

/*mark为区间加减，val为区间和
void mergeMark(Marktype& son, const Marktype& father){son+=father;}
void setMark(Marktype& where, const Marktype& what){MARK[where]=MARK[what];}
Valtype mergeValVal(const Valtype& a,const Valtype& b){return a+b;}
const Valtype withValue(const Marktype& mark, const Valtype& val, int l, int r){return val+(r-l)*mark;}
void clearMark(Marktype& m){m=0;}
const bool MERGABLE = true;
*/

// mark为区间重置，val为最大值
void mergeMark(Marktype& son, const Marktype& father){son=father;}
void setMark(Marktype& where, const Marktype& what){MARK[where]=MARK[what];}
Valtype mergeValVal(const Valtype& a,const Valtype& b){return max(a,b);}
const Valtype withValue(const Marktype& mark, const Valtype& val, int l, int r){return mark;}
void clearMark(Marktype& m){m=0;}
const bool MERGABLE = true;
//

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


int main()
{
    int n,m;
    while(scanf("%d %d", &n, &m)!=EOF)
    {
        REP(i,n)scanf("%d",&INPUT[i]);
        SegmentTree st(n);
        char q;
        int u,v;
        REP(i,m)
        {
            scanf(" %c %d %d", &q, &u, &v);
            if(q=='Q')
            {
                printf("%d\n", st.query(u-1,v));
            }
            else
            {
                st.update(u-1,u,v);
            }
        }
    }



    return 0;
}
