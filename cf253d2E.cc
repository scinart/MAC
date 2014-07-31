// 时间不够了，有bug
// Time-stamp: <2014-06-26 23:10:55 scinart>
// 思路错了：

// 本题我的思路是：先把凹的部分从小到大排除，最后剩一个凸的部分从大到小排，
// 改进后是凸的部分用贪心，从大到小排。

// 再改：现在思路比较清晰了。
// 把所有的都加起来，然后看看有哪些不合理。
// 如果有一个V字型的，那么补差价，就是在总和中左右端点较小着减去V字型底部的值。
// 这样填完坑之后，所有极值点组成新数据，递归填坑。
// 最后把取不到的 max1 和 max2 减去。
// AC了。
// 2014-06-26 23:10:54

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

// vector<PII> vpiiVi;
vector<int> optima;
vector<int> dpoint;

int main()
{
    std::ios::sync_with_stdio(false);
    int N;
    cin>>N;
    // vpiiVi.push_back(PII(0,0));
    optima.push_back(0);
    long long sum = 0;
    int max1=0;
    int max2=0;
    int oldval=0;
    int val=0;
    bool incing =false; //increasing. //important.
    for(int i=1; i<=N; i++)
    {
        cin>>val;
        if(val>max1)
        {
            max2=max1;
            max1=val;
        }
        else
        {
            max2=max(max2,val);
        }
        // vpiiVi.push_back(PII(val,i));
        sum += val;
        if(incing)
        {
            if(val<oldval)
            {// decrease now.
                optima.push_back(oldval);
                incing = false;
            }
            else
            {
                //nothing.
            }
        }
        else
        {
            if(val>oldval)
            {
                incing = true;
                optima.push_back(oldval);
            }
            else
            {
                //nothing.
            }
        }
        oldval = val;
    }
    if(incing)
    {
        optima.push_back(oldval);
    }

    if(N<=2)
    {
        cout<<"0\n";
        return 0;
    }


    int optima_size = optima.size();
    int half_size = optima_size>>1;

    while(optima_size>3)
    {
        REP(i,half_size)
        {
            sum += min(optima[2*i],optima[2*i+2])-optima[2*i+1];
        }

        vector<int> new_optima;
        new_optima.push_back(0);

        bool incing = false; //increasing. //important.
        int oldval=0;
        int val=0;

        for(int i=0; i<optima_size; i+=2)
        {
            val=optima[i];
            if(incing)
            {
                if(val<oldval)
                {// decrease now.
                    new_optima.push_back(oldval);
                    incing = false;
                }
                else
                {
                    //nothing.
                }
            }
            else
            {
                if(val>oldval)
                {
                    incing = true;
                    new_optima.push_back(oldval);
                }
                else
                {
                    //nothing.
                }
            }
            oldval = val;
        }
        if(incing)
        {
            new_optima.push_back(oldval);
        }

        optima.swap(new_optima);
        optima_size = optima.size();
        half_size = optima_size>>1;
    }
    sum-=max1;
    sum-=max2;
    cout<<sum<<'\n';
    return 0;
}
