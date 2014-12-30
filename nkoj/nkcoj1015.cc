#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;


typedef pair<int,int> PII;
bool PIIFs(const PII& a, const PII& b)
{
    return a.first>b.first || (a.first==b.first && a.second<b.second);
}
bool PIIfs(const PII& a, const PII& b)
{
    return a.first<b.first || (a.first==b.first && a.second<b.second);
}
bool PIIFS(const PII& a, const PII& b)
{
    return a.first>b.first || (a.first==b.first && a.second>b.second);
}




map<PII, int> memo;
int f(int m,const vector<PII>& tc, int where)
{//return least coin used to change m where we have tc[0...where];
    int ans=INT_MIN;
    //int tcsize=tc.size();
    if(m==0) return 0;
    if(where==0)
    {
        if(m%tc[0].first==0 && m/tc[0].first<=tc[0].second)
        {//happy ending.
            return m/tc[0].first;
        }
        else
        {//cannot change due to
#ifndef ONLINE_JUDGE
            cout<<"m is "<<m<<" and tc is ("<<tc[0].first<<' '<<tc[0].second<<")\n";
#endif
            return INT_MIN;
        }
    }
    else if(memo.find(PII(m,where))!=memo.end())
    {// has been memoized.
        return memo[PII(m,where)];
    }
    else
    {// return max_{i=0}^{tc.last().second}{f(m-i*tc.last().first, tc, where--}
        int biggestCoinValue=tc[where].first;
        int biggestCoinNums=tc[where].second;
        int loops = min(biggestCoinNums, m/biggestCoinValue);
        int midans=INT_MAX;
        for(int i=0; i<=loops; i++)
        {//here > 0 and minimim
            int ret=f(m-i*biggestCoinValue, tc, where-1);
            if(ret>=0)
                midans=min(midans, ret+i);
        }
        if(midans!=INT_MAX)
        {//subproblem solution found.
            ans=midans;
        }
        else
        {//no solution
            ans=INT_MIN;
        }
    }
    memo[PII(m,where)]=ans;
    return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    int n;

    cin>>n;
    vector<PII> tc(n);
    for(int i=0; i<n; i++)
    {
        cin>>tc[i].first>>tc[i].second;
    }
    int m;
    cin>>m;

    sort(tc.begin(), tc.end(), PIIfs);
#ifndef ONLINE_JUDGE
    for(int i=0; i<n; i++)
    {
        cout<<tc[i].first<<' '<<tc[i].second<<'\n';
    }
#endif
    int ans=f(m,tc,n-1);
    if (ans<0) ans=-1;
    cout<<ans<<'\n';
    return 0;
}
