//problem 2212
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

typedef long long int lli;
int g(lli A, lli N, lli M)
{ // return A^N%M
	// pre-condition: A<M;
	if (N==1)
	{
		return A;
	}
	if(N%2)
	{ // N is odd
		return A*g(A, N-1, M)%M;
	}
	else
	{
		lli mid = g(A, N/2, M);
		return mid*mid%M;
	}
}

int f(lli A, lli N, lli M)
{ //return 1+A+A^2+...+A^N % M
	if (N==1)
	{
		return (1+A)%M;
	}
	if (N%2)
	{
		lli mid = f(A, N/2, M);
		return (mid*(1+g(A, N/2+1, M)))%M;
	}
	else
	{
		return (1+A*f(A, N-1, M))%M;
	}
}

int main()
{
	freopen("input","r",stdin);

	long long int A, N, M; //1 ~ 1000000000;

	//scanf("%hi", &n);
	while (scanf("%lld %lld %lld", &A, &N, &M) != EOF)
	{
		A%=M;
		int res = f(A,N,M);
		printf("%d\n", res);
	}
	return 0;
}
