//
// Time-stamp: <2014-08-06 16:37:21 scinart>

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

#define ROF(i, a, b) for (int i = (b); --i >= (a); )

const int N = 1200;
unsigned char a[N+1];
int sa[N], rnk[N], lcp[N], q[N];
int _rmq_d[N][30];
namespace KoAluru
{
int n;
bool *t;
int *b;

void RMQ_Init(const vector<int>& A)
{
    int n=A.size();
    for (int i=0;i<n;i++) _rmq_d[i][0]=A[i];
    for (int j=1;(1<<j)<=n;j++)
        for (int i=0;i+(1<<j)-1<n;i++)
            _rmq_d[i][j]=min(_rmq_d[i][j-1],_rmq_d[i+(1<<(j-1))][j-1]);
}
void RMQ_Init(int A[], int size)
{
    int n=size;
    for (int i=0;i<n;i++) _rmq_d[i][0]=A[i];
    for (int j=1;(1<<j)<=n;j++)
        for (int i=0;i+(1<<j)-1<n;i++)
            _rmq_d[i][j]=min(_rmq_d[i][j-1],_rmq_d[i+(1<<(j-1))][j-1]);
}

int __RMQ(int L,int R)
{
    int k=0;
    for (k=0;1<<(k+1)<=R-L+1;k++);
    return min(_rmq_d[L][k],_rmq_d[R-(1<<k)+1][k]);
}

int lcp_range(int l,int r)
{
    if(l==r)return n-sa[l];
    if(l>r) swap(l,r);
    return __RMQ(l+1,r);
}


template<typename T>
void bucket(T a[], int n, int k, bool end)
{
    fill_n(b, k, 0);
    REP(i, n) b[a[i]]++;
    if (end)
        FOR(i, 1, k) b[i] += b[i-1];
    else {
        int s = 0;
        REP(i, k)
            s += b[i], b[i] = s-b[i];
    }
}

template<typename T>
void plus_to_minus(T a[], int sa[], int n, int k)
{
    bucket(a, n, k, false);
    sa[b[a[n-1]]++] = n-1;
    REP(i, n-1) {
        int j = sa[i]-1;
        if (j >= 0 && ! t[j])
            sa[b[a[j]]++] = j;
    }
}

template<typename T>
void minus_to_plus(T a[], int sa[], int n, int k)
{
    bucket(a, n, k, true);
    ROF(i, 0, n) {
        int j = sa[i]-1;
        if (j >= 0 && t[j])
            sa[--b[a[j]]] = j;
    }
}

template<typename T>
void ka(T a[], int sa[], int n, int k)
{
    t[n-1] = false;
    ROF(i, 0, n-1)
        t[i] = a[i] < a[i+1] || (a[i] == a[i+1] && t[i+1]);
    bool minor = 2 * count(t, t+n, false) > n;

    bucket(a, n, k, minor);
    fill_n(sa, n, -1);
    if (minor) {
        REP(i, n)
            if (t[i])
                sa[--b[a[i]]] = i;
        plus_to_minus(a, sa, n, k);
        minus_to_plus(a, sa, n, k);
    } else {
        sa[b[a[n-1]]++] = n-1;
        REP(i, n-1)
            if (! t[i])
                sa[b[a[i]]++] = i;
        minus_to_plus(a, sa, n, k);
        plus_to_minus(a, sa, n, k);
    }

    int last = -1, name = 0, nn = count(t, t+n, minor);
    int *sa2, *pi;
    if (minor)
        sa2 = sa, pi = sa+n-nn;
    else
        sa2 = sa+n-nn, pi = sa;
    fill_n(b, n, -1);
    REP(i, n)
        if (sa[i] >= 0 && minor == t[sa[i]]) {
            bool diff = last == -1;
            int p = sa[i];
            if (! diff)
                REP(j, n) {
                    if (last+j >= n || p+j >= n || a[last+j] != a[p+j] || t[last+j] != t[p+j]) {
                        diff = true;
                        break;
                    } else if (j > 0 && (minor == t[last+j] || minor == t[p+j]))
                        break;
                }
            if (diff) {
                name++;
                last = p;
            }
            b[p] = name-1;
        }
    nn = 0;
    REP(i, n)
        if (b[i] >= 0)
            pi[nn++] = b[i];

    if (name < nn)
        ka(pi, sa2, nn, name);
    else
        REP(i, nn)
            sa2[pi[i]] = i;

    ROF(i, 0, nn)
        t[i] = a[i] < a[i+1] || ( a[i] == a[i+1] && t[i+1] );

    nn = 0;
    bucket(a, n, k, minor);
    REP(i, n)
                      if (minor == t[i])
                          pi[nn++] = i;
    if (minor) {
        REP(i, nn)
            sa[i] = pi[sa2[i]];
        ROF(i, 0, nn) {
            int j = sa[i];
            sa[i] = -1;
            sa[--b[a[j]]] = j;
        }
    } else {
        ROF(i, 0, nn)
            sa[n-nn+i] = pi[sa2[i]];
        REP(i, nn) {
            int j = sa[n-nn+i];
            sa[n-nn+i] = -1;
            sa[b[a[j]]++] = j;
        }
    }
    if (minor)
        plus_to_minus(a, sa, n, k);
    else
        minus_to_plus(a, sa, n, k);
}

template<typename T>
void calc_rank_lcp(T a[], int sa[], int rank[], int lcp[])
{
    REP(i, n)
        rank[sa[i]] = i;
    int k = 0;
    lcp[0] = 0;
    REP(i, n)
        if (rank[i]) {
            for (int j = sa[rank[i]-1]; i+k < n && j+k < n && a[i+k] == a[j+k]; k++);
            lcp[rank[i]] = k;
            k && k--;
        }
}

template<typename T>
void KAmain(T a[], int sa[], int b[], int n, int k)
{
    KoAluru::n = n;
    KoAluru::b = b;
    if (n > 0) {
        t = new bool[n];
        ka(a, sa, n, k);
        delete[] t;
    }
    calc_rank_lcp(a, sa, rnk, lcp);
    RMQ_Init(lcp,n);
}

};




int main()
{
    std::ios::sync_with_stdio(false);
    string s;string sharp="#";
    while(cin>>s && s!=sharp)
    {
        REP(i,s.size())
        {
            a[i]=s[i];
        }
        a[s.size()]='\0';
        int n=s.size();
        KoAluru::KAmain(a, sa, q, n, 128);
        LL ans=0;
        for(int i=0; i<n; i++)
        {
            int j=i+1;
            int local_max = 0;
            while(KoAluru::lcp_range(i, j)>lcp[i] && j<n)
            {
                checkmax(local_max, min(abs(sa[j]-sa[i]), KoAluru::lcp_range(i,j))-lcp[i]);
                j++;
            }
            ans+=local_max;
        }
        {
            cout<<ans<<'\n';
        }
#ifndef ONLINE_JUDGE
        puts("sa");
        REP(i, n)
            printf("%d: %d\n", i, sa[i]);
        puts("rank");
        REP(i, n)
            printf("%d: %d\n", i, rnk[i]);
        puts("lcp");
        REP(i, n)
            printf("%d: %d\n", i, lcp[i]);
#endif
    }
}
