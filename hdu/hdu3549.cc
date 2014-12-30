#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 20;
const int INF = 0x3f3f3f3f;

// 邻接链表 0-indexed.
// // 重边请????
// d 和 ptr 不用memset.
// 把e和g清零
struct edge {
    int a, b, cap, flow;
};

int n, s, t, d[MAXN], ptr[MAXN];
vector<edge> e;
vector<int> g[MAXN];

void add_edge (int a, int b, int cap) {
    edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    g[a].push_back ((int) e.size());
    e.push_back (e1);
    g[b].push_back ((int) e.size());
    e.push_back (e2);
}

bool bfs() {
    queue<int> q;
    q.push(s);
    memset (d, -1, n * sizeof d[0]);
    d[s] = 0;
    while (!q.empty() && d[t] == -1) {
        int v = q.front();q.pop();
        for (size_t i=0; i<g[v].size(); ++i) {
            int id = g[v][i],
                to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

int dfs (int v, int flow) {
    if (!flow)  return 0;
    if (v == t)  return flow;
    for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
        int id = g[v][ptr[v]],
            to = e[id].b;
        if (d[to] != d[v] + 1)  continue;
        int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id^1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic() {
    int flow = 0;
    while (bfs()) {
        memset (ptr, 0, n * sizeof ptr[0]);
        while (int pushed = dfs (s,INF))
            flow += pushed;
    }
    return flow;
}


int main()
{
    int cases;cin>>cases;
    for(int cc=1; cc<=cases; cc++)
    {
        e.clear();
        for(int i=0; i<MAXN; i++)
        {
            g[i].clear();
        }


        int m;
        cin>>n>>m;
        for(int i=0; i<m; i++)
        {
            int f,t,c;
            cin>>f>>t>>c;
            add_edge(f-1, t-1, c);
        }
        s=0;
        t=n-1;
        cout<<"Case "<<cc<<": "<<dinic()<<'\n';
    }
}

