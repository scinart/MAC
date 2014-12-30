#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct P{int F;int S;int T;P(int f,int s,int t):F(f),S(s),T(t){}};
bool Z(P a,P b){return a.F*b.S<b.F*a.S;}
int main(){int n,t,w,q=1;cin>>n;vector<P>v;
for(;n--;q++){cin>>t>>w;v.push_back(P(t,w,q));}
stable_sort(v.begin(),v.end(),Z);
for(typeof(v.end()) i=v.begin();i!=v.end();i++){cout<<i->T<<" ";}
cout<<endl;return 0;}
