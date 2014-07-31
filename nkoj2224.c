#include <stdio.h>
#include <math.h>

int main()
{
    int l,r;
    while(scanf("%d %d",&l,&r) != EOF)
    {
        long long int Q = floor(sqrt((double)l));
        long long int R = floor(sqrt((double)r));
        long long int k = R-Q;
        printf("l: %d r: %d\n", l, r);
        printf("Q: %lld R: %lld k: %lld\n",Q,R,k);
        if (k==0)
        {
            long long int res;
            res = Q*(r-l+1);
            printf("%lld\n", res);
            continue;
        }
        long long int sum_of_middle = (k-1)*(k-2)*(k)/3*2;
        sum_of_middle += (3+2*Q)*(k-1)*(k)/2;
        long long int sum_total = sum_of_middle;
        sum_total += (r-l+1)*Q;
        sum_total += (r-R*R+1)*(R-Q);
        printf("%lld\n", sum_total);
        continue;
    }
    return 0;
}
