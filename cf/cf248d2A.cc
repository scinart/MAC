// Codeforces Round #248 div 2 A
// Time-stamp: <2014-05-24 15:07:03 scinart>

#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    std::ios::sync_with_stdio(false);
    int N;
    cin>>N;
    int a100=0;
    int a200=0;
    while(N--)
    {
        int a;
        cin>>a;
        if(a==100)a100++;
        else a200++;
    }
    a200%=2;
    if(a200==0)
    {
        if(a100%2==0) printf("YES\n");
        else printf("NO\n");
    }
    else
    {
        if(a100 >= 2 && a100%2==0) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
