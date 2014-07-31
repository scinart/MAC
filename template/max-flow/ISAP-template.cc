#include <cstdio>
#include <memory>
#include <cstring>
#include <iostream>
using namespace std;


// 邻接链表
// 1-or-0-indexed;
// 不能有自环！！！

const int maxnode = 1024;
int dist[maxnode];
int numbs[maxnode];

#ifdef INFINITY
#undef INFINITY
#endif
template <typename T>
struct edge{
    const static T ZERO;
    const static T EPS;
    const static T INFINITY;
    int ver;  // vertex
    T cap;  // capacity
    T flow;  // current flow in this arc
    edge *next; // next arc
    edge *rev; // reverse arc
    edge(){}
    edge(int Vertex, T Capacity, edge *Next)
        :ver(Vertex), cap(Capacity), flow(ZERO), next(Next), rev((edge*)NULL){}
    void* operator new(size_t, void *p){
        return p;
    }
};

template <typename T>
class Network{
public:
    edge<T>*Net[maxnode];
    edge<T>* buffer;
    edge<T>* data;
    int src,des,n;
    Network(int _n,int _m):n(_n)
    {
        for(int i=0; i<maxnode; i++) Net[i]=NULL;
        buffer = new edge<T>[2*_m];
        data = buffer;
    }
    ~Network()
    {
        delete[] buffer;
    }
    void add_edge(int u,int v,T w)
    {
        Net[u] = new((void*) data++) edge<T>(v, w, Net[u]);
        Net[v] = new((void*) data++) edge<T>(u, edge<T>::ZERO, Net[v]);
        Net[u]->rev = Net[v];
        Net[v]->rev = Net[u];
    }
    void add_bidirectional_edge(int u,int v,T w)
    {
        Net[u] = new((void*) data++) edge<T>(v, w, Net[u]);
        Net[v] = new((void*) data++) edge<T>(u, w, Net[v]);
        Net[u]->rev = Net[v];
        Net[v]->rev = Net[u];
    }

    void reset()
    {
        for(int i=0; i<maxnode;i++)
        {
            edge<T>* this_ = Net[i];
            while(this_)
            {
                this_->cap += this_->flow;
                this_->flow = edge<T>::ZERO;
                this_ = this_->next;
            }
        }
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
            for(edge<T> *e = Net[v]; e; e = e->next){
                if(e->rev->cap <= edge<T>::EPS || dist[e->ver] < maxnode)continue;
                dist[e->ver] = dist[v] + 1;
                ++numbs[dist[e->ver]];
                Q[tail++] = e->ver;
            }
        }
    }

    T maxflow(int s, int t){
        src = s;
        des = t;
        rev_BFS();
        int u;
        T totalflow = edge<T>::ZERO;
        edge<T> *CurEdge[maxnode], *revpath[maxnode];
        for(int i=0; i<=n; ++i)CurEdge[i] = Net[i];
        u = src;
        while(dist[src] < n){
            if(u == des){  // find an augmenting path
                T augflow = edge<T>::INFINITY;
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

            edge<T> *e;
            for(e = CurEdge[u]; e; e = e->next)
                if(e->cap > edge<T>::EPS && dist[u] == dist[e->ver] + 1)break;
            if(e){  // find an admissible arc, then Advance
                CurEdge[u] = e;
                revpath[e->ver] = e->rev;
                u = e->ver;
            } else {  // no admissible arc, then relabel this vertex
                if(0 == (--numbs[dist[u]]))break;  // GAP cut, Important!
                CurEdge[u] = Net[u];
                int mindist = n;
                for(edge<T> *te = Net[u]; te; te = te->next)
                    if(te->cap > edge<T>::EPS)mindist = min(mindist, dist[te->ver]);
                dist[u] = mindist + 1;
                ++numbs[dist[u]];
                if(u != src)
                    u = revpath[u]->ver;  // Backtrack
            }
        }
        return totalflow;
    }
    void dfs(set<int>& visit, int node)
    {
        visit.insert(node);
        edge<T>* e = Net[node];
        for(;e;e=e->next)
        {
            if(e->cap > edge<T>::EPS && visit.find(e->ver)==visit.end())
            {
                dfs(visit,e->ver);
            }
        }
    }
    set<pair<int,int> > Mincut()
    {
        set<pair<int,int> > ans;
        //dfs
        set<int> dfs_set;
        dfs(dfs_set, src);
        EACH(it,dfs_set)
        {
            for(edge<T>* e=Net[*it]; e; e=e->next)
            {
                if(dfs_set.find(e->ver) == dfs_set.end())
                {
                    ans.insert(pair<int,int> (*it,e->ver));
                }
            }
        }
        return ans;
    }
};

template<>
const int edge<int>::ZERO(0);
template<>
const int edge<int>::EPS(0);
template<>
const int edge<int>::INFINITY(0x3f3f3f3f);

template<>
const double edge<double>::ZERO(0);
template<>
const double edge<double>::EPS(1e-8);
template<>
const double edge<double>::INFINITY(1e10);

int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif

    int n,m, u, v;
    double w;
    cin>>n>>m;
    {
        Network<double> net(n+1,m);
        for(int i=0; i<m; i++)
        {
            cin>>u>>v>>w;
            net.add_edge(u,v,w);
        }
        cout<<net.maxflow(1,n)<<'\n';
    }
    return 0;
}

