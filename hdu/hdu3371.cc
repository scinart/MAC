// Time-stamp: <2014-08-03 23:51:49 scinart>
// created at 2014-08-03 23:23:37
// hdu3371.cc

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
namespace DSET {

const int MAXN = 1005;
int pre[MAXN],Rank[MAXN];
int degree;
// default is 1-indexed
void INIT(int n) /* 初始化函数 */
{
    degree=n;
    REP_1(i,n) pre[i]=i, Rank[i]=1;
}

int FIND(int x)
{
    int t,r=x;
    while(x!=pre[x]) x=pre[x];
    while(r!=x)
    {
        t=pre[r];
        pre[r]=x;
        r=t;
    }
    return x;
}

inline int TEST(int x,int y)
{
    return FIND(x)==FIND(y);
}
void UNION(int a,int b)
{
    a=FIND(a);
    b=FIND(b);
    if(a==b) return;
    if(Rank[a]>=Rank[b])
        pre[b]=a, Rank[a]+=Rank[b];
    else
        pre[a]=b, Rank[b]+=Rank[a];
    degree--;
}

}

template <typename T>
class PTTT
{
public:
    T first;
    T second;
    T third;
    PTTT (){}
    PTTT (T a, T b,T c){
        first = a;
        second = b;
        third = c;
    }
    PTTT& operator=(const PTTT& rhs)
    {
        first = rhs.first;
        second = rhs.second;
        third=rhs.third;
        return *this;
    }
    bool operator==(const PTTT& rhs)const
    {
        return first==rhs.first && second == rhs.second && third==rhs.third;
    }
    bool operator<(const PTTT& rhs)const
    {
        return this->third<rhs.third;
    }
};

typedef PTTT<int> TRI;
int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif

    int cases;cin>>cases;
    while(cases--){
        int n,m,k;
        cin>>n>>m>>k;
        vector<TRI> pq(m);
        REP(i,m)
        {
            cin>>pq[i].first>>pq[i].second>>pq[i].third;
        }
        DSET::INIT(n);
        REP(i,k)
        {
            int a,b;
            cin>>a>>b;
            REP(x,a-1)
            {
                int c;
                cin>>c;
                DSET::UNION(b,c);
            }
        }
        int ans=0;
        sort(ALL(pq));
        EACH(it,pq)
        {
            if(!DSET::TEST(it->first, it->second))
            {
                DSET::UNION(it->first, it->second);
                ans+=it->third;
            }
        }
        if(DSET::degree==1)
        {
            cout<<ans<<'\n';
        }
        else cout<<"-1\n";
    }

    return 0;
}
