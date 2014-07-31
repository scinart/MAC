#include <cstdio>
#include <bitset>

template<typename T>
T mod(T N, T M)
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

std::bitset<65536> primes;

void f(int N, bool first)
{
    for(int i=2; i<65536; i++)
    {
        if(!primes.test(i))
        {
            if (mod(N,i)==0)
            {
                if(!first) printf("*");
                printf("%d",i);
                if (N/i == 1) {printf("\n"); return;}
                else return f(N/i,false);
            }
            else
            {

            }
        }
        else
        {
            continue;
        }
    }
}
int main()
{
    for(int i=2; i<65536; i++)
    {
        if(!(primes.test(i)))
        {
            for(int j=i+i; j<65536; j+=i)
            {
                primes.set(j);
            }
        }
    }
    int N;
    scanf("%d", &N);
    int a;
    while(N--)
    {
        scanf(" %d", &a);
        f(a,true);
    }
    return 0;
}
