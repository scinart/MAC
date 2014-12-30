#include <stdio.h>

/*
  input N
  output Catalan(N)
  a[0]*a[n-1] + a[1]*a[n-2] + …....... + a[n-1]*a[0]; (a0 = 1)
*/

int main()
{
    unsigned long long A[5001];
    unsigned long long M = 20000014;
    A[0]=1;
    int i,j;
    unsigned long long tmp;
    for(i=1;i<=5000;i++)
    {
        tmp=0;
        for(j=0;j<i;j++)
        {
            tmp += A[j]*A[i-j-1]%M;
            tmp %= M;
        }
        A[i]=tmp;
    }
    while(scanf(" %d",&i)!=EOF)
    {
        printf("%llu\n",A[i]);
    }
}
