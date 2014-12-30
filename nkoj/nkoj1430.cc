//nkoj1430.cc
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <cstring>
#include <list>
#include <map>
#include <deque>
#include <cstddef>
using namespace std;

//input N
//output fib(N)%10000

#define M 10000
class CC
{
public:
    int a11,a12,a21,a22;
    CC(){}
    CC(int a,int b,int c,int d):a11(a),a12(b),a21(c),a22(d){}
    const CC operator*(const CC& rhs)const
    {
        CC res;
        res.a11 = (a11*rhs.a11 + a12*rhs.a21)%M;
        res.a12 = (a11*rhs.a12 + a12*rhs.a22)%M;
        res.a21 = (a21*rhs.a11 + a22*rhs.a21)%M;
        res.a22 = (a21*rhs.a12 + a22*rhs.a22)%M;
        return res;
    }
};

const CC f(const CC& c, int pow)
{
    if(pow==0)
    {
        CC res;
        res.a11=1;
        res.a12=0;
        res.a21=0;
        res.a22=1;
        return res;
    }
    else if (pow%2==0)
    {
        return f(c*c, pow/2);
    }
    else return c*f(c,pow-1);
}

int main()
{
    int N;
    while(true)
    {
        scanf(" %d", &N);
        if (N==-1)
            break;
        CC bbb(1,1,1,0);
        CC res = f(bbb,N);
        printf("%d\n",res.a12);
    }
    return 0;
}
