//problem 1542
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <cassert>
#include <vector>
#include <cstring>
#include <list>
#include <map>
#include <deque>
#include <bitset>

using namespace std;
// 0-1背包问题
class PII
{
public:
    int a; //time
    int b; //value
    PII(int aa,int bb)
    {
        a=aa;
        b=bb;
    }
    bool operator<(const PII& rhs)const
    {
        return (a<rhs.a) || (a==rhs.a && b>rhs.b);
    }
    bool operator==(const PII& rhs)const
    {
        return a==rhs.a && b==rhs.b;
    }
};

typedef vector<PII> gvii;

int memoize(int remain_time,const gvii & gv, int endf)
{
    // assert gv is sorted.
    static map<PII, int> memo;
    while(true)
    {
        if (endf==0) return 0;
        if (remain_time<=0) return 0;
        if (memo.find(PII(remain_time, endf))!=memo.end())
            return memo[PII(remain_time, endf)];
        if (remain_time >= gv[endf-1].a)
        {
            int val = gv[endf-1].b;
            int used_time = gv[endf-1].a;
            endf--;
            val += memoize(remain_time-used_time, gv,endf);//use the most time-consuming-option
            int obtionb = memoize(remain_time, gv, endf); //don't pick the most time-consuming option.
            memo[PII(remain_time, endf+1)] = max(val, obtionb);
            return max(val, obtionb);
        }
        else
        {
            endf--;
        }
    }
}

int main()
{
    freopen("input", "r", stdin);
    int T,M;
    scanf("%d %d",&T,&M);
    gvii gv;
    int a,b;
    for(int i=0; i<M; i++)
    {
        scanf("%d %d",&a,&b);
        gv.push_back(PII(a,b));
    }
    sort(gv.begin(), gv.end());
    printf("%d\n", memoize(T, gv, gv.size()));
}

