#include<stdio.h>
#define R(i,n)for(i=0;i<n;++i)
#define K(a,b){if((b)>a)a=(b);}
int M[110][110],A[110][110];
int main(){int n,i,j;scanf("%d",&n);R(i,n)R(j,i+1)scanf("%d",&M[i][j]);A[0][0]=M[0][0];R(i,n-1)R(j,i+1){K(A[i+1][j],A[i][j]+M[i+1][j]);K(A[i+1][j+1],A[i][j]+M[i+1][j+1]);}int X=0;R(i,n)K(X,A[n-1][i]);printf("%d\n",X);return 0;}
