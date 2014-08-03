namespace DSET {

const int MAXN = ...;
#error please specifi MAXN;
int pre[MAXN],Rank[MAXN];
int degree;
// default is 1-indexed
void INIT(int n) /* 初始化函数 */
{
    degree=n;
    REP_1(i,n) pre[i]=i, Rank[i]=1;
}

int FIND(int x)
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

inline int TEST(int x,int y)
{
    return FIND(x)==FIND(y);
}
void UNION(int a,int b)
{
    a=FIND(a);
    b=FIND(b);
    if(a==b) return;
    if(Rank[a]>=Rank[b])
        pre[b]=a, Rank[a]+=Rank[b];
    else
        pre[a]=b, Rank[b]+=Rank[a];
    degree--;
}

}
