//nkoj 2230
#include <iostream>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <climits>
#include <vector>
#include <map>
#include <deque>

using namespace std;
#define GOAL 10
int main()
{
    int N; //[10 65536]
    scanf(" %d",&N);
    vector<int> vi;
    vi.reserve(N);
    unsigned int sum=0;

    int sca;
    for(int i=0; i<N; i++)
    {
        scanf(" %d",&sca);
        vi.push_back(sca-2000);
    }

    vector<int> triD(N,0);

    for(int i=0; i<10; i++)
    {
        triD[0]+=vi[i];
    }
    if(triD[0]==GOAL)
        sum++;
    for(int i=1; i<=N-10; i++)
    {
        triD[i] = triD[i-1]-vi[i-1]+vi[i+9];
        if(triD[i]==GOAL)
            sum++;
    }
#ifndef ONLINE_JUDGE
        for_each(triD.begin(), triD.end(), [](const int& a){cout<<a<<"\t";});
        cout<<endl;
#endif
    for(int length=11; length<=N; length++) //length, a.k.a number of points
    {
        for(int start=0; start<=N-length; start++)
        {
            triD[start]+=vi[start+length-1];
            if(triD[start]==GOAL)
                sum++;
        }
#ifndef ONLINE_JUDGE
        for_each(triD.begin(), triD.end(), [](const int& a){cout<<a<<"\t";});
        cout<<endl;
#endif
    }
    printf("%u\n", sum);
    return 0;
}
