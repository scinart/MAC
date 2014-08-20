// Time-stamp: <2014-08-21 01:53:11 scinart>
// created at 2014-08-21 00:43:35
// cf262d2D.cc

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

ll msb(ll x)
{
    ll ans=1;
    while((x>>=1))ans<<=1;
    return ans;
}
int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    ll l,r,k;
    cin>>l>>r>>k;

    if(r-l+1>=7 && k>=4)
    {
        cout<<"0\n";
        while(l%4!=0)l++;
        cout<<"4\n";
        cout<<l<<' '<<l+1<<' '<<l+2<<' '<<l+3<<'\n';
    }
    else if(r-l+1<7)
    {
        //brute force;
        int bits=r-l+1;
        ll minans=l;
        for(int i=1; i<(1<<bits); i++)
        {
            ll tempxor=0;
            bitset<6> bs(i);
            if(bs.count()>k)continue;

            for(int b=0; b<6; b++)
            {
                if(bs.test(b))
                {
                    tempxor^=(l+b);
                }
            }
            checkmin(minans,tempxor);
        }

        for(int i=1; i<(1<<bits); i++)
        {
            ll tempxor=0;
            bitset<6> bs(i);
            if(bs.count()>k)continue;

            for(int b=0; b<6; b++)
            {
                if(bs.test(b))
                {
                    tempxor^=(l+b);
                }
            }
            if(tempxor==minans)
            {
                cout<<tempxor<<'\n';
                cout<<bs.count()<<'\n';
                for(int b=0; b<5; b++)
                {
                    if(bs.test(b))
                    {
                        cout<<l+b<<' ';
                    }
                }
                cout<<'\n';
                break;
            }
        }
    }
    else if(k==3)
    {
        if(msb(l)==msb(r))
        {
            if((l^(l+1))==1)
            {
                r=l+1;
            }
            else
            {
                l++;r=l+1;
            }
            cout<<(l^r)<<'\n';
            cout<<"2\n";
            cout<<l<<' '<<r<<'\n';
        }
        else
        {
            ll ones=(msb(l)<<1)-1;
            ll sb = ones+1+((ones+1)>>1);
            if(r>=sb)
            {
                cout<<"0\n";
                cout<<"3\n";
                cout<<sb<<' '<<sb-1<<' '<<ones<<'\n';
            }
            else
            {
                if((l^(l+1))==1)
                {
                    r=l+1;
                }
                else
                {
                    l++;r=l+1;
                }
                cout<<(l^r)<<'\n';
                cout<<"2\n";
                cout<<l<<' '<<r<<'\n';
            }
        }
    }
    else if(k==2)
    {
        if(r-l==1)
        {//only two candidates.
            if((l^r)<l)
            {
                cout<<(l^r)<<'\n';
                cout<<"2\n";
                cout<<l<<' '<<r<<'\n';
            }
            else
            {
                cout<<l<<'\n'<<1<<'\n'<<l<<'\n';
            }
        }
        else
        {
            if((l^(l+1))==1)
            {
                r=l+1;
            }
            else
            {
                l++;r=l+1;
            }
            cout<<(l^r)<<'\n';
            cout<<"2\n";
            cout<<l<<' '<<r<<'\n';
        }
    }
    else //if(k==1)
    {
        cout<<l<<'\n'<<"1\n"<<l<<'\n';
    }



    return 0;
}
