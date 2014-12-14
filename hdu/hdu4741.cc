// Time-stamp: <2014-08-11 19:29:19 scinart>
// created at 2014-08-11 17:11:39
// hdu4741.cc

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


class vec{
public:
    double x,y,z;
    vec(){};
    vec(double x_,double y_,double z_):x(x_),y(y_),z(z_){}
    vec cross_product(const vec& rhs)const
    {
        return vec(y*rhs.z-z*rhs.y, -(x*rhs.z-z*rhs.x), x*rhs.y-y*rhs.x);
    }
};

class point{
public:
    double x,y,z;
    point(){}
    point(double x_, double y_,double z_):x(x_),y(y_),z(z_){}
    vec formvec(const point& rhs)const
    {
        return vec(x-rhs.x,y-rhs.y,z-rhs.z);
    }
};

typedef double T;

// Gauss-Jordan elimination with full pivoting.
//
// Uses:
//   (1) solving systems of linear equations (AX=B)
//   (2) inverting matrices (AX=I)
//   (3) computing determinants of square matrices
//
// Running time: O(n^3)
//
// INPUT:    _a[][] = an nxn matrix
//           _b[][] = an nxm matrix
//
// OUTPUT:   X      = an nxm matrix (stored in _b[][])
//           A^{-1} = an nxn matrix (stored in _a[][])
//           returns determinant of _a[][]

const int n = 3;
const int m = 2;

double _a[n][n];
double _b[n][m];
double _tmpa[n];
double _tmpb[m];
int _irow[n],_icol[n],_ipiv[n];
T GaussJordan()
{
    for(int i=0; i<n; i++)
    {
        _irow[i]=0;
        _icol[i]=0;
        _ipiv[i]=0;
    }
    T det = 1;

    for (int i = 0; i < n; i++) {
        int pj = -1, pk = -1;
        for (int j = 0; j < n; j++)
            if (!_ipiv[j])
                for (int k = 0; k < n; k++)
                    if (!_ipiv[k])
                        if (pj == -1 || fabs(_a[j][k]) > fabs(_a[pj][pk])) { pj = j; pk = k; }
        _ipiv[pk]++;

        // if(pj!=pk)
        //     for(int i=0; i<n; i++)
        //     {
        //         _tmp[i]=_a[pj][i]; _a[pj][i]=_a[pk][i];_a[pk][i]=_tmp[i];
        //         _tmp[i]=_b[pj][i]; _b[pj][i]=_b[pk][i];_b[pk][i]=_tmp[i];
        //     }
        if(pj!=pk)
        {
            for(int i=0; i<n; i++)
            {
                _tmpa[i]=_a[pj][i]; _a[pj][i]=_a[pk][i];_a[pk][i]=_tmpa[i];
            }
            for(int i=0; i<m; i++)
            {
                _tmpb[i]=_b[pj][i]; _b[pj][i]=_b[pk][i];_b[pk][i]=_tmpb[i];
            }
        }

        if (pj != pk) det *= -1;
        _irow[i] = pj;
        _icol[i] = pk;

        T c = 1.0 / _a[pk][pk];
        det *= _a[pk][pk];
        _a[pk][pk] = 1.0;
        for (int p = 0; p < n; p++) _a[pk][p] *= c;
        for (int p = 0; p < m; p++) _b[pk][p] *= c;
        for (int p = 0; p < n; p++)
            if (p != pk) {
                c = _a[p][pk];
                _a[p][pk] = 0;
                for (int q = 0; q < n; q++) _a[p][q] -= _a[pk][q] * c;
                for (int q = 0; q < m; q++) _b[p][q] -= _b[pk][q] * c;
            }
    }

    for (int p = n-1; p >= 0; p--)
        if (_irow[p] != _icol[p]) {
            for (int k = 0; k < n; k++)
            {
                double ttmp=_a[k][_irow[p]];
                _a[k][_irow[p]] = _a[k][_icol[p]];
                _a[k][_icol[p]] = ttmp;
            }
        }

    return det;
}

double dis(double a0,double a1,double a2,double a3,double a4,double a5)
{
    return sqrt((a1-a0)*(a1-a0)+(a3-a2)*(a3-a2)+(a5-a4)*(a5-a4));
}
int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    double xa1,ya1,za1,xa2,ya2,za2;
    double xb1,yb1,zb1,xb2,yb2,zb2;

    int cases;
    scanf("%d", &cases);
    REP(cc,cases){
        scanf("%lf %lf %lf", &xa1,&ya1,&za1);
        scanf("%lf %lf %lf", &xb1,&yb1,&zb1);
        scanf("%lf %lf %lf", &xa2,&ya2,&za2);
        scanf("%lf %lf %lf", &xb2,&yb2,&zb2);

        point A(xa1,ya1,za1);
        point B(xb1,yb1,zb1);
        point C(xa2,ya2,za2);
        point D(xb2,yb2,zb2);

        vec a = A.formvec(B);
        vec b = C.formvec(D);

        vec alpha0 = a.cross_product(b);
        vec alpha1 = a.cross_product(alpha0);
        vec alpha2 = b.cross_product(alpha0);

        double
            a0=alpha0.x,
            a1=alpha1.x,
            a2=alpha2.x,
            b0=alpha0.y,
            b1=alpha1.y,
            b2=alpha2.y,
            c0=alpha0.z,
            c1=alpha1.z,
            c2=alpha2.z;


        _a[0][0]=a1;
        _a[0][1]=b1;
        _a[0][2]=c1;
        _a[1][0]=a2;
        _a[1][1]=b2;
        _a[1][2]=c2;
        _a[2][0]=a0;
        _a[2][1]=b0;
        _a[2][2]=c0;


        _b[0][0]=a1*xa1+b1*ya1+c1*za1;
        _b[1][0]=a2*xa2+b2*ya2+c2*za2;
        _b[2][0]=a0*xa1+b0*ya1+c0*za1;

        _b[0][1]=a1*xa1+b1*ya1+c1*za1;
        _b[1][1]=a2*xa2+b2*ya2+c2*za2;
        _b[2][1]=a0*xa2+b0*ya2+c0*za2;

        GaussJordan();

        double p1x=_b[0][1];
        double p1y=_b[1][1];
        double p1z=_b[2][1];

        double p2x=_b[0][0];
        double p2y=_b[1][0];
        double p2z=_b[2][0];


        printf("%.6lf\n",dis(p1x,p2x,p1y,p2y,p1z,p2z));

        printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n",p2x,p2y,p2z,p1x,p1y,p1z);
    }
    return 0;
}
