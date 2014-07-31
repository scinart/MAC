// 又不行了～
// 没过
// codeforces round 248 div 2 D
// Time-stamp: <2014-05-24 16:49:29 scinart>

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

template <typename T> inline void RD(T& x){cin>>x;}
template <typename T, typename U> inline void RD(T& a, U& b){return RD(a),RD(b);}
template <typename T, typename U, typename V> inline void RD(T& a, U& b, V& c){return RD(a),RD(b),RD(c);}
template <typename T, typename U, typename V, typename W>
inline void RD(T& a, U& b, V& c,W& d){return RD(a),RD(b),RD(c),RD(d);}
template <typename T, typename U, typename V, typename W, typename X>
inline void RD(T& a, U& b, V& c,W& d,X& e){return RD(a),RD(b),RD(c),RD(d),RD(e);}

#define MAXN 1001

char bo[MAXN][MAXN] = {{0}};

class RECT
{
public:
    int x1,y1,x2,y2;
    RECT(int a,int b,int c,int d):x1(a),y1(b),x2(c),y2(d){}
    bool operator<(const RECT& rhs)const
    {
        return x1<rhs.x1 ||
                  (x1==rhs.x1 && y1<rhs.y1) ||
            (x1==rhs.x1 && y1==rhs.y1 && x2<rhs.x2) ||
            (x1==rhs.x1 && y1==rhs.y1 && x2==rhs.x2 && y2<rhs.y2);
    }
};
map<RECT,int> mm;
int query_aid(int x1,int y1,int x2, int y2)
{
    if(mm.find(RECT(x1,y1,x2,y2))!=mm.end())
    {
        return mm[RECT(x1,y1,x2,y2)];
    }
    int l=0,u=0,r=0,d=0;
    bool ll=x1,uu=true,rr=true,dd=y1;
    if(bo[x1][y1]==0) return 0;
    if(ll)
    {
        FOR(i,y1,y2)
        {
            if(bo[x1-1][i]==0)
            {
                ll=0;
                break;
            }
        }
    }
    if(dd)
    {
        FOR(i,x1,x2)
        {
            if(bo[i][y1-1]==0)
            {
                dd=0;
                break;
            }
        }
    }
    FOR(i,y1,y2)
    {
        if(bo[x2][i]==0)
        {
            rr=0;
            break;
        }
    }
    FOR(j,x1,x2)
    {
        if(bo[j][y2]==0)
        {
            uu=0;
            break;
        }
    }
    int ans=(x2-x1)*(y2-y1);
    if(ll) ans=max(ans,query_aid(x1-1,y1,x2,y2));
    if(rr) ans=max(ans,query_aid(x1,y1,x2+1,y2));
    if(dd) ans=max(ans,query_aid(x1,y1-1,x2,y2));
    if(uu) ans=max(ans,query_aid(x1,y1,x2,y2+1));
    mm[RECT(x1,y1,x2,y2)]=ans;
#define DEBUG
#ifdef DEBUG
    cout<<"Q "<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<" is "<<ans<<"\n";
#endif
    return ans;
}
int query(int i,int j)
{
    return query_aid(i,j,i+1,j+1);
}

int main()
{
    std::ios::sync_with_stdio(false);
    int n,m,q;
    cin>>n>>m>>q;
    REP(i,n)
    {
        REP(j,m)
        {
            int x;cin>>x;
            bo[i][j]=x;
        }
    }
#define DBG() do{ REP(i,n) {REP(j,m) {cout<<(int)bo[i][j]<<" "; } cout<<"\n";} }while(0);
    int a,b,c;
    REP(i,q)
    {
        cin>>a>>b>>c;
        if(a==1)
        {
            bo[b-1][c-1] = !bo[b-1][c-1];
            //DBG();
            mm.clear();
        }
        else
        {
            cout<<query(b-1,c-1)<<"\n";
        }
    }
    return 0;
}
