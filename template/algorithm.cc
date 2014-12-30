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
// 符号与第二个数一致
// 5 -3
// (1)·5+(2)·-3=-1
// -5 3
// (1)·-5+(2)·3=1
template<typename T>
void exEuAid(T& a,T& b,T& res,const T& x, const T& y)
{
    if(y==0)
    {
        res=x;
        a=1;
        b=0;
    }
    else
    {
        exEuAid(a,b,res,y,mod(x,y));
        std::swap(a,b);
        b=-b-a*(mod(x,y));
    }
}
template<typename T>
void exEu(T& a,T& b,T& res, const T& x, const T& y)
{
    if(x>=y)return exEuAid(a,b,res,x,y);
    else return exEuAid(b,a,res,y,x);
}

int gcd(int a, int b)
{
    if (a<0) a=-a;
    if (b<0) b=-b;
    if (a>b)
    {
        int c=a;
        a=b;
        b=c;
    }
    if (a==0)
        return b;
    return gcd(mod(b,a),a);
}

template<typename T>
long long pow(long long n, long long m, long long mod = 0){
    if(m < 0) return 0;
    long long ans = 1;
    long long k = n;
    while(m){
        if(m & 1) {
            ans *= k;
            if(mod) ans %= mod;
        }
        k *= k;
        if(mod) k %= mod;
        m >>= 1;
    }
    return ans;
}
