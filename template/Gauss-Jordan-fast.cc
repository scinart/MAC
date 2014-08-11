#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

typedef double T;

// Gauss-Jordan elimination with full pivoting.
//
// Uses:
//   (1) solving systems of linear equations (AX=B)
//   (2) inverting matrices (AX=I)
//   (3) computing determinants of square matrices
//
// Running time: O(n^3)
//
// INPUT:    _a[][] = an nxn matrix
//           _b[][] = an nxm matrix
//
// OUTPUT:   X      = an nxm matrix (stored in _b[][])
//           A^{-1} = an nxn matrix (stored in _a[][])
//           returns determinant of _a[][]

const int n = ...;
const int m = ...;

double _a[n][n];
double _b[n][m];
double _tmp[...]; //this should be max(n,m);
int _irow[n],_icol[n],_ipiv[n];
T GaussJordan()
{
    for(int i=0; i<n; i++)
    {
        _irow[i]=0;
        _icol[i]=0;
        _ipiv[i]=0;
    }
    T det = 1;

    for (int i = 0; i < n; i++) {
        int pj = -1, pk = -1;
        for (int j = 0; j < n; j++)
            if (!_ipiv[j])
                for (int k = 0; k < n; k++)
                    if (!_ipiv[k])
                        if (pj == -1 || fabs(_a[j][k]) > fabs(_a[pj][pk])) { pj = j; pk = k; }
        _ipiv[pk]++;

        if(pj!=pk)
        {
            for(int i=0; i<n; i++)
            {
                _tmp[i]=_a[pj][i]; _a[pj][i]=_a[pk][i];_a[pk][i]=_tmp[i];
            }
            for(int i=0; i<m; i++)
            {
                _tmp[i]=_b[pj][i]; _b[pj][i]=_b[pk][i];_b[pk][i]=_tmp[i];
            }
        }
        if (pj != pk) det *= -1;
        _irow[i] = pj;
        _icol[i] = pk;

        T c = 1.0 / _a[pk][pk];
        det *= _a[pk][pk];
        _a[pk][pk] = 1.0;
        for (int p = 0; p < n; p++) _a[pk][p] *= c;
        for (int p = 0; p < m; p++) _b[pk][p] *= c;
        for (int p = 0; p < n; p++)
            if (p != pk) {
                c = _a[p][pk];
                _a[p][pk] = 0;
                for (int q = 0; q < n; q++) _a[p][q] -= _a[pk][q] * c;
                for (int q = 0; q < m; q++) _b[p][q] -= _b[pk][q] * c;
            }
    }

    for (int p = n-1; p >= 0; p--)
        if (_irow[p] != _icol[p]) {
            for (int k = 0; k < n; k++)
            {
                double ttmp=_a[k][_irow[p]];
                _a[k][_irow[p]] = _a[k][_icol[p]];
                _a[k][_icol[p]] = ttmp;
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
                _b[i][j]=1;
        for(int i=0;i<n;i++)
            for(int j=0; j<n;j++)
                _a[i][j]=0;
        for(int i=0; i<=20; i++)
        {
            _a[ind(20,i)][ind(20,i)] = 1;
            _b[ind(20,i)][0] = 0;
        }

        _a[ind(0,0)][ind(0,0)] = p;
        _a[ind(0,0)][ind(1,0)] = -p;
        for(int i=1; i<20; i++)
        {
            _a[ind(i,0)][ind(i,0)] = p;
            _a[ind(i,0)][ind(i,1)] = -p;
        }
        for(int i=2; i<=19; i++)
        {
            _a[ind(i,1)][ind(i,1)] = 1;
            _a[ind(i,1)][ind(i,0)] = -q;
            _a[ind(i,1)][ind(i,2)] = -p;
        }
        for(int i=3; i<=19; i++)
        {
            for(int j=2; j<=i-1; j++)
            {
                _a[ind(i,j)][ind(i,j)] = 1;
                _a[ind(i,j)][ind(i,j-2)] = -q;
                _a[ind(i,j)][ind(i,j+1)] = -p;
            }
        }
        _a[ind(1,1)][ind(1,1)] = 1;
        _a[ind(1,1)][ind(1,0)] = -q;
        _a[ind(1,1)][ind(2,1)] = -p;
        for(int i=2; i<=19; i++)
        {
            _a[ind(i,i)][ind(i,i)] = 1;
            _a[ind(i,i)][ind(i,i-2)] = -q;
            _a[ind(i,i)][ind(i+1,i)] = -p;
        }


        GaussJordan();
        cout<<fixed<<setprecision(6)<<_b[0][0]<<'\n';
    }
}
