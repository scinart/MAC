int _d[N][30]; // 30>log(N)
void RMQ_Init(const vector<int>& A)
{
    int n=A.size();
    for (int i=0;i<n;i++) _d[i][0]=A[i];
    for (int j=1;(1<<j)<=n;j++)
        for (int i=0;i+(1<<j)-1<n;i++)
            _d[i][j]=min(_d[i][j-1],_d[i+(1<<(j-1))][j-1]);
}
void RMQ_Init(int A[], int size)
{
    int n=size;
    for (int i=0;i<n;i++) _d[i][0]=A[i];
    for (int j=1;(1<<j)<=n;j++)
        for (int i=0;i+(1<<j)-1<n;i++)
            _d[i][j]=min(_d[i][j-1],_d[i+(1<<(j-1))][j-1]);
}


int RMQ(int L,int R)
{
    int k=0;
    for (k=0;1<<(k+1)<=R-L+1;k++);
    return min(_d[L][k],_d[R-(1<<k)+1][k]);
}
