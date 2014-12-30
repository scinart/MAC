#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

string s;
bool test(int N)
{
    if(s[N]=='E' && (((N-1>0) && s[N-1]=='E')
                    ||
                   (N+1<s.length() && s[N+1]=='E')))
        return true;
    else
        return false;
}

int main()
{
    int N;
    cin>>N;
    cin>>s;
    if(N%2==1)
    {//odd
        for(int i=1,j=1; i<=N; i++, j*=-1)
        {
            if(test(N/2+j*i/2))
            {
                printf("%d\n", N/2+j*i/2);
                return 0;
            }
        }
        printf("-1\n");
    }
    else
    {
        for(int i=1,j=-1; i<=N; i++, j*=-1)
        {
            if(test(N/2-1+j*i/2))
            {
                printf("%d\n", N/2-1+j*i/2);
                return 0;
            }
        }
        printf("-1\n");
    }
}
