#include <iostream>
#include <stack>
#include <deque>
#include <cstdio>
#include <cstring>

const int maxnode = 100010;
const double DOUBLE_INF = 1234567890123;
const double eps=1e-6;

#define BELLMAN
#define LCA
#define TARJAN
#define DFS
#define ITERTREE

#ifdef TARJAN
int DFN[maxnode];
int LOW[maxnode];
bool instack[maxnode];
int Stap[maxnode];
int Belong[maxnode];
int Stop, Bcnt, Dindex;
#endif

#ifdef LCA
  #ifndef ITERTREE
    #define ITERTREE
  #endif
int _d[maxnode][21]; // 21>log(N)
bool rmqinited;
#endif

#ifdef ITERTREE
int iteridx[maxnode]; //第几是哪个节点
int noderank[maxnode]; //节点第几
int itertrace[maxnode<<1]; //这里存的是rank.
int firstappearintrace[maxnode]; //节点第一次出现在itertrace中。
int rnk;
int trace;
#endif

#ifdef DFS
  #ifndef COLOR
    #define COLOR
  #endif
#endif

#ifdef DEG
int indegree[maxnode];
int outdegree[maxnode];
#endif
#ifdef COLOR
int color[maxnode];//0,1,2 is WHITE, GREY, BLACK, respectively.
enum {WHITE,GREY,BLACK};
#endif


#ifdef BELLMAN //a.k.a bellman ford.
#error long long or double?
XXX dist[maxnode];
int inqueue[maxnode]; //inqueue[node]>>1是次数，inqueue[node]&1是在不在queue里
int predecessor[maxnode];
#endif

template<typename TT>
struct edge{
    int ver;  // vertex
    TT cap; //capacity or cost
    edge *next; // next arc
    edge *rev; // reverse arc
    bool forward; //forward or backward edge.
    edge(){}
    edge(int Vertex, TT c, edge *Next, bool f)
        :ver(Vertex), cap(c), next(Next), rev((edge*)NULL), forward(f){}
    void* operator new(size_t, void *p){
        return p;
    }
};
#error TT is int or double
edge<TT>*Net[maxnode];

template <typename TT>
struct Graph{
#define EACH_EDGE(e,init) for(__typeof__(init) e=init; e; e=e->next)
    edge<TT>* buffer;
    edge<TT>* data;
    int n;//n nodes.
    Graph(int _n,int _m):n(_n)
    {
        for(int i=0; i<maxnode; i++) Net[i]=NULL;
#ifdef DEG
        memset(indegree,0,sizeof(indegree));
        memset(outdegree,0,sizeof(outdegree));
#endif
#ifdef COLOR
        memset(color,0,sizeof(color));
#endif
#ifdef LCA
        rmqinited = false;
#endif
        buffer = new edge<TT>[2*_m];
        data = buffer;
    }
    ~Graph() {
        delete[] buffer;
    }
    void add_edge(int u,int v, TT c)
    {
        Net[u] = new((void*) data++) edge<TT>(v, c, Net[u],true);
        Net[v] = new((void*) data++) edge<TT>(u, 0, Net[v],false);
        Net[u]->rev = Net[v];
        Net[v]->rev = Net[u];
#ifdef DEG
        Node[u].outdegree++;
        Node[v].indegree++;
#endif
    }
    void add_bidirectional_edge(int u,int v, TT c)
    {
        Net[u] = new((void*) data++) edge<TT>(v, c, Net[u],true);
        Net[v] = new((void*) data++) edge<TT>(u, c, Net[v],true);
        Net[u]->rev = Net[v];
        Net[v]->rev = Net[u];
#ifdef DEG
        Node[u].indegree++;
        Node[u].outdegree++;
        Node[v].indegree++;
        Node[v].outdegree++;
#endif
    }


#ifdef DFS
    void dfs(int node)
    {
        color[node] = GREY;
        EACH_EDGE(e,Net[node])
            if(e->forward && color[e->ver] == WHITE)
                dfs(e->ver);
        color[node] = BLACK;
    }
#endif

    void dfstree(int root)
    {//non-recursive
        edge<TT>* it = Net[root];
        std::stack<edge<TT>*> next;
        while(it)
        {
            for(;it && !it->forward;it=it->next);
            if(!it)
            {
                if(!next.empty())
                {
                    it=next.top();
                    next.pop();
                }
                else
                {
                    continue; //=break;
                }
            }
            else
            {
                it->rev->forward=false;
                if(it->next)
                {
                    next.push(it->next);
                }
                it=Net[it->ver];
            }
        }
    }

#ifdef ITERTREE
    void itertree(int root)
    {
        edge<TT>* it = Net[root];
        std::stack<edge<TT>*> next;
        rnk=0;
        trace=0;
        iteridx[rnk]=root;
        noderank[root]=rnk;
        firstappearintrace[root]=trace;
        itertrace[trace]=noderank[root];
        rnk++;trace++;
        while(it)
        {
            for(;it && !it->forward;it=it->next); // find an edge;
            if(!it)
            {
                if(!next.empty())
                {
                    it=next.top();
                    next.pop();
                    //currently back to father;
                    //backto is it->rev->ver;
                    itertrace[trace++]=noderank[it->rev->ver];
                    while(!next.empty() && !it->next)
                    {
                        it=next.top();
                        next.pop();
                        //currently back to father;
                        //backto is it->rev->ver;
                        itertrace[trace++]=noderank[it->rev->ver];
                    }
                    if(it->next)
                    {
                        it=it->next;
                    }
                    else
                    {
                        it=NULL;//= break;
                    }
                }
                else
                {
                    continue; //=break;
                }
            }
            else
            {
                it->rev->forward=false;
                int ver=it->ver;
                iteridx[rnk]=ver;
                noderank[ver]=rnk;
                firstappearintrace[ver]=trace;
                itertrace[trace]=noderank[ver];
                rnk++;trace++;
                next.push(it);
                it=Net[ver];
            }
        }
    }
#endif

#ifdef LCA
    void RMQ_Init(int A[], int size)
    {
        int n=size;
        for (int i=0;i<n;i++) _d[i][0]=A[i];
        for (int j=1;(1<<j)<=n;j++)
            for (int i=0;i+(1<<j)-1<n;i++)
                _d[i][j]=std::min(_d[i][j-1],_d[i+(1<<(j-1))][j-1]);
    }


    int RMQ(int L,int R)
    {
        if(R<L)std::swap(L,R);
        int k=0;
        for (k=0;1<<(k+1)<=R-L+1;k++);
        return std::min(_d[L][k],_d[R-(1<<k)+1][k]);
    }

    int lca(int nodea, int nodeb)
    {
        if(!rmqinited)
        {
            RMQ_Init(itertrace,trace);
            rmqinited=true;
        }
        if(nodea==nodeb)return nodea;
        else
            return iteridx[RMQ(firstappearintrace[nodea], firstappearintrace[nodeb])];
    }
#endif

#ifdef TARJAN
    void tarjan_aid(int i)
    {
        int j;
        DFN[i]=LOW[i]=++Dindex;
        instack[i]=true;
        Stap[++Stop]=i;
        EACH_EDGE(e, Net[i])
        {
            if(e->forward)
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
        memset(DFN,0,sizeof(DFN));
        memset(LOW,0,sizeof(LOW));
        memset(instack,0,sizeof(instack));
        memset(Stap,0,sizeof(Stap));
        memset(Belong,0,sizeof(Belong));

        int i;
        Stop=Bcnt=Dindex=0;
        for (i=1;i<=n;i++)
            if (!DFN[i])
                tarjan_aid(i);
    }
#endif

#ifdef BELLMAN
#define SLF
#define LLL
    int bellman(int s);
#endif
};

#ifdef BELLMAN
template<> int Graph<int>::bellman(int s)
    {
        memset(inqueue,0,sizeof(inqueue));
        std::deque<int> q;
        memset(dist,0x3F,sizeof(dist));
        dist[s]=0;
        predecessor[s]=s;
        q.push_back(s);
        inqueue[s]++;
#ifdef LLL
        long long sumofdis=0;
#endif
        while(!q.empty())
        {
#ifdef LLL
            while((dist[q.front()])*q.size()>sumofdis)
            {
                q.push_back(q.front());
                q.pop_front();
            }
#endif
            int x=q.front();
            q.pop_front();
            inqueue[x]++;
#ifdef LLL
            sumofdis-=dist[x];
#endif
            EACH_EDGE(e, Net[x])
            {
                int v=e->ver;
                if(e->forward && dist[v]>dist[x]+e->cap)
                {
                    predecessor[v]=x;
                    dist[v]=dist[x]+e->cap;
                    if((inqueue[v]&1)==0)
                    {
#ifdef SLF
                        if(q.empty() || dist[v]<=dist[q.front()])
                            q.push_front(v);
                        else
#endif
                            q.push_back(v);
                        inqueue[v]++;
#ifdef LLL
                        sumofdis+=dist[v];
#endif
                        if((inqueue[v]>>1)>=n)
                        {
                            //negative cycle;
                            return -1;
                        }
                    }
                }
            }
        }
        return 0;
    }


template<> int Graph<double>::bellman(int s)
    {
        memset(inqueue,0,sizeof(inqueue));
        std::deque<int> q;
        REP(i,n)dist[i]=DOUBLE_INF;
        dist[s]=0;
        predecessor[s]=s;
        q.push_back(s);
        inqueue[s]++;
#ifdef LLL
        double sumofdis=0;
#endif
        while(!q.empty())
        {
#ifdef LLL
            while((dist[q.front()])*q.size()>sumofdis+eps)
            {
                q.push_back(q.front());
                q.pop_front();
            }
#endif
            int x=q.front();
            q.pop_front();
            inqueue[x]++;
#ifdef LLL
            sumofdis-=dist[x];
#endif
            EACH_EDGE(e, Net[x])
            {
                int v=e->ver;
                if(e->forward && dist[v]>dist[x]+e->cap)
                {
                    predecessor[v]=x;
                    dist[v]=dist[x]+e->cap;
                    if((inqueue[v]&1)==0)
                    {
#ifdef SLF
                        if(q.empty() || dist[v]<=dist[q.front()])
                            q.push_front(v);
                        else
#endif
                            q.push_back(v);
                        inqueue[v]++;
#ifdef LLL
                        sumofdis+=dist[v];
#endif
                        if((inqueue[v]>>1)>=n)
                        {
                            //negative cycle;
                            return -1;
                        }
                    }
                }
            }
        }
        return 0;
    }

#endif

int main()
{
    Graph<double> g(10,20);

}
