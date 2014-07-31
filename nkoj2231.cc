//nkoj 2231
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
#include <queue>
#include <bitset>
#include <set>

using namespace std;


typedef map<long long int, int> ME;

int main()
{
    int N;
    scanf(" %d", &N);
    int sca,scb,w,a,b;
    vector<vector<int> > V(N+1); //V is adjacent list, 1 indexed, 0 reserved.
    ME E;
    for(int i=0; i<N-1; i++)
    {
        scanf(" %d %d %d",&sca,&scb, &w);
        a=min(sca,scb);
        b=max(sca,scb);
        // push to adjacent list.
        V[a].push_back(b);
        V[b].push_back(a);
        long long int llia = a;
        long long int llib = b;
        // record edge weight.
        E[(llia<<32)|b] = w;
        E[(llib<<32)|a] = w;
    }

    // bfs to build the tree.
    // initialize;
    V[0].insert(V[0].begin(), N+1, 0); //recond each node's parent.
    V[0][1]=1; // first node is the top node. self loop
    vector<int> dis(N+1,0); // distance from top node to here.
    queue<int> not_yet; // bfs queue.
    not_yet.push(1);
    while(!not_yet.empty())
    {
        int a=not_yet.front();
        for(vector<int>::iterator it=V[a].begin(); it!=V[a].end(); it++)
        {
            if(V[0][*it]==0) // not been visited yet.
            {
                V[0][*it]=a;//set parent;
                not_yet.push(*it);
                dis[*it] = dis[a]+E[(((long long)a)<<32)|(*it)];
            }
        }
        not_yet.pop();
    }
#ifndef ONLINE_JUDGE
    // test the tree we build.
    for(int i=1; i<=N; i++)
    {
        cout<<i<<" => "<<V[0][i]<<endl;
    }
    // test the distance.
    for(int i=1; i<=N; i++)
    {
        cout<<"dis "<<i<<" => "<<dis[i]<<endl;
    }
#endif
    int oversum=0;
    int maxreduce=0;
    set<int>spii; //must go-through points.
    int required_points;
    scanf(" %d",&required_points);
    for(int i=0; i<required_points; i++)
    {
        scanf(" %d", &sca);
        for(int node=sca; node!=1; node=V[0][node])
            spii.insert(node);
        maxreduce=max(maxreduce,dis[sca]);
    }
    for(set<int>::iterator it=spii.begin(); it!=spii.end(); it++)
    {
        oversum+=E[(((long long)(*it))<<32)|(V[0][*it])];
    }
#ifndef ONLINE_JUDGE
    printf("oversum: %d\nmaxredd: %d\n", oversum, maxreduce);
#endif
    printf("%d\n", 2*oversum-maxreduce);
    return 0;
}
