// Time-stamp: <2014-08-24 16:32:20 scinart>
// created at 2014-08-24 15:12:21
// hdu2544.cc

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cassert>
#include <list>
#include <iomanip>
#include <cmath>
#include <deque>
#include <stack>
#include <utility>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <climits>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <sstream>

using namespace std;

#define REP(i, n) for (int  i=0; i<(int)(n); ++i)
#define REP_1(i, n) for (int i=1; i<=(int)(n); ++i)
#define FOR(i, b, e) for (int i=(b); i<(int)(e); ++i)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define DWN(i, b, e) for (int i=(b); i>(int)(e); --i)
#define ALL(c) c.begin(), c.end()

#ifdef __GNUC__
  #if __cplusplus >= 201103L
    #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
    #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
  #else
    #ifdef __STRICT_ANSI__
      #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
      #define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
    #else
      #define EACH(it,A) for (typeof(A.begin()) it=A.begin(); it!=A.end(); ++it)
      #define REACH(it,A) for (typeof(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
    #endif
  #endif
#else
  #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
  #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
#endif
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

typedef unsigned int uint;
typedef unsigned long long ULL;
typedef long long LL;
typedef long long ll;
typedef pair<int, int> PII;
typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;

bool PIIfs(const PII& a, const PII& b){return a.first<b.first || (a.first == b.first && a.second<b.second);}
bool PIIsf(const PII& a, const PII& b){return a.second<b.second || (a.second == b.second && a.first<b.first);}
bool PIIFS(const PII& a, const PII& b){return a.first>b.first || (a.first == b.first && a.second>b.second);}
bool PIISF(const PII& a, const PII& b){return a.second>b.second || (a.second == b.second && a.first>b.first);}
bool PIIfS(const PII& a, const PII& b){return a.first<b.first || (a.first == b.first && a.second>b.second);}
bool PIIsF(const PII& a, const PII& b){return a.second<b.second || (a.second == b.second && a.first>b.first);}
bool PIIFs(const PII& a, const PII& b){return a.first>b.first || (a.first == b.first && a.second<b.second);}
bool PIISf(const PII& a, const PII& b){return a.second>b.second || (a.second == b.second && a.first<b.first);}

template <typename T> inline T max(T a, T b, T c) { return max(max(a, b), c); }
template <typename T> inline T max(T a, T b, T c, T d) { return max(max(a, b, c), d); }
template <typename T> inline T max(T a, T b, T c, T d, T e) { return max(max(a, b, c, d), e); }
template <typename T> inline T min(T a, T b, T c) { return min(min(a, b), c); }
template <typename T> inline T min(T a, T b, T c, T d) { return min(min(a, b, c), d); }
template <typename T> inline T min(T a, T b, T c, T d, T e) { return min(min(a, b, c, d), e); }

template <typename T> inline istream& RD(T& x){return cin>>x;}
template <typename T, typename U> inline istream& RD(T& a, U& b){return cin>>a>>b;}
template <typename T, typename U, typename V> inline istream& RD(T& a, U& b, V& c){return cin>>a>>b>>c;}
template <typename T, typename U, typename V, typename W>
inline istream& RD(T& a, U& b, V& c,W& d){return cin>>a>>b>>c>>d;}
template <typename T, typename U, typename V, typename W, typename X>
inline istream& RD(T& a, U& b, V& c,W& d,X& e){return cin>>a>>b>>c>>d>>e;}

template <typename T>
void checkmin(T& a,const T& b){if(b<a)a=b;}
template <typename T>
void checkmax(T& a, const T& b){if(b>a)a=b;}


const int maxnode = 110;


#define BELLMAN
// #define LCA
// #define TARJAN
// #define DFS
// #define ITERTREE


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
    bool forward; //forward or backward edge.
    edge(){}
    edge(int Vertex, int c, edge *Next, bool f)
        :ver(Vertex), cap(c), next(Next), rev((edge*)NULL), forward(f){}
    void* operator new(size_t, void *p){
        return p;
    }
}*Net[maxnode];


#ifdef LCA
  #ifndef ITERTREE
    #define ITERTREE
  #endif
int _d[N][21]; // 21>log(N)
bool rmqinited;
#endif

#ifdef ITERTREE
int iteridx[maxnode]; //第几是哪个节点
int noderank[maxnode]; //节点第几
int itertrace[maxnode<<1]; //这里存的是rank.
int firstappearintrace[maxnode]; //节点第一次出现在itertrace中。
int rank;
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
int dist[maxnode];
int inqueue[maxnode]; //inqueue[node]>>1是次数，inqueue[node]&1是在不在queue里
int predecessor[maxnode];
#endif

struct Graph{
#define EACH_EDGE(e,init) for(edge* e=init; e; e=e->next)
    edge* buffer;
    edge* data;
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
        buffer = new edge[2*_m];
        data = buffer;
    }
    ~Graph() {
        delete[] buffer;
    }
    void add_edge(int u,int v, int c)
    {
        Net[u] = new((void*) data++) edge(v, c, Net[u],true);
        Net[v] = new((void*) data++) edge(u, 0, Net[v],false);
        Net[u]->rev = Net[v];
        Net[v]->rev = Net[u];
#ifdef DEG
        Node[u].outdegree++;
        Node[v].indegree++;
#endif
    }
    void add_bidirectional_edge(int u,int v, int c)
    {
        Net[u] = new((void*) data++) edge(v, c, Net[u],true);
        Net[v] = new((void*) data++) edge(u, c, Net[v],true);
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
        Node[node].color = GREY;
        EACH_EDGE(e,Net[node])
            if(e->forward && Node[e->ver].color == WHITE)
                dfs(e->ver);
        Node[node].color = BLACK;
    }
#endif

    void dfstree(int root)
    {//non-recursive
        edge* it = Net[root];
        std::stack<edge*> next;
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
        edge* it = Net[root];
        std::stack<edge*> next;
        rank=0;
        trace=0;
        iteridx[rank]=root;
        noderank[root]=rank;
        firstappearintrace[root]=trace;
        itertrace[trace]=noderank[root];
        rank++;trace++;
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
                iteridx[rank]=ver;
                noderank[ver]=rank;
                firstappearintrace[ver]=trace;
                itertrace[trace]=noderank[ver];
                rank++;trace++;
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
                _d[i][j]=min(_d[i][j-1],_d[i+(1<<(j-1))][j-1]);
    }


    int RMQ(int L,int R)
    {
        if(R<L)swap(L,R);
        int k=0;
        for (k=0;1<<(k+1)<=R-L+1;k++);
        return min(_d[L][k],_d[R-(1<<k)+1][k]);
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
            return idx[RMQ(firstappearintrace[nodea], firstappearintrace[nodeb])];
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
    int bellman(int s)
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
            while(((long long)(dist[q.front()]))*q.size()>sumofdis)
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
};

int main()
{
    int n,m;
    while(scanf("%d %d", &n, &m),n)
    {
        Graph g(n,10010);
        for(int i=0,u,v,w;i<m;i++)
        {
            scanf("%d %d %d", &u, &v, &w);
            g.add_bidirectional_edge(u, v, w);
        }
        g.bellman(1);
        printf("%d\n", dist[n]);
    }
    return 0;
}
