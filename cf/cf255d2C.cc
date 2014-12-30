//
// Time-stamp: <2014-07-13 23:59:34 scinart>

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
#ifdef __GNUC__
  #if __cplusplus >= 201103L
    #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
  #else
    #ifndef __STRICT_ANSI__
      #define EACH(it,A) for (typeof(A.begin()) it=A.begin(); it!=A.end(); ++it)
    #else
      #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
    #endif
  #endif
  #if __cplusplus >= 201103L
      #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
  #else
    #ifndef __STRICT_ANSI__
      #define REACH(it,A) for (typeof(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
    #else
      #define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
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

int main()
{
    std::ios::sync_with_stdio(false);
    // mimic hash.

    int n;
    cin>>n;

    // map<int,int> how_long_from_here;
    map<int,int> how_long_to_here;
    // map<int,int> gap_and_prev_length;

    vector<int> vi(n+1);

    REP(i,n) cin>>vi[i];
    vi[n] = 0;

    int curlen = 1;
    bool incing = false;
    for(int i=1; i<=n; i++)
    {
        if(vi[i]>vi[i-1])
        {
            curlen++;
            incing = true;
        }
        else
        {
            how_long_to_here[i-1] = curlen;
            incing = false;
            curlen = 1;
        }
    }

#ifndef ONLINE_JUDGE
    EACH(it,how_long_to_here)
    {
        cout<<it->first<<':'<<it->second<<'\n';
    }
#endif

    int ans = 0;

    if (how_long_to_here.size() == 1)
    {
        ans = n;
    }
    // else if (how_long_to_here.size() == 2)
    // {
    //     map<int,int>::iterator fit = how_long_to_here.begin();
    //     map<int,int>::iterator sit = how_long_to_here.begin();
    //     sit++;
    //     ans = max(fit->second, sit->second);
    //     ans++;
    // }
    // else
    // {
    else
    {
        EACH(it,how_long_to_here)
        {
            checkmax(ans, it->second+1);
        }
        {
            map<int,int>::iterator fit = how_long_to_here.begin();
            map<int,int>::iterator sit = how_long_to_here.begin();
            sit++;sit++;

            while(sit!=how_long_to_here.end())
            {
                if(fit->first + 1 == sit->first - sit->second &&
                   vi[fit->first] + 1 < vi[sit->first-sit->second+1])
                {
                    checkmax(ans, fit->second+sit->second+1);
                }

                fit++;sit++;
            }
        }
        {
            map<int,int>::iterator fit = how_long_to_here.begin();
            map<int,int>::iterator sit = how_long_to_here.begin();
            sit++;

            while(sit!=how_long_to_here.end())
            {
                if(vi[fit->first] + 1 < vi[sit->first-sit->second+2])
                {
                    checkmax(ans, fit->second+sit->second);
                }
                else if(vi[fit->first - 1] + 1 < vi[sit->first-sit->second+1])
                {
                    checkmax(ans, fit->second+sit->second);
                }

                fit++;sit++;
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
