#include <cstdio>
#define uint128 __uint128_t
#define int128 __int128_t
#define LL int128
long long MOD = 1e10+7;
LL mymod(LL N, LL M)
{
    // return canonical N%M
    if((M>0 && N>0) || (M<0 && N<0))
    {
        return N%M;
    }
    else if (M*N<0)
    {
        return N%M+((N%M)?M:0);
    }
    else
        return 0;
}

LL pow(LL n, LL m, LL mod)
{
    if(m < 0) return 0;
    if(m==0) return 1;
    LL ans = 1;
    LL k = n;
    while(m){
        if(m & 1) {
            ans *= k;
            if(mod) ans = mymod(ans , mod);
        }
        k *= k;
        if(mod) k = mymod(k,mod);
        m >>= 1;
    }
    return ans;
}

int main()
{
    int cases;scanf("%d", &cases);
    while(cases--)
    {
        long long ans=0;
        int n;
        long long k;
        long long A;
        int i;
        scanf("%d", &n);
        scanf("%lld", &k);
        for(i=0; i<n; i++)
        {
            scanf("%lld", &A);
            ans += pow(A, k, MOD);
        }
        ans = mymod(ans,MOD);
        printf("%lld\n", ans);
    }
    return 0;
}
