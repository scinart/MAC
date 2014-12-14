//nkoj 2229
#include <iostream>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <climits>
#include <vector>
#include <cstring>
#include <list>
#include <map>
#include <deque>

using namespace std;

#define U people_to_feed

bool gt(const int& a, const int& b)
{
    return a>b;
}
int main()
{
    int N,M,Q; // N<=10000, M<=1 000 000 000,0<=Q<100
    cin>>N>>M>>Q;
    vector<int> vi;
    int lastop=0;
    for(int outi=0; outi<N; outi++)
    {
        int people_there = outi; //not including current people.
        int people_to_feed = floor(Q*(people_there+1)/100.0); //so as to get strictly greater then Q%.
        int i=0,sum=0;

#ifndef ONLINE_JUDGE
        printf("PT: %d, PTF %d\n", people_there, people_to_feed);
#endif

        if(!U || U<people_there) //if I'm the first one or I could possibly feed some people there.
        {
            int ri;
            for(ri=people_there-1, i=0; i<U; i++,ri--)
            {
                sum+=vi[ri]; //feed costs.
            }
            if(M>=sum+U) //affordable.
            {
                vector<int> nvi;
                nvi.reserve(people_there+1);
                for(int i=0; i<people_there; i++)
                {
                    if(i<=ri)
                        nvi.push_back(0);
                    else
                        nvi.push_back(vi[i]+1);
                }
                nvi.push_back(M-sum-U);
                lastop=M-sum-U;
                sort(nvi.begin(), nvi.end(), gt);
                vi.swap(nvi);
            }
            else //die
            {
                vi.push_back(0);
                lastop=-1;
            }
        }
        else //die
        {
            vi.push_back(0);
            lastop=-1;
        }
#ifndef ONLINE_JUDGE
        for_each (vi.begin(), vi.end(), [](const int& a){cout<<a<<" ";});
        cout<<endl;
#endif
    }
    cout<<lastop<<endl;
    return 0;
}
