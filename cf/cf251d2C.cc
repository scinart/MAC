// Time-stamp: <2014-07-22 19:25:20 scinart>
// created at 2014-07-22 19:06:50
// cf2512C.cc

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

#define NNOO {cout<<"NO\n";return 0;}
#define OUTALL {cout<<odds.size()+evens.size()<<' ';EACH(it,odds)cout<<*it<<' ';EACH(it,evens)cout<<*it<<' ';cout<<'\n';}
int main()
{
    std::ios::sync_with_stdio(false);

    int n,k,p,q;
    cin>>n>>k>>q;
    p=k-q;//p is odd, q is even.

    VI odds;odds.reserve(n);
    VI evens;evens.reserve(n);

    REP(i,n)
    {
        int a;cin>>a;
        if(a&1)
            odds.push_back(a);
        else
            evens.push_back(a);
    }

    int x = odds.size();
    int y = evens.size();

    if(p>x)
    {
        NNOO;
    }
    if((x-p)&1)
    {
        NNOO;
    }
    if(q>((x-p)>>1)+y)
    {
        NNOO;
    }

    {
        //good.

        cout<<"YES\n";
        if(q!=0)
        {
            REP(i,p)
            {
                cout<<"1 "<<odds.back()<<'\n';
                odds.pop_back();
            }
            if(q-1<evens.size())
            {
                REP(i,q-1)
                {
                    cout<<"1 "<<evens.back()<<'\n';
                    evens.pop_back();
                }
                OUTALL;
            }
            else
            {
                EACH(it,evens)cout<<"1 "<<*it<<'\n';
                q-=evens.size();
                evens.clear();
                REP(i,q-1)
                {
                    cout<<"2 ";
                    cout<<odds.back()<<' ';
                    odds.pop_back();
                    cout<<odds.back()<<'\n';
                    odds.pop_back();
                }
                OUTALL;
            }
        }
        else
        {
            REP(i,p-1)
            {
                cout<<"1 "<<odds.back()<<'\n';
                odds.pop_back();
            }
            OUTALL;
        }
    }



    return 0;
}
