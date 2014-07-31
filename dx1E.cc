// Time-stamp: <2014-07-22 17:38:50 scinart>
// created at 2014-07-22 14:41:06
// dx1E.cc

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
bool checkmin(T& a,const T& b){if(b<a){a=b;return true;}else return false;}
template <typename T>
bool checkmax(T& a, const T& b){if(b>a){a=b;return true;}else return false;}

const int K = 3;
const int N = 4;

int O[N] = {0,1,2,3}; //观察空间
//Dry , Dryish , Damp and Soggy.
int S[K] = {0,1,2}; //状态S
//Sunny, Cloudy and  Rainy

double A[3][3] = {
    {0.5, 0.375, 0.125},
    {0.25, 0.125, 0.625},
    {0.25, 0.375, 0.375}
};
double B[3][4] = {
    {0.6, 0.2, 0.15, 0.05},
    {0.25, 0.3, 0.2, 0.25},
    {0.05, 0.1, 0.35, 0.5}
};
double pi[] = {
    0.63, 0.17, 0.2
};

// double A[2][2] = {
//     {0.7, 0.3},
//     {0.4, 0.6}
// };
// double B[2][3] = {
//     {0.5, 0.4, 0.1},
//     {0.1, 0.3, 0.6}
// };
// double pi[2] = {
//     0.6, 0.4
// };

VI Y; //观察序列
int T; //序列长度
vector<double> T1[K];
vector<int> T2[K];
vector<int> Z;
vector<int> X;

const double MINUS_INF = -1e9;

#define PP(x) do{ \
        cout<<x<<'\n';                                                    \
        REP(i,K){EACH(it,T1[i]) cout<<exp(*it)<<'\t'; cout<<'\n';}         \
        REP(i,K){EACH(it,T2[i]) cout<<(*it)<<'\t'; cout<<'\n';} }while(0)

// #define PP(x) do{}while(0)
void init()
{
    REP(i,K)REP(j,K) A[i][j] = log(A[i][j]);
    REP(i,K)REP(j,N) B[i][j] = log(B[i][j]);
    REP(i,K)pi[i] = log(pi[i]);
}
void viterbi()
{
    REP(i,K)EACH(it,T1[i])*it=MINUS_INF;
    REP(i,K){
        T1[i][0] = pi[i]+B[i][Y[0]];
        T2[i][0] = 0;
    }
    PP("11");
    for(int i=1; i<T; i++)
    {
        REP(j,K)
        {
            REP(k,K)
            {
                if(checkmax(T1[j][i],T1[k][i-1]+A[k][j]+B[j][Y[i]]))
                {
                    T2[j][i] = k;
                }
            }
        }
    }
    PP("22");
    double tmp = (MINUS_INF);
    REP(i,K)
    {
        if(checkmax(tmp,T1[i][T-1]))
        {
            Z[T-1] = i;
        }
    }
    X[T-1] = S[Z[T-1]];
    for(int i=T-1; i>=1; i--)
    {
        Z[i-1] = T2[Z[i]][i];
        X[i-1] = S[Z[i-1]];
    }
}

int main()
{
    std::ios::sync_with_stdio(false);


// VI Y; //观察序列
// int T; //序列长度
// vector<double> T1[K];
// vector<int> T2[K];
// vector<int> Z;
// vector<int> X;

    map<string,int> msileaf;
    msileaf["Dry"] = 0;
    msileaf["Dryish"] = 1;
    msileaf["Damp"] = 2;
    msileaf["Soggy"] = 3;

    map<int,string> msileaf_;
    msileaf_[0] = string("Dry");
    msileaf_[1] = string("Dryish");
    msileaf_[2] = string("Damp");
    msileaf_[3] = string("Soggy");

    map<string,int> msiweather;
    msiweather["Sunny"] = 0;
    msiweather["Cloudy"] = 1;
    msiweather["Rainy"] = 2;

    map<int,string> msiweather_;
    msiweather_[0] = string("Sunny");
    msiweather_[1] = string("Cloudy");
    msiweather_[2] = string("Rainy");

    init();
    int cases;cin>>cases;
    REP(cc, cases)
    {
//todo clear;
        cin>>T;
        Y.resize(T);
        REP(i,K)T1[i].resize(T);
        REP(i,K)T2[i].resize(T);
        Z.resize(T);
        X.resize(T);

        REP(x,T)
        {
            string s;
            cin>>s;
            Y[x] = msileaf[s];
        }

        viterbi();

        cout<<"Case #"<<cc+1<<":\n";
        EACH(it,X)cout<<msiweather_[*it]<<'\n';

    }
    return 0;
}
