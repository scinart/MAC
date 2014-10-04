// Time-stamp: <2014-09-20 21:53:33 scinart>
// created at 2014-09-20 21:26:45
// cf268d1B.cc

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
#include <stack>
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
    #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
    #define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
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


// 杭电only
// inline int ri(){int x;scanf("%d", &x);return x;}
// inline double rd(){double x;scanf("%lf", &x);return x;}
// #ifdef ONLINE_JUDGE
// inline long long rll(){long long x;scanf("%I64d", &x);return x;}
// #else
// inline long long rll(){long long x;scanf("%lld", &x);return x;}
// #endif

template <typename T>
void checkmin(T& a,const T& b){if(b<a)a=b;}
template <typename T>
void checkmax(T& a, const T& b){if(b>a)a=b;}

int N;
int AR[2];
map<int,char> mic;

int doend(int key, int s)
{
    char togo = s+'0';
    mic[key]=togo;
    int cnt=1;
    while(mic.find(AR[s]-key)!=mic.end())
    {
        cnt++;
        key=AR[s]-key;
        mic[key]=togo;
        s++;
        s&=1;
    }
    if(cnt&1)
    {
        return -1;//failure.
    }
    else
    {
        return 0;//success
    }
}
int dobi(int key)
{
    int magic=0;
    while(mic.find(AR[magic]-key)!=mic.end())
    {
        key=AR[magic]-key;
        magic++;
        magic&=1;
    }
    magic++;
    magic&=1;
    return doend(key, magic);
}
int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    RD(N,AR[0],AR[1]);
    int A=AR[0];
    int B=AR[1];

    vector<int> vi(N);
    REP(i,N)cin>>vi[i];

    EACH(it,vi)mic.insert(pair<int,char>(*it,'x'));

    bool ok=true;

    if(A==B)
    EACH(it,mic)
    {
        int A_ = A-it->first;
        bool a = (mic.find(A_)!=mic.end());
        if(!a)
        {
            ok=false;
            break;
        }
        else
        {
            it->second='0';
        }
    }

    else
    EACH(it,mic)
    {
        if(it->second=='x')
        {
            int A_ = A-it->first;
            int B_ = B-it->first;
            bool a = (mic.find(A_)!=mic.end());
            bool b = (mic.find(B_)!=mic.end());

            if(a&&!b)
            {
                if(doend(it->first,0) != 0)
                {
                    ok=false;
                    break;
                }
            }
            else if(b&&!a)
            {
                if(doend(it->first,1) != 0)
                {
                    ok=false;
                    break;
                }
            }
            else if(!a && !b)
            {
                ok=false;
                break;
            }
            else
            {
                if(dobi(it->first) != 0)
                {
                    ok=false;
                    break;
                }
            }
        }
    }

    if(ok)
    {
        cout<<"YES\n";
        EACH(it,vi)cout<<mic[*it]<<' ';
    }
    else
    {
        cout<<"NO\n";
    }



    return 0;
}
