//nkoj 2219
#include <iostream>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <string>
#include <cstddef>

using namespace std;


/*
QUESTION:
现有一长为n的整数列：d1, d2, d3, ......, dn。
求满足下列条件的最长子序列（子序列指连续的若干个数）的长度：
该子序列中最大值与最小值之差不超过k
*/

/*
ANSWER:

THIS ANSWER SHOULD BE O(N);

 */


deque<int> lmax; //[1 3 5]
deque<int> lmin; //[1 -1 -5]

int difmaxmin()
{//output max - min.
    return lmax.back()-lmin.back();
}


int main()
{
    freopen("nkoj2219.in", "r", stdin);
    int n,k, *arr;
    while(scanf("%d %d",&n,&k) != EOF)
    {
        lmax.clear();
        lmin.clear();
        arr = new int[n];
        for(int i=0; i<n; i++)
        {
            scanf("%d",&arr[i]);
        }

        int windowLength = 1;
        lmax.push_front(arr[0]);
        lmin.push_front(arr[0]);
        for(int endp=1; endp<n; endp++) //[endp-windowLength, endp)
        {
            while(!lmax.empty() && arr[endp]>(lmax.front()))
            {
                // if newly added is larger than what is smallest.
                lmax.pop_front();
                // pop that smallest.
            }
            while(!lmin.empty() && arr[endp]<(lmin.front()))
                lmin.pop_front();

            lmax.push_front(arr[endp]);
            lmin.push_front(arr[endp]);

            if(difmaxmin()<=k)
            {
                windowLength++;
            }
            else
            {
                if (arr[endp-windowLength] == lmax.back())
                {
                    lmax.pop_back();
                    // if current max is out if window.
                    // pop it.
                }
                if (arr[endp-windowLength] == lmin.back())
                {
                    lmin.pop_back();
                }
            }
        }
        printf("%d\n",windowLength);
        delete[] arr;
    }
}
