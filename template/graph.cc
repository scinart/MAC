#include <cstdio>
#include <cstring>
const int maxnode = 100010;

#ifdef TARJAN
int DFN[maxnode];
int LOW[maxnode];
bool instack[maxnode];
int Stap[maxnode];
int Belong[maxnode];
int Stop, Bcnt, Dindex;
#endif

struct edge{
    int ver;  // vertex
    int cap; //capacity or cost
    edge *next; // next arc
    edge *rev; // reverse arc
    edge(){}
    edge(int Vertex, int c, edge *Next)
        :ver(Vertex), cap(c), next(Next), rev((edge*)NULL){}
    void* operator new(size_t, void *p){
        return p;
    }
}*Net[maxnode];
#if __cplusplus < 201103L
enum Color {WHITE,GREY,BLACK};
#else
enum class Color {WHITE,GREY,BLACK};
#endif


struct node{
    int indegree;
    int outdegree;
    Color color;
#if __cplusplus < 201103L
    node():indegree(0),outdegree(0),color(WHITE){}
    void reset(){indegree=0;outdegree=0;color=WHITE;}
#else
    node():indegree(0),outdegree(0),color(Color::WHITE){}
    void reset(){indegree=0;outdegree=0;color=Color::WHITE;}
#endif

} Node[maxnode];

struct Graph{
#define EACH_EDGE(e,node) for(edge* e=node; e; e=e->next)
    edge* buffer;
    edge* data;
    int n;//n nodes.
    Graph(int _n,int _m):n(_n)
    {
        for(int i=0; i<maxnode; i++) Net[i]=NULL;
        for(int i=0; i<maxnode; i++) Node[i].reset();
        buffer = new edge[2*_m];
        data = buffer;
    }
    ~Graph() {
        delete[] buffer;
    }
    void add_edge(int u,int v, int c)
    {
        Net[u] = new((void*) data++) edge(v, c, Net[u]);
        Net[v] = new((void*) data++) edge(u, 0, Net[v]);
        Net[u]->rev = Net[v];
        Net[v]->rev = Net[u];
        Node[u].outdegree++;
        Node[v].indegree++;
    }
    void add_bidirectional_edge(int u,int v, int c)
    {
        Net[u] = new((void*) data++) edge(v, c, Net[u]);
        Net[v] = new((void*) data++) edge(u, c, Net[v]);
        Net[u]->rev = Net[v];
        Net[v]->rev = Net[u];
        Node[u].indegree++;
        Node[u].outdegree++;
        Node[v].indegree++;
        Node[v].outdegree++;
    }

    void dfs(int node)
    {
#if __cplusplus < 201103L
        Node[node].color = GREY;
#else
        Node[node].color = Color::GREY;
#endif
        edge* e = Net[node];
        for(;e;e=e->next)
        {
#if __cplusplus < 201103L
            if(e->cap && Node[e->ver].color == WHITE)
#else
            if(e->cap && Node[e->ver].color == Color::WHITE)
#endif
            {
                dfs(e->ver);
            }
        }
#if __cplusplus < 201103L
        Node[node].color = BLACK;
#else
        Node[node].color = Color::BLACK;
#endif

    }

#ifdef TARJAN
    void tarjan_aid(int i)
    {
        int j;
        DFN[i]=LOW[i]=++Dindex;
        instack[i]=true;
        Stap[++Stop]=i;
        EACH_EDGE(e, Net[i])
        {
            if(e->cap!=0)
            {
                j=e->ver;
                if (!DFN[j])
                {
                    tarjan_aid(j);
                    if (LOW[j]<LOW[i])
                        LOW[i]=LOW[j];
                }
                else if (instack[j] && DFN[j]<LOW[i])
                    LOW[i]=DFN[j];
            }
        }
        if (DFN[i]==LOW[i])
        {
            Bcnt++;
            do
            {
                j=Stap[Stop--];
                instack[j]=false;
                Belong[j]=Bcnt;
            }
            while (j!=i);
        }
    }
    void tarjan()
    {
        int i;
        Stop=Bcnt=Dindex=0;
        memset(DFN,0,sizeof(DFN));
        for (i=1;i<=n;i++)
            if (!DFN[i])
                tarjan_aid(i);
    }
#endif
};

int main()
{
    Graph a(10,20);

}
