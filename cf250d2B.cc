// codeforces round 250 div 2 A.
// Time-stamp: <2014-06-01 22:39:38 scinart>

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

#define MM 15
int arr[] = {1,3,8,20,48,112,256,576,1280,2816,6144,13312,28672,61440,131072,278528};


// void solve(int limit, int target, vector<int>& ans)
// {
//     vector<int> headers;
//     int curans = 0;
//     bool first = false;
//     for(int i=(1<<28),j=28; i>0; i>>=1,j--)
//     {
//         if( first || (limit&i) )
//         {
//             first = true;
//             //if(curans+(1<<headers.size())*i<=target)
//             //later!!: headers.push_back(i);
//             int hs =headers.size();
//             cout<<"headers :";
//             EACH(it,headers)
//             {
//                 cout<<*it<<" ";
//             }
//             cout<<"\n";
//             for(int hi=0; hi<(1<<hs); hi++)
//             {//add them one by one.
//                 printf("curans is %d, i: %d\n", curans,i);
//                 if(curans + i <= target)
//                 {
//                     int anstopushback=i;
//                     for(int ji=0; ji<hs; ji++)
//                     {
//                         if(hi&(1<<ji))
//                         {
//                             anstopushback |= headers[ji];
//                         }
//                     }
//                     if(anstopushback<=limit)
//                     {
//                         ans.push_back(anstopushback);
//                         curans+=i;
//                     }
//                 }
//                 else if(curans == target)
//                 {
//                     return;
//                 }
//                 else
//                 {
//                     break;
//                 }
//             }
//             if(i&limit)
//             {
//                 headers.push_back(i);
//             }
//         }
//     }
// }

int low(int x)
{
    for(int i=0; i<30; i++)
    {
        if((1<<i)&x)
        {
            return (1<<i);
        }
    }
    return 0;
}

int main()
{
    std::ios::sync_with_stdio(false);

    // int ar[MM];
    // ar[1]=1;
    // for(int i=2; i<=MM; i++)
    // {
    //     ar[i]=2*ar[i-1]+(1<<(i-1));
    //     cout<<ar[i]+(1<<i)<<" ";
    // }

    int sum,limit;
    cin>>sum>>limit;
    int limittotal=0;
    for(int i=(1<<28),j=28; i>0; i>>=1,j--)
    {
        if(limit&i)
        {
            limittotal += arr[j];
        }
    }
    // cout<<limittotal;
    if(limittotal>=sum)
    {


        vector<PII> arr;
        vector<int> sol;
        for(int i=1; i<=limit; i++)
        {
            arr.push_back(PII(i,low(i)));
        }
        sort(arr.begin(), arr.end(), PIISf);

        int curans = 0;
        for(int i=0; i<limit; i++)
        {
            if(curans+arr[i].second<sum)
            {
                curans+=arr[i].second;
                sol.push_back(arr[i].first);
            }
            else if (curans+arr[i].second==sum)
            {// got it.
                sol.push_back(arr[i].first);
                cout<<sol.size()<<"\n";
                EACH(it,sol)
                {
                    cout<<*it<<" ";
                }
                cout<<"\n";
                return 0;
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        cout<<"-1\n";
    }

    return 0;
}
