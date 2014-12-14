// Codeforces 426A.cc
// Time-stamp: <2014-04-27 23:42:44 scinart>

#include <iostream>
#include <fstream>
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
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
bool piig(const pii& a, const pii& b)
{
    return a.first<b.first || (a.first == b.first && a.second<b.second);
}


template <class T> inline T abs1(T a) {return a < 0 ? -a : a;}
template <class T> inline T max1(T a, T b) { return a > b ? a : b; }
template <class T> inline T max1(T a, T b, T c) { return max1(max1(a, b), c); }
template <class T> inline T max1(T a, T b, T c, T d) { return max1(max1(a, b, c), d); }
template <class T> inline T max1(T a, T b, T c, T d, T e) { return max1(max1(a, b, c, d), e); }
template <class T> inline T min1(T a, T b) { return a < b ? a : b; }
template <class T> inline T min1(T a, T b, T c) { return min1(min1(a, b), c); }
template <class T> inline T min1(T a, T b, T c, T d) { return min1(min1(a, b, c), d); }
template <class T> inline T min1(T a, T b, T c, T d, T e) { return min1(min1(a, b, c, d), e); }


#define LOOP(var, times) for (int var=0; var<(times); var++)
#define ITER(c, it) for (typeof((c).begin()) it=(c).begin(); it!=(c).end(); it++)

#define FOR(i, b, e) for ((i)=(int)(b); (i)<(int)(e); (i)++)
#define RFOR(i, rb, re) for ((i)=(int)(rb); (int)(re)<=(i); (i)--)

#define RS(X) scanf(" %s", (X))
#define RI(X) scanf(" %d", &(X))
#define R2I(X, Y) scanf(" %d %d", &(X), &(Y))
#define R3I(X, Y, Z) scanf(" %d %d %d", &(X), &(Y), &(Z))
#define R4I(W, X, Y, Z) scanf(" %d %d %d %d", &(W), &(X), &(Y), &(Z))
#define MS0(X) memset((X), 0, sizeof((X)))
#define MS1(X) memset((X), -1, sizeof((X)))

int main()
{
    int n,s,m=0,sum=0,tmp;

    R2I(n,s);

    LOOP(i,n)
    {
        RI(tmp);
        sum+=tmp;
        m=max1(m, tmp);
    }

    if(sum-m<=s)
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
