#include <stdio.h>
#include <math.h>

int main()
{
    unsigned long long int M[10][10][10];
    int V[10][10][10];
    int n;
    while(scanf("%d",&n) != EOF)
    {
        int i,j,k,I,J,K;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                for (k=0; k<n; k++)
                {
                    M[i][j][k]=0;
                    scanf(" %d",&V[i][j][k]);
                }

            }
        }
        M[0][0][0]=1;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                for (k=0; k<n; k++)
                {
                    for(I=0;I<=V[i][j][k] && I+i<n;I++)
                    {
                        for(J=0;J<=V[i][j][k] && J+j<n;J++)
                        {
                            for (K=0; K<=V[i][j][k] && K+k<n; K++)
                            {
                                if(I||J||K)
                                    M[I+i][J+j][K+k] += M[i][j][k];
                            }

                        }
                    }

                }

            }
        }
/* for(int i=0;i<n;i++)
        // {
        //     for(int j=0;j<n;j++)
        //     {
        //         for (int k=0; k<n; k++)
        //         {
        //             printf("%llu\t",M[i][j][k]);
        //         }
        //         printf("\n");
        //     }
        //     printf("\n");
        // }
        */
        printf("%llu\n",M[n-1][n-1][n-1]%1000000007);

    }
    return 0;
}
