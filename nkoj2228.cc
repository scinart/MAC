//nkoj2228
#include <iostream>
#include <cstdio>
#include <sstream>
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
// #define MYDBG for(auto a = vi.begin(); a!=vi.end(); a++) { cout<<"("<<a->first<<" "<<a->second<<")"; } cout<<endl
#define MYDBG do{}while(0)

typedef pair<int,int> pii;

bool piif(const pii& a, const pii& b)
{
    return a.first<b.first;
}

bool piis(const pii& a, const pii& b)
{
    return a.second<b.second;
}

int main()
{
    string s;
    while(getline(cin, s))
    {
        stringstream ss;
        //cin.get();
        ss<<s;
        if(s.empty())
            continue;
        vector<pii> vi;
        int a,i=0;
        while(ss>>a)
        {
            i++;
            vi.push_back(pii(a,i));
        }
        MYDBG;
        sort(vi.begin(), vi.end(), piif);
        MYDBG;
        for(int i=0; i < vi.size(); i++)
        {
            vi[i].first = i;
        }
        MYDBG;
        sort(vi.begin(), vi.end(), piis);
        MYDBG;

        //cout<<endl;
        map<int, int> mii;
        for(vector<pii>::iterator i=vi.begin(); i!=vi.end(); i++)
        {
            if(mii.find(i->first-1)!=mii.end())
            {
                pii a(i->first, mii[i->first-1]+1);
                mii.erase(i->first-1);
                mii.insert(a);
            }
            else
            {
                mii[i->first]=1;
            }
        }
        int max=0;
        for(map<int,int>::iterator i=mii.begin(); i!=mii.end(); i++)
        {
            //cout<<i->first<<" "<<i->second<<endl;
            max=i->second>max?i->second:max;
        }
        cout<<vi.size()-max;
        cout<<endl;
    }
}
