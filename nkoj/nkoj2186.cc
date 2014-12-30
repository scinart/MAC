// nkoj2186
// Time-stamp: <2014-05-23 21:05:18 scinart>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
template <typename T> inline T min(T a, T b, T c) { return min(min(a, b), c); }
int dp[2000][2000]={{0}};
string a,b; int k;
int Lev(int ae, int se){
    if(ae==0) return k*se;
    if(se==0) return k*ae;
    if(dp[ae][se]!=0) return dp[ae][se];
    else return dp[ae][se]=min(Lev(ae,se-1)+k, Lev(ae-1,se)+k, Lev(ae-1,se-1)+min(2*k, abs(a[ae-1]-b[se-1])));
}
int main(){
    cin>>a>>b>>k;
    cout<<Lev(a.size(),b.size())<<endl;
    return 0;
}
