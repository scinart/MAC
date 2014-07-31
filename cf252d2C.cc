// Time-stamp: <2014-07-21 23:40:10 scinart>
// created at 2014-07-21 22:31:35
// cf2522C.cc
// 题不难但是没过 
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


int simple(int n,int m,int k)
{
    if(m==1)
    {
        if(k==1)
        {
            cout<<n<<' ';
            REP_1(x,n)
            {
                cout<<x<<' '<<m<<' ';
            }
            cout<<'\n';
        }
        else
        {
            while(k!=1)
            {
                cout<<"2 ";
                cout<<n<<' '<<m<<' '<<n-1<<' '<<m<<' ';
                n-=2;
                k--;
            }
            simple(n,m,k);
        }
        return true;
    }
    else if(n==1)
    {
        if(k==1)
        {
            cout<<m<<' ';
            REP_1(x,m)
            {
                cout<<n<<' '<<x<<' ';
            }
            cout<<'\n';
        }
        else
        {
            while(k!=1)
            {
                cout<<"2 ";
                cout<<n<<' '<<m<<' '<<n<<' '<<m-1<<' ';
                m-=2;
                k--;
            }
            cout<<'\n';
            simple(n,m,k);
        }
        return true;
    }
    else if (k<=n)
    {
        int kk=k-1;
        int nn=k-1;
        {
            int space = kk-nn;
            int row_lenn = m-space;
            REP_1(i,nn)
            {
                cout<<row_lenn<<' ';
                for(int j=m-row_lenn+1; j<=m; j++)
                {
                    cout<<i<<' '<<j<<' ';
                }
                cout<<'\n';
            }
            REP(i,space)
            {
                cout<<nn<<' ';
                REP_1(j,nn)
                {
                    cout<<j<<' '<<i+1<<' ';
                }
                cout<<'\n';
            }
        }
        {
            int nn_start = k;
            int nn_end = n;
            cout<<m*(nn_end-nn_start+1)<<' ';
            bool direction = true;
            while(nn_start <= nn_end)
            {
                if(direction)
                    REP_1(j,m)
                    {
                        cout<<nn_start<<' '<<j<<' ';
                    }
                else
                {
                    DWN(j,m,0)
                    {
                        cout<<nn_start<<' '<<j<<' ';
                    }
                }
                direction = !direction;
                nn_start++;
            }
            cout<<'\n';
        }
        return true;
    }
    else if (k<=m)
    {
        DWN(j,m,m-k+1)
        {
            cout<<n<<' ';
            REP_1(i,n)
            {
                cout<<i<<' '<<j<<' ';
            }
            cout<<'\n';
        }
        m -= (k-1);
        {
            int nn_start = 1;
            int nn_end = n;
            cout<<m*(nn_end-nn_start+1)<<' ';
            bool direction = true;
            while(nn_start <= nn_end)
            {
                if(direction)
                    REP_1(j,m)
                    {
                        cout<<nn_start<<' '<<j<<' ';
                    }
                else
                {
                    DWN(j,m,0)
                    {
                        cout<<nn_start<<' '<<j<<' ';
                    }
                }
                direction = !direction;
                nn_start++;
            }
            cout<<'\n';
        }
        return true;
    }
    return false;
}
void solve(int n,int m,int k)
{
    if(simple(n,m,k))
    {
        return;
    }
    if(k>m)
    {
        if(m%2==0)
        {
            for(int nn = n; nn>n-2; nn--)
            {
                cout<<"2 ";
                for(int i=1; i<=m; i++)
                {
                    cout<<nn<<' '<<i<<' '<<nn<<' '<<i+1<<' ';
                    i++;
                }
                cout<<'\n';
            }
        }
        else
        {
            for(int nn = n; nn>n-2; nn--)
            {
                cout<<"2 ";
                for(int i=1; i<=m-1; i++)
                {
                    cout<<nn<<' '<<i<<' '<<nn<<' '<<1+i<<' ';
                    i++;
                }
                cout<<'\n';
            }
            cout<<"2 ";
            cout<<n<<' '<<m<<' '<<n-1<<' '<<m<<' ';
            cout<<'\n';
        }
        solve(n-2,m,k-m);
    }
}
int main()
{
    std::ios::sync_with_stdio(false);

    int n,m,k;
    cin>>n>>m>>k;

    solve(n,m,k);

    return 0;
}
