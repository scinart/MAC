//nkoj 2169
//#include <iostream>
//#include <cstdio>
 //#include <climits>
 //#include <algorithm>
 //#include <sstream>
 //#include <vector>
 //#include <map>
 //#include <set>
 //#include <deque>
 //#include <string>
 //#include <cstddef>
#include <stdio.h>
//using namespace std;

int main()
{
    freopen("nkoj2169.in", "r", stdin);
    short T;
    scanf("%hi", &T);

    long long a,b;
    while(T--)
    {
        scanf("%lld %lld",&a,&b);
        printf("%lld\n", ((a+b)*(b-a+1)/2)%10);
    }
    return 0;
}
