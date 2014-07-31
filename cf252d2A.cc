#include <iostream>
#include <sstream>
using namespace std;

bool ok[100] = { 0 };
int main()
{
    int T;cin>>T;
    int money;cin>>money;
    for(int i=0; i<T; i++)
    {
        int k;cin>>k;
        for(int j=0; j<k; j++)
        {
            int x;
            cin>>x;
            if(x<money) ok[i]=true;
        }
    }
    stringstream ss;
    int cnt = 0;
    for(int i=0; i<T; i++)
    {
        if(ok[i])
        { ss<<i+1<<' ';
            cnt++;}
    }
    cout<<cnt<<'\n'<<ss.str()<<'\n';
    return 0;
}
