#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cassert>
#include <list>
#include <iomanip>
#include <math.h>
#include <deque>
#include <utility>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <climits>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <sstream>

using namespace std;

typedef unsigned int ui;
typedef unsigned long long ull;
typedef long long ll;


#define QQRR

template <typename T> struct matrix{
    const static int maxn = 60;
    int row, col;
    T mat[maxn][maxn];
#ifdef QQRR
    long double A[maxn][maxn];
    long double Q[maxn][maxn];
    long double R[maxn][maxn];
    const int NUM=15; //QR分解次数
#endif

    matrix(int r = 0, int c = 0){
        row = r; col = c;
        for(int i = 0; i < row; i++) for(int j = 0; j < col; j++) mat[i][j] = 0;
    }
    const T * operator[] (int i) const {
        return mat[i];
    }
    T * operator[] (int i) {
        return mat[i];
    }
    bool makeEye(){
        if(row != col) return 0;
        for(int i = 0; i < row; i++) for(int j = 0; j < col; j++) mat[i][j] = bool (i == j);
        return 1;
    }
    matrix operator * (const matrix& b) const{
        int i, j, k;
        matrix <T> c(row, b.col);
        memset(c.mat, 0, sizeof(c.mat));
        for (i = 0; i < c.row; i++) for (k = 0; k < col; k++)
            if(mat[i][k])
                for (j = 0; j < c.col; j++){
                    c.mat[i][j] += mat[i][k] * b.mat[k][j];
                }
        return c;
    }
    matrix operator + (const matrix& b) const{
        matrix <T> c(max1(row, b.row), max1(col, b.col));
        for(int i = 0; i < c.row; i++) for(int j = 0; j < c.col; j++){
            T a = 0; if(i < row && j < col) a = mat[i][j];
            T b1 = 0; if(i < b.row && j < b.col) b1 = b.mat[i][j];
            c.mat[i][j] = a + b1;
        }
        return c;
    }
    matrix operator - (const matrix& b) const{
        matrix <T> c(max1(row, b.row), max1(col, b.col));
        for(int i = 0; i < c.row; i++) for(int j = 0; j < c.col; j++){
            T a = 0; if(i < row && j < col) a = mat[i][j];
            T b1 = 0; if(i < b.row && j < b.col) b1 = b.mat[i][j];
            c.mat[i][j] = a - b1;
        }
        return c;
    }
    inline void operator = (const matrix & b){
        memcpy(mat, b.mat, sizeof(mat));
        col = b.col;  row = b.row;
    }
    matrix pow(long long n){
        matrix <T> ans(row, col), temp = *this;

        ans.makeEye();
        while(n){
            if(n & 1) ans = ans * temp;
            temp = temp * temp;
            n >>= 1;
        }
        return ans;
    }
    matrix addpow(long long n) {// calculate 1 + m + m ^ 2 + ... + m ^ n
        n++;
        matrix <T> ans(row, col), temp = *this, temp1(row, col), ans1(row, col);

        ans.makeEye(); temp1.makeEye();
        while(n){
            if(n & 1){
                ans1 = ans1 + ans * temp1;
                temp1 = temp * temp1;
            }
            ans = ans + ans * temp;
            temp = temp * temp;
            n >>= 1;
        }
        return ans1;
    }
    int inv(){
        int i, j, k, is[maxn], js[maxn];
        double t1;

        if (row != col) return 0;
        for(k = 0; k < row; k++){
            for(t1 = 0,i = k; i < row; i++) for(j = k; j < row; j++)
                if(fabs(mat[i][j]) > t1)
                    t1=fabs(mat[is[k] = i][js[k] = j]);
            if (fabs(t1 - 0) < 1e-9) return 0;
            if (is[k] != k) for(j = 0; j < row; j++)
                t1 = mat[k][j], mat[k][j] = mat[is[k]][j], mat[is[k]][j] = t1;
            if (js[k] != k) for (i = 0; i < row; i++)
                t1 = mat[i][k], mat[i][k] = mat[i][js[k]], mat[i][js[k]] = t1;
            mat[k][k] = 1 / mat[k][k];
            for(j = 0; j < row; j++) if (j != k)
                mat[k][j] *= mat[k][k];
            for (i = 0; i < row; i++)    if (i != k)
                for (j = 0; j < row; j++) if (j != k)
                    mat[i][j] -= mat[i][k] * mat[k][j];
            for (i = 0;i < row; i++) if (i != k)
                mat[i][k] *= -mat[k][k];
        }
        for (k = row-1; k >= 0; k--){
            for (j = 0; j < row; j++) if (js[k] != k)
                    t1 = mat[k][j], mat[k][j] = mat[js[k]][j], mat[js[k]][j]=t1;
            for (i = 0; i < row; i++) if (is[k] != k)
                t1 = mat[i][k], mat[i][k] = mat[i][is[k]], mat[i][is[k]] = t1;
        }
        return 1;
    }
    double det(){
        int i, j, k, sign = 0;
        double b[maxn][maxn], ret = 1, t1;

        if (row != col) return 0;
        for (i = 0; i < row; i++) for (j = 0; j < col; j++)
            b[i][j] = mat[i][j];
        for (i = 0; i < row; i++){
            if (fabs(b[i][i] - 0) < 1e-9){
                for (j = i + 1; j < row; j++)
                    if (fabs(b[j][i] - 0) > 1e-9) break;
                    if (j == row) return 0;
                    for (k = i; k < row; k++)
                        t1 = b[i][k], b[i][k] = b[j][k], b[j][k] = t1;
                    sign++;
            }
            ret *= b[i][i];
            for (k = i + 1; k < row; k++) b[i][k] /= b[i][i];
            for (j = i + 1; j < row; j++) for (k = i + 1; k < row; k++)
                b[j][k] -= b[j][i] * b[i][k];
        }
        if (sign & 1) ret = -ret;
        return ret;
    }

    void print()
    {
        for(int i=0;i<row;i++,cout<<'\n')
            for(int j=0;j<col;j++)
                cout<<mat[i][j]<<'\t';
    }

#ifdef QQRR
    void QR()
    {
        int N=col;
        int i,j,k,m;
        long double temp;
        long double a[maxn],b[maxn];
        for(j=0;j<N;j++)
        {
            for(i=0;i<N;i++)
            {
                a[i]=A[i][j];
                b[i]=A[i][j];
            }
            for(k=0;k<j;k++)
            {
                R[k][j]=0;
                for(m=0;m<N;m++)
                    R[k][j]+=a[m]*Q[m][k];
                for(m=0;m<N;m++)
                    b[m]-=R[k][j]*Q[m][k];
            }
            temp=0;
            for(i=0;i<N;i++)
                temp+=b[i]*b[i];
            R[j][j]=sqrt(temp);
            for(i=0;i<N;i++)
                Q[i][j]=b[i]/sqrt(temp);
        }
    }
    void Multiplicate()
    {
        int N=col;
        int i,j,k;
        long double temp;
        for(i=0;i<N;i++)
            for(j=0;j<N;j++)
            {
                temp=0;
                for(k=0;k<N;k++)
                    temp+=R[i][k]*Q[k][j];
                A[i][j]=temp;
            }
    }
    void doQR()
    {

        for(int i=0;i<row;i++)
            for(int j=0;j<col;j++)
                A[i][j]=mat[i][j];


        for(int i=1;i<=NUM;i++)
        {
            QR();
            Multiplicate();
        }
    }
#endif

};


