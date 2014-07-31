// nkoj2112
// Time-stamp: <2014-05-23 17:15:49 scinart>

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

template <typename T> inline T abs1(T a) {return a < 0 ? -a : a;}
template <typename T> inline T max1(T a, T b) { return a > b ? a : b; }
template <typename T> inline T max1(T a, T b, T c) { return max1(max1(a, b), c); }
template <typename T> inline T max1(T a, T b, T c, T d) { return max1(max1(a, b, c), d); }
template <typename T> inline T max1(T a, T b, T c, T d, T e) { return max1(max1(a, b, c, d), e); }
template <typename T> inline T min1(T a, T b) { return a < b ? a : b; }
template <typename T> inline T min1(T a, T b, T c) { return min1(min1(a, b), c); }
template <typename T> inline T min1(T a, T b, T c, T d) { return min1(min1(a, b, c), d); }
template <typename T> inline T min1(T a, T b, T c, T d, T e) { return min1(min1(a, b, c, d), e); }

template <typename T> inline int RD(T& x){return 0;}
template <> inline int RD<char>(char& c){return scanf(" %c",&c);}
template <> inline int RD<int>(int& c){return scanf(" %d",&c);}
template <> inline int RD<uint>(uint& c){return scanf(" %u",&c);}
template <> inline int RD<LL>(LL& c){return scanf(" %lld",&c);}
template <> inline int RD<ULL>(ULL& c){return scanf(" %llu",&c);}
template <> inline int RD<float>(float& c){return scanf(" %f",&c);}
template <> inline int RD<double>(double& c){return scanf(" %lf",&c);}
template <typename T, typename U> inline int RD(T& a, U& b){return RD(a),RD(b);}
template <typename T, typename U, typename V> inline int RD(T& a, U& b, V& c){return RD(a),RD(b),RD(c);}
template <typename T, typename U, typename V, typename W>
inline int RD(T& a, U& b, V& c,W& d){return RD(a),RD(b),RD(c),RD(d);}
template <typename T, typename U, typename V, typename W, typename X>
inline int RD(T& a, U& b, V& c,W& d,X& e){return RD(a),RD(b),RD(c),RD(d),RD(e);}


vector<vector<LL> > adj; //[mark, self height, [next node, weight]*]
int main()
{

    int N,M;
    RD(N,M);
    N++;
    adj.resize(N);
    REP(i,N)
    {
        adj[i].push_back(0);
        adj[i].push_back(-1LL);
    }
    adj[0][1]=0;
    REP(i,M)
    {
        int a,b,w;
        RD(a,b,w);
        adj[b].push_back(a); adj[b].push_back(w);
        adj[a].push_back(b); adj[a].push_back(-w);
    }
    queue<int> Q;
    Q.push(0);
    while(!Q.empty())
    {
        vector<LL>& vl = adj[Q.front()];
        Q.pop();
        int s=vl.size();
        for(int i=2; i!=s;i+=2)
        {
            if(!adj[vl[i]][0])
            {
                adj[vl[i]][1]=vl[1]+vl[i+1];
                Q.push(vl[i]);
            }
        }
        vl[0]=1;
    }
    FOR(i,1,N)
    {
        printf("%lld\n",adj[i][1]);
    }
    return 0;
}
