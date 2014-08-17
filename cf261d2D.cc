// Time-stamp: <2014-08-16 00:54:03 scinart>
// created at 2014-08-16 00:39:10
// cf261d2D.cc

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

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

typedef vector<int> vi;
typedef pair<vi::iterator, vi::iterator> pii;

const int maxn = 1000010;

int data[maxn];
int up[maxn];
vi rec[maxn << 2];
int ht[maxn];


void build(int l, int r, int rt){
    rec[rt].clear();
    for (int i = l; i <= r; i++){
        rec[rt].push_back(ht[i]);
    }
    int m = (l + r) >> 1;

    sort(rec[rt].begin(), rec[rt].end());
    //    for (vi::iterator ii = rec[rt].begin(); ii != rec[rt].end(); ii++){
    //        printf("%d ", *ii);
    //    }
    //    puts("end\n");
    if (l == r) return ;

    build(lson);
    build(rson);
}

int query(int L, int R, int key, int l, int r, int rt){
    if (L <= l && r <= R){
        pii tmp;
        tmp = equal_range(rec[rt].begin(), rec[rt].end(), key);
        return tmp.second - rec[rt].begin();
    }
    int m = (l + r) >> 1;
    int ret = 0;

    if (L <= m) ret = query(L, R, key, lson);
    if (m < R) ret += query(L, R, key, rson);

    return ret;
}



int main(){

    int n;
    scanf("%d", &n);

    REP(i,n)
    {
        scanf("%d", &data[i]);
    }

    map<int,int> upcnt;
    map<int,int> downcnt;

    REP(i,n)
    {
        up[i]=++upcnt[data[i]];
    }
    for(int i=n-1;i>=0; i--)
    {
        ht[i]=++downcnt[data[i]];
    }

    // REP(i,n)cout<<up[i]<<' ';cout<<'\n';
    // REP(i,n)cout<<ht[i]<<' ';cout<<'\n';

    ll ans=0;
    build(0, n - 1, 1);
    for(int i=0; i<n-1; i++)
    {
        int l=i+1;
        int r=n-1;
        int k=up[i]-1;
        ans+=query(l,r,k,0,n-1,1);
    }
    printf("%lld\n", ans);
    return 0;
}

