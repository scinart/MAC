#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

typedef double T;

const int n = 231;
const int m = 1;

double a[n][n];
double b[n][m];
double tmp[n];
int irow[n],icol[n],ipiv[n];
T GaussJordan()
{
    for(int i=0; i<n; i++)
    {
        irow[i]=0;
        icol[i]=0;
        ipiv[i]=0;
    }
    T det = 1;

    for (int i = 0; i < n; i++) {
        int pj = -1, pk = -1;
        for (int j = 0; j < n; j++)
            if (!ipiv[j])
                for (int k = 0; k < n; k++)
                    if (!ipiv[k])
                        if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) { pj = j; pk = k; }
        ipiv[pk]++;

        if(pj!=pk)
            for(int i=0; i<n; i++)
            {
                tmp[i]=a[pj][i]; a[pj][i]=a[pk][i];a[pk][i]=tmp[i];
                tmp[i]=b[pj][i]; b[pj][i]=b[pk][i];b[pk][i]=tmp[i];
            }
        if (pj != pk) det *= -1;
        irow[i] = pj;
        icol[i] = pk;

        T c = 1.0 / a[pk][pk];
        det *= a[pk][pk];
        a[pk][pk] = 1.0;
        for (int p = 0; p < n; p++) a[pk][p] *= c;
        for (int p = 0; p < m; p++) b[pk][p] *= c;
        for (int p = 0; p < n; p++)
            if (p != pk) {
                c = a[p][pk];
                a[p][pk] = 0;
                for (int q = 0; q < n; q++) a[p][q] -= a[pk][q] * c;
                for (int q = 0; q < m; q++) b[p][q] -= b[pk][q] * c;
            }
    }

    for (int p = n-1; p >= 0; p--)
        if (irow[p] != icol[p]) {
            for (int k = 0; k < n; k++)
            {
                double ttmp=a[k][irow[p]];
                a[k][irow[p]] = a[k][icol[p]];
                a[k][icol[p]] = ttmp;
            }
        }

    return det;
}

int tb[21] = {1,3,6,10,15,21,28,36,45,55,66,78,91,105,120,136,153,171,190,210,231};
inline int ind(int x,int y){return tb[x]-(x-y)-1;}
int main()
{
    std::ios::sync_with_stdio(false);
    double p,q;
    while(cin>>p)
    {
        q=1-p;
        for(int i=0;i<n; i++)
            for(int j=0; j<m; j++)
                b[i][j]=1;
        for(int i=0;i<n;i++)
            for(int j=0; j<n;j++)
                a[i][j]=0;
        for(int i=0; i<=20; i++)
        {
            a[ind(20,i)][ind(20,i)] = 1;
            b[ind(20,i)][0] = 0;
        }

        a[ind(0,0)][ind(0,0)] = p;
        a[ind(0,0)][ind(1,0)] = -p;
        for(int i=1; i<20; i++)
        {
            a[ind(i,0)][ind(i,0)] = p;
            a[ind(i,0)][ind(i,1)] = -p;
        }
        for(int i=2; i<=19; i++)
        {
            a[ind(i,1)][ind(i,1)] = 1;
            a[ind(i,1)][ind(i,0)] = -q;
            a[ind(i,1)][ind(i,2)] = -p;
        }
        for(int i=3; i<=19; i++)
        {
            for(int j=2; j<=i-1; j++)
            {
                a[ind(i,j)][ind(i,j)] = 1;
                a[ind(i,j)][ind(i,j-2)] = -q;
                a[ind(i,j)][ind(i,j+1)] = -p;
            }
        }
        a[ind(1,1)][ind(1,1)] = 1;
        a[ind(1,1)][ind(1,0)] = -q;
        a[ind(1,1)][ind(2,1)] = -p;
        for(int i=2; i<=19; i++)
        {
            a[ind(i,i)][ind(i,i)] = 1;
            a[ind(i,i)][ind(i,i-2)] = -q;
            a[ind(i,i)][ind(i+1,i)] = -p;
        }


        GaussJordan();
        cout<<fixed<<setprecision(6)<<b[0][0]<<'\n';
    }
}
