//codeforces 408 B
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

using namespace std;


int main()
{

    int has[26];
    int want[26];
    for(int i=0; i<26; i++)
    {
        has[i]=want[i]=0;
    }
    string ss;
    cin>>ss;
    for(int i=0; i<ss.size(); i++)
    {
        has[ss[i]-'a']++;
    }
    cin>>ss;
    for(int i=0; i<ss.size(); i++)
    {
        want[ss[i]-'a']++;
    }
    int eend=0,sum=0;
    for(int i=0; i<26; i++)
    {// see if has color is enough.
        if(want[i] && !has[i])
        {
            cout<<"-1"<<endl;
            eend=1;
            break;
        }
        else
        {
            sum+=min(want[i], has[i]);
        }
    }
    if(eend)
    {

    }
    else
    {
        cout<<sum<<endl;
    }
    return 0;
}
