//nkoj 1760
#include <stdio.h>
// biggest sum of subarray.
// suppose A[p..q] is the biggest sum of all subarray.
// then A[i..p) must be negative.
// and  A[p..j] probable be positive (j≤q) //in case all number is negetive.
#define max(a,b) ((a>b)?(a):(b))
int main()
{
    int N,a;
    while (scanf ("%d", &N)!=EOF)
    {
        int max_ = 0;
        int prefix = 0;
        int maxelem = 0x80000000;
        while(N--)
        {
            scanf(" %d", &a);
            prefix += a;
            if(prefix<0)
                prefix=0;
            max_=max(max_, prefix);
            maxelem=max(maxelem, a);
        }
        printf("%d\n", maxelem>0?max_:maxelem);
    }
}

