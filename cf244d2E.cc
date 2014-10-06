// Time-stamp: <2014-10-06 16:00:47 scinart>
// created at 2014-10-06 15:30:51
// cf244d2E.cc
#include <iostream>
#include <algorithm>
using namespace std;
#define REP_1(i, n) for (int i=1; i<=(int)(n); ++i)
typedef long long ll;
ll pos[1000010];
ll tol[1000010];
ll tor[1000010];
ll sum[1000010];
int main()
{
    std::ios::sync_with_stdio(false);cin.tie(0);
    int n,m;cin>>n>>m;
    REP_1(i,n) cin>>pos[i];
    pos[n+1]=pos[n-1];
    pos[0]=pos[1];
    int cap,growthrate;
    cap=growthrate=0;
    for(int i=n;i>=1;i--)
    {
        tol[i]=tol[i+1]+growthrate*(pos[i+1]-pos[i]);
        if(cap) cap--;
        else cap=m-1, growthrate+=2;
    }
    growthrate=cap=0;
    REP_1(i,n)
    {
        tor[i]=tor[i-1]+growthrate*(pos[i]-pos[i-1]);
        if(cap) cap--;
        else cap=m-1, growthrate+=2;
    }
    REP_1(i,n)sum[i]=tol[i]+tor[i];
    // REP_1(i,n)cout<<tol[i]<<' ';cout<<'\n';
    // REP_1(i,n)cout<<tor[i]<<' ';cout<<'\n';
    // REP_1(i,n)cout<<sum[i]<<' ';cout<<'\n';
    cout<<*min_element(sum+1,sum+n+1)<<'\n';
    return 0;
}
