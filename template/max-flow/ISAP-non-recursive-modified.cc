#include <cstdio>
#include <memory>
#include <cstring>
using namespace std;


// 邻接链表
// 1-or-0-indexed;
// 不能有自环！！！

const int maxnode = 1024;
const int infinity = 2100000000;
int dist[maxnode];
int numbs[maxnode];
struct edge{
    int ver;  // vertex
    int cap;  // capacity
    int flow;  // current flow in this arc
    edge *next; // next arc
    edge *rev; // reverse arc
    edge(){}
    edge(int Vertex, int Capacity, edge *Next)
        :ver(Vertex), cap(Capacity), flow(0), next(Next), rev((edge*)NULL){}
    void* operator new(size_t, void *p){
        return p;
    }
}*Net[maxnode];

class Network{
public:
    edge* buffer;
    edge* data;
    int src,des,n;
    Network(int _n,int _m):n(_n)
    {
        for(int i=0; i<maxnode; i++) Net[i]=NULL;
        buffer = new edge[2*_m];
        data = buffer;
    }
    ~Network()
    {
        delete[] buffer;
    }
    void add_edge(int u,int v,int w)
    {
        Net[u] = new((void*) data++) edge(v, w, Net[u]);
        Net[v] = new((void*) data++) edge(u, 0, Net[v]);
        Net[u]->rev = Net[v];
        Net[v]->rev = Net[u];
    }
    void rev_BFS()
    {
        int Q[maxnode], head = 0, tail = 0;
        for(int i=0; i<=n; ++i){
            dist[i] = maxnode;
            numbs[i] = 0;
        }
        Q[tail++] = des;
        dist[des] = 0;
        numbs[0] = 1;
        while(head != tail){
            int v = Q[head++];
            for(edge *e = Net[v]; e; e = e->next){
                if(e->rev->cap == 0 || dist[e->ver] < maxnode)continue;
                dist[e->ver] = dist[v] + 1;
                ++numbs[dist[e->ver]];
                Q[tail++] = e->ver;
            }
        }
    }

    int maxflow(int s, int t){
        src = s;
        des = t;
        rev_BFS();
        int u, totalflow = 0;
        edge *CurEdge[maxnode], *revpath[maxnode];
        for(int i=0; i<=n; ++i)CurEdge[i] = Net[i];
        u = src;
        while(dist[src] < n){
            if(u == des){  // find an augmenting path
                int augflow = infinity;
                for(int i = src; i != des; i = CurEdge[i]->ver)
                    augflow = min(augflow, CurEdge[i]->cap);
                for(int i = src; i != des; i = CurEdge[i]->ver){
                    CurEdge[i]->cap -= augflow;
                    CurEdge[i]->rev->cap += augflow;
                    CurEdge[i]->flow += augflow;
                    CurEdge[i]->rev->flow -= augflow;
                }
                totalflow += augflow;
                u = src;
            }

            edge *e;
            for(e = CurEdge[u]; e; e = e->next)
                if(e->cap > 0 && dist[u] == dist[e->ver] + 1)break;
            if(e){  // find an admissible arc, then Advance
                CurEdge[u] = e;
                revpath[e->ver] = e->rev;
                u = e->ver;
            } else {  // no admissible arc, then relabel this vertex
                if(0 == (--numbs[dist[u]]))break;  // GAP cut, Important!
                CurEdge[u] = Net[u];
                int mindist = n;
                for(edge *te = Net[u]; te; te = te->next)
                    if(te->cap > 0)mindist = min(mindist, dist[te->ver]);
                dist[u] = mindist + 1;
                ++numbs[dist[u]];
                if(u != src)
                    u = revpath[u]->ver;  // Backtrack
            }
        }
        return totalflow;
    }
};
int main()
{
    int n,m, u, v, w;
    while(scanf("%d%d", &m, &n) != EOF)
    {
        Network net(n,m);
        for(int i=0; i<m; i++)
        {
            scanf("%d %d %d", &u, &v, &w);
            net.add_edge(u,v,w);
        }
        printf("%d\n", net.maxflow(1,n));
    }
    return 0;
}

