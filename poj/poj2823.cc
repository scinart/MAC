//poj 2823
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
An array of size n ≤ 10^6 is given to you.
There is a sliding window of size k which is moving from the very left of the array to the very right.
You can only see the k numbers in the window.
Each time the sliding window moves rightwards by one position.
Following is an example:

The array is [1 3 -1 -3 5 3 6 7], and k is 3.

Window position             Minimum value Maximum value
[1  3  -1] -3  5  3  6  7  -1             3
 1 [3  -1  -3] 5  3  6  7  -3             3
 1  3 [-1  -3  5] 3  6  7  -3             5
 1  3  -1 [-3  5  3] 6  7  -3             5
 1  3  -1  -3 [5  3  6] 7   3             6
 1  3  -1  -3  5 [3  6  7]  3             7

Sample Input

8 3
1 3 -1 -3 5 3 6 7

Sample Output

-1 -3 -3 -3 3 3
3 3 5 5 6 7

*/
stringstream smax;
stringstream smin;

deque<int> lmax; //[1 3 5]
deque<int> lmin; //[1 -1 -5]

void fmaxmin()
{//output max and min of si.
    smin<<(lmin.back())<<" ";
    smax<<(lmax.back())<<" ";
}
int main()
{

    freopen("poj2823.in", "r", stdin);
    int length, wd;
    scanf("%d %d", &length, &wd);
    int lengthbackup = length;
    map<int,int> si;
    int * arr = new int[length];
    while(length--)
    {
        scanf("%d" , &arr[lengthbackup-length-1]);
    }
    for(int i=0; i<wd;i++)
    {
        while(!lmax.empty() && arr[i]>(lmax.front()))
        {
            // if newly added is larger than what is smallest.
            lmax.pop_front();
            // pop that smallest.
        }
        while(!lmin.empty() && arr[i]<(lmin.front()))
            lmin.pop_front();
        lmax.push_front(arr[i]);
        lmin.push_front(arr[i]);
    }
    fmaxmin();
    for(int i=wd; i<lengthbackup; i++)
    {
        if (arr[i-wd] == lmax.back())
        {
            lmax.pop_back();
            // if current max is out if window.
            // pop it.
        }
        if (arr[i-wd] == lmin.back())
            lmin.pop_back();
        while(!lmax.empty() && arr[i]>(lmax.front()))
            lmax.pop_front();
        while(!lmin.empty() && arr[i]<(lmin.front()))
            lmin.pop_front();
        lmax.push_front(arr[i]);
        lmin.push_front(arr[i]);
        fmaxmin();
    }
    cout<<smin.str()<<"\n"<<smax.str()<<endl;
}
