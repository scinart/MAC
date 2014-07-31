//nkoj 1008
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <cassert>
#include <vector>
#include <cstring>
#include <list>
#include <map>
#include <deque>
#include <bitset>


using namespace std;


typedef pair<int,int> pii;

bool piis(const pii& a, const pii& b)
{
    return a.second<b.second;
}

int main()
{
    int N,a,b;
    scanf("%d", &N);
    vector<pii> v;
    v.reserve(N);
    while(N--)
    {
        scanf(" %d %d", &a, &b);
        v.push_back(pii(min(a,b), max(a,b)));
    }
    sort(v.begin() ,v.end(), piis);
    int sum=0;
    int rbound = -19999;
    for(vector<pii>::iterator it = v.begin(); it!=v.end(); it++)
    {
        if(it->first>=rbound)
        {
            sum++;
            rbound = it->second;
        }
    }
    printf("%d\n", sum);
}
