namespace DSET {

const int MAXN = ...;
#error please specifi MAXN;
int pre[MAXN],Rank[MAXN];
int degree;
// default is 1-indexed
void init(int n) /* 初始化函数 */
{
    degree=n;
    REP_1(i,n) pre[i]=i, Rank[i]=1;
}

int fin(int x)
{
    int t,r=x;
    while(x!=pre[x]) x=pre[x];
    while(r!=x)
    {
        t=pre[r];
        pre[r]=x;
        r=t;
    }
    return x;
}

inline int test(int x,int y)
{
    return fin(x)==fin(y);
}
int unio(int a,int b)
{
    a=fin(a);
    b=fin(b);
    if(a==b) return a;
    degree--;
    if(Rank[a]>=Rank[b])
        return pre[b]=a, Rank[a]+=Rank[b],a;
    else
        return pre[a]=b, Rank[b]+=Rank[a],b;
}

}
