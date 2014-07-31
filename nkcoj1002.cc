//problem nkcoj 1002
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <sstream>
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

#define MAXN 63

// topological sorting.
int main()
{
/* 入
出 [ [bitset1] [bitset2] [bitset3] ... [bitsetn] ]
   [ [bitset1] [bitset2] [bitset3] ... [bitsetn] ]
   [ [bitset1] [bitset2] [bitset3] ... [bitsetn] ]
   [ [bitset1] [bitset2] [bitset3] ... [bitsetn] ]
   [ [bitset1] [bitset2] [bitset3] ... [bitsetn] ]
   [ [bitset1] [bitset2] [bitset3] ... [bitsetn] ]
   [ [bitset1] [bitset2] [bitset3] ... [bitsetn] ]
   [ [bitset1] [bitset2] [bitset3] ... [bitsetn] ]

*/
    freopen("nkcoj1002.in", "r", stdin);
    int nodes, edges; // 1≤nodes≤50
    cin>>nodes>>edges;

    vector<int> yes;
    vector<int> no;

    typedef bitset<MAXN+1> BS;

    vector<BS> vbs(nodes);
    while (edges--)
    {
        int a,b;
        cin>>a>>b;
        a--;b--;
        vbs[b].set(MAXN-a, 1);
    }

    bool progressing = true;
    while(progressing)
    {
        progressing = false;
        for(int i=0; i<vbs.size(); i++)
        {
            if (!(vbs[i].any()))
            {
                progressing = true;
                yes.push_back(i);
                vbs[i].set(0,1);
                for(int j=0; j<vbs.size(); j++)
                {
                    vbs[j].set(MAXN-i,0);
                }
            }
        }
    }
    if (yes.size() == vbs.size())
    {
        cout<<"YES\n";
        for(vector<int>::iterator it = yes.begin(); it+1 != yes.end(); it++)
        {
            cout<<(*it + 1)<<",";
        }
        cout<<(*(yes.rbegin()) + 1)<<endl;
    }
    else
    {// find a circle in the residual.
        int anode;
        for(int i=0; i<vbs.size(); i++)
        {
            if ((! vbs[i].test(0)) && vbs[i].any())
            {
                anode = i;
                break;
            }
        }
        bool theloop = false;
        do
        {
            for(int i=0; i<no.size(); i++)
            {
                if (no[i] == anode)
                {
                    cout<<"NO\n";
                    cout<<no[i]+1<<",";
                    for (int j=no.size()-1; j>i; j--)
                    {
                        cout<<no[j]+1<<",";
                    }
                    cout<<no[i]+1<<endl;
                    theloop = true;
                    break;
                }
            }
            no.push_back(anode);
            for(int i=0; i<vbs.size(); i++)
            {
                if (vbs[anode].test(MAXN-i))
                {
                    anode = i;
                    break;
                }
            }

        }
        while(!theloop);
    }

}
