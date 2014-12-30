#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

typedef unsigned int ui;
typedef unsigned long long ull;
typedef long long ll;
template<typename T>
T mymod(T N, T M)
{
    // return canonical N%M
    if((M>0 && N>0) || (M<0 && N<0))
        return N%M;
    else if ((M<0&&N>0) || (M>0&&N<0))
        return N%M+((N%M)?M:0);
    else
        return 0;
}
template <typename T> struct matrix{
    int row, col;
    vector<vector<T> > mat;
    matrix(int r = 0, int c = 0):row(r),col(c),mat(r,vector<T>(c,0)){}
    void makeEye(){for(int i=0;i<row;i++)for(int j=0;j<col;j++)mat[i][j]=bool(i==j);}
    matrix operator * (const matrix& b) const{
        int i, j, k;
        matrix <T> c(row, b.col);
        for (i = 0; i < c.row; i++)
            for (k = 0; k < col; k++)
                for (j = 0; j < c.col; j++)
                    c.mat[i][j] += mat[i][k] * b.mat[k][j];
        return c;
    }
    matrix operator+(const matrix& b) const{
        matrix ret(*this);
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                ret.mat[i][j] += b.mat[i][j];
        return ret;
    }
    matrix operator-(const matrix& b) const{
        matrix ret(*this);
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
                ret.mat[i][j] -= b.mat[i][j];
        return ret;
    }
    inline void operator = (const matrix & b){
        row=b.row; col=b.col; mat=b.mat;
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
    matrix& multi_(const matrix& b, long long mod)
    {
        int i, j, k;
        matrix <T> c(row, b.col);
        for (i = 0; i < c.row; i++)
            for (k = 0; k < col; k++)
                for (j = 0; j < c.col; j++)
                {
                    c.mat[i][j] += (mat[i][k] * b.mat[k][j]) % mod;
                    c.mat[i][j] %= mod;
                }
        *this=c;
        return *this;
    }
    matrix powmod(long long n,long long mod)const
    {
        matrix <T> ans(row, col), temp = *this;
        REP(i,row)REP(j,col)
            temp.mat[i][j]=mymod(temp.mat[i][j],mod);
        if(n==1)return temp;
        if(n & 1) ans = temp;
        else ans.makeEye();
        temp = powmod(n>>1,mod);
        temp.multi_(temp,mod);
        return ans.multi_(temp,mod);
    }
    matrix addpow(long long n) {// calculate 1 + m + m ^ 2 + ... + m ^ n
        n++;
        matrix <T> ans(row, col), temp = *this, temp1(row, col), ans1(row, col);
        ans.makeEye();
        temp1.makeEye();
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
    void print() {
        for(int i=0;i<row;i++,cout<<'\n')
            for(int j=0;j<col;j++)
                cout<<mat[i][j]<<'\t';
    }

};


int main()
{
    return 0;
}
