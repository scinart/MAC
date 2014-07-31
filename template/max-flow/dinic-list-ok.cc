#include <vector>
#include <queue>
using namespace std;
const int MAXN = 20;
const int INF = 0x3f3f3f3f;
struct edge { int a, b, cap, flow; };

// 邻接链表 0-indexed.
// 重边不用管
// d 和 ptr 不用memset.
// 每次使用前把e和g清零

int _N, _S, _T, _D[MAXN], _PTR[MAXN];
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
    q.push(_S);
    memset (_D, -1, _N * sizeof _D[0]);
    _D[_S] = 0;
    while (!q.empty() && _D[_T] == -1) {
        int v=q.front();q.pop();
        for (size_t i=0; i<g[v].size(); ++i) {
            int id = g[v][i], to = e[id].b;
            if (_D[to] == -1 && e[id].flow < e[id].cap) {
                q.push(to);
                _D[to] = _D[v] + 1; } } }
    return _D[_T] != -1;
}

int dfs (int v, int flow) {
    if (!flow)  return 0;
    if (v == _T)  return flow;
    for (; _PTR[v]<(int)g[v].size(); ++_PTR[v]) {
        int id = g[v][_PTR[v]],
            to = e[id].b;
        if (_D[to] != _D[v] + 1) continue;
        int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id^1].flow -= pushed;
            return pushed; } }
    return 0;
}

int dinic() {
    int flow = 0;
    while(bfs()){
        memset (_PTR, 0, _N * sizeof _PTR[0]);
        int pushed = 0;
        while ((pushed = dfs (_S, INF)))
            flow += pushed; }
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
        _S=0;
        _T=n-1;
        cout<<"Case "<<cc<<": "<<dinic()<<'\n';
    }
}


