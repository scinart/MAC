// Time-stamp: <2014-08-07 18:45:01 scinart>
// created at 2014-08-06 21:31:46
// hdu3397.cc

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
typedef char Marktype;

const int maxn = 100010;

Valtype VALSUM[2*maxn];
Valtype VALONEM[2*maxn];
Valtype VALONEL[2*maxn];
Valtype VALONER[2*maxn];
Valtype VALZEROM[2*maxn];
Valtype VALZEROL[2*maxn];
Valtype VALZEROR[2*maxn];
Valtype INPUT[maxn];
int L[2*maxn];
int R[2*maxn];
Marktype MARK[2*maxn];

inline void mergeMark(Marktype& son, const Marktype& father)
{
    if(father=='2')
    {
        if(son=='2')son=0;
        else if(son=='1')son='0';
        else if(son=='0')son='1';
        else son=father;
    }
    else
    {
        son=father;
    }
}
inline void setMark(Marktype& where, const Marktype& what){where=what;}
inline Valtype mergeValSUM(const Valtype& a,const Valtype& b){return a+b;}
inline const Valtype withValueSum(const Marktype& mark, const Valtype& val, int l, int r)
{
    if(mark=='2')
        return r-l-val;
    else
        return (r-l)*mark;
}
inline void clearMark(Marktype& m){m=0;}


class SegmentTree
{//zero indexed left close right open tree.
public:
    SegmentTree(size_t N):query_head(indexof(0,N))
    { //length of Segment.
        // suppose node already has its value.
        build(0,N);
    }
    Valtype query_sum(int l,int r)
    {
        return query_aid_sum(query_head, l,r);
    }
    Valtype query_lc(int l,int r)
    {
        return query_aid_lc(query_head, l, r);
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
            int lmid = indexof(l,(l+r)/2);
            int rmid = indexof((l+r)/2,r);
            VALSUM[ind]=mergeValSUM(VALSUM[lmid],VALSUM[rmid]);

            VALONEM[ind]=0;
            if(VALONER[rmid]==r-(l+r)/2)
            {
                VALONER[ind]=VALONER[rmid]+VALONER[lmid];
                checkmax(VALONEM[ind],VALONER[ind]);
            }
            else
            {
                VALONER[ind]=VALONER[rmid];
            }
            if(VALONEL[lmid]==(r+l)/2-l)
            {
                VALONEL[ind]=VALONEL[lmid]+VALONEL[rmid];
                checkmax(VALONEM[ind],VALONEL[ind]);
            }
            else
            {
                VALONEL[ind]=VALONEL[lmid];
            }
            checkmax(VALONEM[ind], VALONER[lmid]+VALONEL[rmid]);
            checkmax(VALONEM[ind], VALONEM[lmid]);
            checkmax(VALONEM[ind], VALONEM[rmid]);

            VALZEROM[ind]=0;
            if(VALZEROR[rmid]==r-(l+r)/2)
            {
                VALZEROR[ind]=VALZEROR[rmid]+VALZEROR[lmid];
                checkmax(VALZEROM[ind],VALZEROR[ind]);
            }
            else
            {
                VALZEROR[ind]=VALZEROR[rmid];
            }
            if(VALZEROL[lmid]==(r+l)/2-l)
            {
                VALZEROL[ind]=VALZEROL[lmid]+VALZEROL[rmid];
                checkmax(VALZEROM[ind],VALZEROL[ind]);
            }
            else
            {
                VALZEROL[ind]=VALZEROL[lmid];
            }
            checkmax(VALZEROM[ind], VALZEROR[lmid]+VALZEROL[rmid]);
            checkmax(VALZEROM[ind], VALZEROM[lmid]);
            checkmax(VALZEROM[ind], VALZEROM[rmid]);

        }
        else
        {
            L[ind]=l;
            R[ind]=r;
            if(INPUT[l])
            {
                VALSUM[ind]=1;

                VALONEL[ind]=1;
                VALONER[ind]=1;
                VALONEM[ind]=1;
                VALZEROL[ind]=0;
                VALZEROR[ind]=0;
                VALZEROM[ind]=0;
            }
            else
            {
                VALSUM[ind]=0;

                VALONEL[ind]=0;
                VALONER[ind]=0;
                VALONEM[ind]=0;
                VALZEROL[ind]=1;
                VALZEROR[ind]=1;
                VALZEROM[ind]=1;
            }
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
                mergeMark(MARK[indexof(l,(l+r)/2)], (mark));
                mergeMark(MARK[indexof((l+r)/2,r)], (mark));
            }
            if(mark=='0')
            {
                VALSUM[which_node]=0;
                VALONEL[which_node]=0;
                VALONER[which_node]=0;
                VALONEM[which_node]=0;
                VALZEROL[which_node]=r-l;
                VALZEROR[which_node]=r-l;
                VALZEROM[which_node]=r-l;
            }
            else if(mark=='1')
            {
                VALSUM[which_node]=r-l;
                VALONEL[which_node]=r-l;
                VALONER[which_node]=r-l;
                VALONEM[which_node]=r-l;
                VALZEROL[which_node]=0;
                VALZEROR[which_node]=0;
                VALZEROM[which_node]=0;
            }
            else
            {
                VALSUM[which_node]=r-l-VALSUM[which_node];
                swap(VALONEL[which_node], VALZEROL[which_node]);
                swap(VALONER[which_node], VALZEROR[which_node]);
                swap(VALONEM[which_node], VALZEROM[which_node]);
            }
            clearMark(MARK[which_node]);
        }
    }
    Valtype query_aid_sum(int which_node, int l,int r)
    {
        pushDown(which_node);//necessary.
        int lbound = L[which_node];
        int rbound = R[which_node];
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            return VALSUM[which_node];
        }
        else
        {
            Valtype ans;
            int mid = (lbound+rbound)>>1;
            if(l<mid)
            {
                ans = query_aid_sum(indexof(lbound,mid),l,r);
                if(r>mid)
                {
                    ans += query_aid_sum(indexof(mid,rbound),l,r);
                }
            }
            else
            {
                ans = query_aid_sum(indexof(mid,rbound),l,r);
            }
            return ans;
        }
    }
    Valtype query_aid_lc(int which_node, int l,int r)
    {
        pushDown(which_node);//necessary.
        int lbound = L[which_node];
        int rbound = R[which_node];
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            return VALONEM[which_node];
        }
        else
        {
            int mid = (lbound+rbound)>>1;
            if(l<mid)
            {
                if(r<=mid) return query_aid_lc(indexof(lbound,mid),l,r);
                else
                {
                    Valtype ans=0;
                    checkmax(ans,query_aid_lc(indexof(lbound,mid),l,r));
                    checkmax(ans,query_aid_lc(indexof(mid,rbound),l,r));
                    checkmax(ans,query_aid_r(indexof(lbound,mid),l,r) + query_aid_l(indexof(mid,rbound),l,r));
                    return ans;
                }
            }
            else
            {
                return query_aid_lc(indexof(mid,rbound),l,r);
            }
        }
    }
    Valtype query_aid_l(int which_node, int l, int r)
    {
        pushDown(which_node);//necessary.
        return min(VALONEL[which_node], r-L[which_node]);
    }
    Valtype query_aid_r(int which_node, int l,int r)
    {
        pushDown(which_node);//necessary.
        return min(VALONER[which_node],R[which_node]-l);
    }
    void update_aid(int which_node, int l,int r,const Marktype& mark)
    {
        int lbound = L[which_node];
        int rbound = R[which_node];
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            mergeMark(MARK[which_node],(mark));
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

            int ind=which_node;
            int lmid=indexof(lbound,mid);
            int rmid=indexof(mid,rbound);
            VALSUM[ind]=mergeValSUM(VALSUM[lmid],VALSUM[rmid]);

            VALONEM[ind]=0;
            if(VALONER[rmid]==rbound-mid)
            {
                VALONER[ind]=VALONER[rmid]+VALONER[lmid];
                checkmax(VALONEM[ind],VALONER[ind]);
            }
            else
            {
                VALONER[ind]=VALONER[rmid];
            }
            if(VALONEL[lmid]==mid-lbound)
            {
                VALONEL[ind]=VALONEL[lmid]+VALONEL[rmid];
                checkmax(VALONEM[ind],VALONEL[ind]);
            }
            else
            {
                VALONEL[ind]=VALONEL[lmid];
            }
            checkmax(VALONEM[ind], VALONER[lmid]+VALONEL[rmid]);
            checkmax(VALONEM[ind], VALONEM[lmid]);
            checkmax(VALONEM[ind], VALONEM[rmid]);

            VALZEROM[ind]=0;
            if(VALZEROR[rmid]==rbound-mid)
            {
                VALZEROR[ind]=VALZEROR[rmid]+VALZEROR[lmid];
                checkmax(VALZEROM[ind],VALZEROR[ind]);
            }
            else
            {
                VALZEROR[ind]=VALZEROR[rmid];
            }
            if(VALZEROL[lmid]==mid-lbound)
            {
                VALZEROL[ind]=VALZEROL[lmid]+VALZEROL[rmid];
                checkmax(VALZEROM[ind],VALZEROL[ind]);
            }
            else
            {
                VALZEROL[ind]=VALZEROL[lmid];
            }
            checkmax(VALZEROM[ind], VALZEROR[lmid]+VALZEROL[rmid]);
            checkmax(VALZEROM[ind], VALZEROM[lmid]);
            checkmax(VALZEROM[ind], VALZEROM[rmid]);

        }
    }
};


int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif

    int cases;scanf("%d", &cases);
    REP(cc,cases)
    {
        int n,m;

        memset(VALSUM,0,sizeof(int)*2*maxn);
        memset(VALONEM,0,sizeof(int)*2*maxn);
        memset(VALONEL,0,sizeof(int)*2*maxn);
        memset(VALONER,0,sizeof(int)*2*maxn);
        memset(VALZEROM,0,sizeof(int)*2*maxn);
        memset(VALZEROL,0,sizeof(int)*2*maxn);
        memset(VALZEROR,0,sizeof(int)*2*maxn);
        memset(INPUT,0,sizeof(int)*maxn);
        memset(L,0,sizeof(int)*2*maxn);
        memset(R,0,sizeof(int)*2*maxn);
        memset(MARK,0,sizeof(char)*2*maxn);


        scanf("%d %d", &n, &m);
        REP(i,n)scanf("%d",&INPUT[i]);
        SegmentTree st(n);
        REP(i,m)
        {
            int op,a,b;
            scanf("%d %d %d", &op, &a, &b);
            switch(op)
            {
              case 0 ... 2:
              {
                  st.update(a, b+1, op+'0');
                  break;
              }
              case 3:
              {
                  printf("%d\n",st.query_sum(a, b+1));;
                  break;
              }
              case 4:
              {
                  printf("%d\n", st.query_lc(a,b+1));
                  break;
              }
            }
        }
    }
    return 0;
}
