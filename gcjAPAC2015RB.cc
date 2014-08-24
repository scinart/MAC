// Time-stamp: <2014-08-18 14:41:54 scinart>
// created at 2014-08-18 14:18:09
// gcjAPAC2015RB.cc

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


const int MAXN = 22;
int N;
int old[MAXN][MAXN];
int perm[MAXN][MAXN];
int permans[MAXN][MAXN];
int ans[MAXN][MAXN];

void rotate(int deg) //clockwise
{
    switch(deg)
    {
      case 0:
      {
          REP(i,N)REP(j,N)perm[i][j]=old[i][j];
          break;
      }
      case 1:
      {
          REP(i,N)REP(j,N)perm[j][N-i-1]=old[i][j];
          break;
      }
      case 2:
      {
          REP(i,N)REP(j,N)perm[N-1-i][N-1-j]=old[i][j];
          break;
      }
      case 3:
      {
          REP(i,N)REP(j,N)perm[N-1-j][i]=old[i][j];
      }
    }
}
void rotate2(int deg)
{
    switch(deg)
    {
      case 0:
      {
          REP(i,N)REP(j,N)ans[i][j]=permans[i][j];
          break;
      }
      case 1:
      {
          REP(i,N)REP(j,N)ans[j][N-i-1]=permans[i][j];
          break;
      }
      case 2:
      {
          REP(i,N)REP(j,N)ans[N-1-i][N-1-j]=permans[i][j];
          break;
      }
      case 3:
      {
          REP(i,N)REP(j,N)ans[N-1-j][i]=permans[i][j];
      }
    }
}

void init()
{
    memset(permans,0,sizeof(permans));
}
void insert_line(int line, int val)
{
    for(int i=0;;i++)
    {
        if(permans[line][i]==0)
        {
            permans[line][i]=val;
            break;
        }
    }
}
void doline(int line)
{
    int last=0;
    for(int i=0; i<N; i++)
    {
        int get = perm[line][i];
        if(get!=0)
        {
            if(get==last)
            {
                insert_line(line,get<<1);
                last=0;
            }
            else
            {
                insert_line(line,last);
                last=get;
            }
        }
    }
    if(last!=0)
    {
        insert_line(line,last);
    }
}
int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    int T;cin>>T; REP_1(cc,T)
    {
        init();
        cin>>N;
        string s;cin>>s;
        char direction=s[0];
        int dir=0;
        switch(direction)
        {
          case 'l':
          {
              dir=0;
              break;
          }
          case 'd':
          {
              dir=1;
              break;
          }
          case 'r':
          {
              dir=2;
              break;
          }
          case 'u':
          {
              dir=3;
              break;
          }
        }
        REP(i,N)REP(j,N)cin>>old[i][j];
        rotate(dir);
        dir=(4-dir)%4;
        for(int i=0; i<N; i++)
        {
            doline(i);
        }
        rotate2(dir);
        cout<<"Case #"<<cc<<":\n";
        REP(i,N){REP(j,N)cout<<ans[i][j]<<' ';cout<<'\n';}

    }


    return 0;
}
