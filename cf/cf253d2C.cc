//
// Time-stamp: <2014-06-20 00:43:28 scinart>

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

template <typename T> inline void RD(T& x){cin>>x;}
template <typename T, typename U> inline void RD(T& a, U& b){return RD(a),RD(b);}
template <typename T, typename U, typename V> inline void RD(T& a, U& b, V& c){return RD(a),RD(b),RD(c);}
template <typename T, typename U, typename V, typename W>
inline void RD(T& a, U& b, V& c,W& d){return RD(a),RD(b),RD(c),RD(d);}
template <typename T, typename U, typename V, typename W, typename X>
inline void RD(T& a, U& b, V& c,W& d,X& e){return RD(a),RD(b),RD(c),RD(d),RD(e);}

bool mat[5][5];
map<string,int> memo;

bool distinguishable(string had)
{
    int matrix[5][5];
    int count=0;
    REP(i,5)REP(j,5){matrix[i][j]=mat[i][j];if(mat[i][j])count++;}
    if(count<=1){return true;}
    REP(i,5)
    {
        if(had[i]=='1')
        {
            int count_row=0;
            REP(j,5){
                if(matrix[i][j])
                {
                    matrix[i][j]+=10;count_row++;
                }
            }
            if(count_row==1)
            {
                count--;
                REP(k,5)if(matrix[i][k])matrix[i][k]=0;
            }
        }
    }
    REP(i,5)
    {
        if(had[i+5]=='1')
        {
            int count_column = 0;
            REP(j,5){
                if(matrix[j][i])
                {
                    matrix[j][i]+=11;
                    count_column++;
                }
            }
            if(count_column==1)
            {
                count--;
                REP(k,5)if(matrix[k][i])matrix[k][i]=0;
            }
        }
    }
    if(count<=1)
    {
        return true;
    }
    else
    {
        REP(i,5)REP(j,5){
            if(matrix[i][j]>=20)
            {
                matrix[i][j]=0;
                count--;
            }
        }
        REP(i,5)
        {
            if(had[i]=='1')
            {
                int count_row=0;
                REP(j,5){
                    if(matrix[i][j])
                    {
                        matrix[i][j]+=10;count_row++;
                    }
                }
                if(count_row==1)
                {
                    count--;
                    REP(k,5)if(matrix[i][k])matrix[i][k]=0;
                }
            }
        }
        REP(i,5)
        {
            if(had[i+5]=='1')
            {
                int count_column = 0;
                REP(j,5){
                    if(matrix[j][i])
                    {
                        matrix[j][i]+=11;
                        count_column++;
                    }
                }
                if(count_column==1)
                {
                    count--;
                    REP(k,5)if(matrix[k][i])matrix[k][i]=0;
                }
            }
        }
        if(count<=1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
int mindp(string had, int next_empty)
{
    if(memo.find(had)!=memo.end())
    {
        return memo[had];
    }
    else
    {
        if(distinguishable(had))
        {
            memo[had]=0;
            return 0;
        }
        else if(next_empty<10)
        {
            string had_with_me = had;
            had_with_me[next_empty]='1';
            int with_me = mindp(had_with_me,next_empty+1);
            int with_out_me = mindp(had, next_empty+1);
            memo[had]=min(with_out_me, with_me+1);
            return memo[had];
        }
        else
        {
            memo[had]=100000;//INT_MAX
            return memo[had];
        }
    }
}
int main()
{
    std::ios::sync_with_stdio(false);
    int N;
    RD(N);
    REP(i,5)REP(j,5)mat[i][j]=false;
    REP(i,N)
    {
        string s;
        RD(s);
        char f=s[0];
        int sec = s[1]-'1';
        switch(f)
        {
          case 'R':
          {
              mat[0][sec]=true;break;
          }
          case 'G':
          {
              mat[1][sec]=true;break;
          }
          case 'B':
          {
              mat[2][sec]=true;break;
          }
          case 'Y':
          {
              mat[3][sec]=true;break;
          }
          case 'W':
          {
              mat[4][sec]=true;break;
          }
        }
    }

#ifndef ONLINE_JUDGE
    // REP(i,5)
    // {
    //     REP(j,5)
    //     {
    //         cout<<mat[i][j]<<' ';
    //     }
    //     cout<<'\n';
    // }
#endif
    string init("0000000000");
    cout<<mindp(init,0)<<'\n';
    return 0;
}
