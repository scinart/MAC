//
// Time-stamp: <2014-06-03 11:37:24 scinart>

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

string f(string& s,int k,int beginpos)
{
//    cout<<s<<k<<beginpos<<endl;
    int l=s.length();
    if(k==0)
    {
        return s;
    }
    if(beginpos==l)
    {
        return s;
    }
    char x='0';
    int firstmaxpos=beginpos;
    for(int i=beginpos;i < min(beginpos+k+1,(int)l); i++)
    {
        if(x<s[i])
        {
            x=s[i];
            firstmaxpos=i;
        }
    }
    if(s[beginpos]==x)
    {
        return f(s,k,beginpos+1);
    }
    else
    {
        for(int i=firstmaxpos-1; i>=beginpos; i--)
        {
            s[i+1]=s[i];
        }
        s[beginpos]=x;
    }
    return f(s,k-(firstmaxpos-beginpos),beginpos+1);
}

int main()
{
    std::ios::sync_with_stdio(false);

    string s;int k;
    RD(s,k);

    cout<<f(s,k,0)<<"\n";


    return 0;
}
