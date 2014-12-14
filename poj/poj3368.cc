//
// Time-stamp: <2014-07-20 22:28:37 scinart>

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


vector<int> vi;

/*
*一维RMQ ST算法
*构造RMQ数组 makermq(int n,int b[]) O(nlog(n))的算法复杂度
*dp[i][j] 表示从i到i+2^j -1中最小的一个值(从i开始持续2^j个数)
*dp[i][j]=min{dp[i][j-1],dp[i+2^(j-1)][j-1]}
*查询RMQ rmq(int s,int v)
*将s-v 分成两个2^k的区间
*即 k=(int)log2(s-v+1)
*查询结果应该为 min(dp[s][k],dp[v-2^k+1][k])
*/

const int MAXN = 100010;
int dp[MAXN][20];
template <typename T>
void makermq(int n,const T& b)
{
        int i,j;
        for(i=0;i<n;i++)
                dp[i][0]=b[i];
        for(j=1;(1<<j)<=n;j++)
                for(i=0;i+(1<<j)-1<n;i++)
                        dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}
int rmq(int s,int v)
{
        int k=(int)(log((v-s+1)*1.0)/log(2.0));
/* 或者int d = v - s+1 ,  k;
                         for(k = 0; (1<<k) <= d; k++) ;
                                k- -;*/
        return max(dp[s][k],dp[v-(1<<k)+1][k]);
}


int main()
{
    std::ios::sync_with_stdio(false);

    int n,queries;
    while(cin>>n && n)
    {
        map<int,int> mii;
        cin>>queries;
        int val,old=INT_MIN;
        int cnt = 0;
        REP(i,n)
        {
            cin>>val;
            if(val!=old)
            {
                mii[i]=cnt;
                old = val;
                cnt++;
            }
            else
            {
                //nothing.
            }
        }
        {
            mii[n] = cnt;
        }
        vi.clear();
        vi.reserve(mii.size());

        {
            map<int,int>::iterator it=mii.begin(), jt=it;jt++;
            while(jt!=mii.end())
            {
                vi.push_back(jt->first-it->first);
                it++;
                jt++;
            }
        }
        makermq(vi.size(), vi);
#ifndef ONLINE_JUDGE
        // vi中存的是将原数据分组，每组的长度
        // 比如 -1 -1 1 1 1 1 3 10 10 10 就是 [2 4 1 3]
        EACH(it,vi)cout<<*it<<' ';cout<<'\n';
        // mii是每组的起始下标->这是第几组
        // 0:0
        // 2:1
        // 6:2
        // 7:3
        // 10:4

        EACH(it,mii){
            cout<<it->first<<':'<<it->second<<'\n';
        }
#endif
        REP(j,queries)
        {
            int b,e;
            cin>>b>>e;
            b--;e--;
            map<int,int>::iterator bup = mii.upper_bound(b);
            map<int,int>::iterator elow = mii.upper_bound(e); elow--;
#ifndef ONLINE_JUDGE
            cout<<'\n';
            // b 的下一个是哪组，输出组首元素编号和第几组。
            cout<<b<<' '<<bup->first<<":"<<bup->second<<'\n';
            // e 在哪组，输出组首元素编号和第几组
            cout<<e<<' '<<elow->first<<":"<<elow->second<<'\n';
            // 在b和e中间有哪些组，输出第几组。
            cout<<"mid: ["<<bup->second<<","<<elow->second-1<<"]\n";
#endif
            int b_seg = bup->first-b; //b所在组的长度
            int e_seg = e-elow->first+1;//e所在组的长度
            int mid=0;//中间那些组的rmq
            if(bup->second<elow->second)
                mid = rmq(bup->second, elow->second-1);
            // cout<<b_seg<<":"<<e_seg<<":"<<mid<<"\n";
            cout<<max(b_seg, e_seg, mid)<<'\n';
        }
    }

    return 0;
}
