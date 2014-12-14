// Time-stamp: <2014-08-07 12:45:36 scinart>
// created at 2014-08-07 12:17:16
// dx6E.cc

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



int f(int n,int m)
{
    if(n==1 && m==1) return 1;
    if(n==1 && m==2) return 2;
    if(m==1 && n==2) return 2;

    if(m==1)
    {
        swap(n,m);
    }
    if(n==1)
    {
        if(m%2==1)
        {
            return (m/2)*4;
        }
        else
        {
            return (m-1)/2*4+2;
        }
    }



    int ans=0;
    if(n%2==1 && m%2==1)
    {
    }
    else
    {
        ans+=8;
    }

    int up,down,left,right;
    up=(m-1)/2;
    if(m%2==0)
    {
        down=up;
    }
    else
    {
        down=up;
        if(n%2==0)
        {
            down--;
        }
    }

    left=(n-1)/2;
    if(n%2==0)
    {
        right=left;
    }
    else
    {
        right=left;
        if(m%2==0)
        {
            right--;
        }
    }
    int mid=(n-2)*(m-2)/2;
    ans+=8*(down+up+left+right);
    ans+=16*mid;
    return ans;
}
int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    int T;cin>>T;
    REP(i,T)
    {
        int n,m;
        cin>>n>>m;

        cout<<f(n,m)<<'\n';
    }


    return 0;
}
