#include <iostream>
#include <stack>
#include <deque>
#include <queue>
#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>
using namespace std;
#ifndef EACH
#define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
#endif

#define BELLMAN //0-indexed.
#define LCA
#define TARJAN //should be 1-indexed.
#define DFS
#define ITERTREE
#define MDST //should leave node 0 blank.
             //must be strongly connected.
#define KRUSKAL

typedef ______ EDGE_TYPE;    //double or int
typedef ______ EDGE_TYPE_LL; //double or long long
#define EPS eps; //eps or 0;




#define TX template<class T>
TX struct Node {
    T key;
    int dist;
    EDGE_TYPE adder;
    bool adder_mark;
    Node<T> *L;
    Node<T> *R;
    Node(T k,int d=0):key(k),dist(d),adder(0),adder_mark(0),L(NULL),R(NULL){}
    void push_down()
    {
        if(adder_mark)
        {
            if(L)
                L->adder+=adder, L->adder_mark=true;
            if(R)
                R->adder+=adder, R->adder_mark=true;
            key->fixer+=adder;
            adder=0;
            adder_mark=false;
        }
    }
};
TX void merge(Node<T>* &A, Node<T>* &B)
{
    if(A==NULL) {std::swap(A,B);return;}
    if(B==NULL) return;
    A->push_down();
    B->push_down();
    if((B->key->cap)+B->adder+B->key->fixer<(A->key->cap)+A->adder+A->key->fixer)
        std::swap(A,B);
    merge(A->R,B);
    if((A->L==NULL) || (A->R!=NULL && A->R->dist>A->L->dist))
        std::swap(A->R,A->L);
    if(A->R==NULL)A->dist=0;
    else A->dist=A->R->dist+1;
    B=NULL;
}
TX void destroy(Node<T>* &tree)
{
    if(tree->L)destroy(tree->L);
    if(tree->R)destroy(tree->R);
    delete tree;
    tree=NULL;
}
////////// Complete Class Declarations //////////
// 左偏树模板类 //
/////////////////////////////////////////////////
// Predeclaration For Friend
TX class LeftistTree;
TX void merge(LeftistTree<T>&, LeftistTree<T>&);
// Class Declarations
template<class T>
class LeftistTree
{
    Node<T>* root;
    size_t SZ;
    LeftistTree(const LeftistTree& rhs);
    LeftistTree* operator=(const LeftistTree& rhs);
public:
    T top() const { return root->key; }
    bool empty() const { return root == NULL; }
    size_t size() const { return SZ; }
    friend void merge<>(LeftistTree<T>&, LeftistTree<T>&);
    void pop(){ merge(root->L, root->R); Node<T>* newRoot = root->L; delete root; root = newRoot; --SZ;}
    void insert(T val){ Node<T>* newTree = new Node<T>(val); merge(root, newTree); ++SZ;}
    LeftistTree():root(NULL),SZ(0){}
    LeftistTree(const T& elem):SZ(1){root=new Node<T>(elem);}
    void clear(){if(root)destroy(root);SZ=0;}
    void add_adder(EDGE_TYPE howmuch){if(root){root->adder+=howmuch; root->adder_mark=true;}}
    ~LeftistTree(){clear();}
};
TX void merge(LeftistTree<T>& A, LeftistTree<T>& B) {
    merge(A.root, B.root);
    A.SZ += B.SZ;
    B.SZ = 0;
}


#define NUMNODES 110
#ifdef MDST
const int maxnode = NUMNODES<<1;
#else
const int maxnode = NUMNODES;
#endif
const double DOUBLE_INF = 1234567890123;
const double eps=1e-6;

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
EDGE_TYPE_LL dist[maxnode];
int inqueue[maxnode]; //inqueue[node]>>1是次数，inqueue[node]&1是在不在queue里
int predecessor[maxnode];
#endif


#ifdef MDST

EDGE_TYPE_LL maxdist;

template<typename TT>struct edge;
edge<EDGE_TYPE>* in[maxnode];
int prov[maxnode];
int parent[maxnode];
std::deque<int> children[maxnode];
LeftistTree<edge<EDGE_TYPE>* > P[maxnode];

#endif

#if defined MDST || defined KRUSKAL
namespace DSET {

int pre[maxnode],Rank[maxnode];
int degree;
// 0 indexed;
void init(int n)
{
    degree=n;
    for(int i=0;i<n;i++) pre[i]=i, Rank[i]=1;
}

int fin(int x)
{
    int t,r=x;
    while(x!=pre[x]) x=pre[x];
    while(r!=x)
    {
        t=pre[r];
        pre[r]=x;
        r=t;
    }
    return x;
}

inline int test(int x,int y)
{
    return fin(x)==fin(y);
}
int unio(int a,int b)
{
    a=fin(a);
    b=fin(b);
    if(a==b) return a;
    degree--;
    if(Rank[a]>=Rank[b])
        return pre[b]=a, Rank[a]+=Rank[b], a;
    else
        return pre[a]=b, Rank[b]+=Rank[a], b;
}

}
#endif

template<typename TT>
struct edge{
    int ver;  // vertex
    TT cap; //capacity or cost
    TT fixer; // MDST only.
    edge *next; // next arc
    edge *rev; // reverse arc
    bool forward; //forward or backward edge.
    edge(){}
    edge(int Vertex, TT c, edge *Next, bool f):ver(Vertex), cap(c), fixer(0), next(Next), rev((edge*)NULL), forward(f){}
    void* operator new(size_t, void *p){return p;}
};
edge<EDGE_TYPE>*Net[maxnode];

template <typename TT>
struct Graph{
#define EACH_EDGE(e,init) for(__typeof__(init) e=init; e; e=e->next)
    edge<TT>* buffer;
    edge<TT>* data;
    int n;//n nodes.
#ifdef MDST
    int nn;//for new nodes;
#endif
    Graph(int _n,int _m):n(_n)
    {
        memset(Net,0,sizeof(Net));
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
#ifdef MDST
        nn=n-1;
        // memset(in,0,sizeof(in));
        // memset(prov,0,sizeof(prov));
        // memset(parent,0,sizeof(parent));
        for(int i=0;i<maxnode;i++)children[i].clear(),P[i].clear();
        DSET::init(maxnode);
#endif
        buffer = new edge<TT>[2*_m];
        data = buffer;
    }
    ~Graph() {
#ifdef MDST
        for(int xi=1;xi<=nn;xi++)in[xi]=0;
        for(int xi=1;xi<=nn;xi++)prov[xi]=0;
        for(int xi=1;xi<=nn;xi++)parent[xi]=0;
#endif
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
#ifdef MDST
        P[v].insert(Net[u]);
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

#ifdef MDST
    void contract()
    {
        int a = 1;//should be rand vertex.
        while(!(P[a].empty()))
        {
            edge<TT>* uv = P[a].top(); P[a].pop();
            int u=uv->rev->ver;
            int b = DSET::fin(u);
            if(a!=b)
            {
                in[a]=uv;
                prov[a]=b;
                if(in[u]==NULL) //Path extended.
                {
                    a=b;
                }
                else
                {
                    int c=++nn;
                    std::deque<int> temparray;
                    while(parent[a]==0)
                    {
                        temparray.push_back(a);
                        //DSET::pre[a]=c;
                        DSET::Rank[c]++;
                        parent[a]=c;
                        //cost[a]=-in[a]->cap;
                        children[c].push_back(a);
                        P[a].add_adder(-in[a]->cap-in[a]->fixer);
                        merge(P[c],P[a]);
                        a=DSET::fin(prov[a]);
                    }
                    EACH(it,temparray)DSET::pre[*it]=c;
                    a=c;
                }
            }
        }
    }
    EDGE_TYPE_LL expand(int r)
    {
        EDGE_TYPE_LL ans=0;
        std::deque<int> R;
        int rr=r;
        do{R.push_front(rr);} while((rr=parent[rr]));
        rr=r;
        bool firsttime=true;
        do
        {
            if(!firsttime)
            {
                r=in[R.front()]->ver;
                rr=r;
                R.pop_front();
                do{R.push_front(rr);} while((rr=parent[rr]));
            }
            edge<TT>* saved_inR = in[R.front()];
            while(R.front()!=r)
            {
                int c=R.front();R.pop_front();
                if(!children[c].empty())
                    EACH(it,children[c])
                    {
                        parent[*it]=0;
                        if(*it!=R.front())
                            R.push_back(*it);
                    }
            }
            // most inner node.
            if(!firsttime)
            {
                if(saved_inR->cap+eps>=maxdist)
                    return -1;
                else
                    ans+=saved_inR->cap;
            }
            in[r]=saved_inR;
            R.pop_front();
            firsttime=false;
        }while(!R.empty());
        return ans;
    }

#ifdef KRUSKAL
    void kruskal()
    {
        DSET::init(n);
        edge<TT>* edges = new edge<TT>[data-buffer];
        edge<TT>* theend = edges+(data-buffer);
        memcpy(edges,buffer,unsigned(data)-unsigned(buffer));
        sort(edges,theend,[](const edge<TT>& a,const edge<TT>& b){return a->cap<b.cap;});
        for(edge<TT>* it=edges;it!=theend;it++,it++)
        {
            if(DSET::fin(it->rev->ver)!=DSET::fin(it->ver))
            {
                //do stuff;
                DSET::unio(it->rev->ver,it->ver);
            }
        }
        free(edges);
    }
#endif
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
        for(int i=0;i<n;i++)dist[i]=DOUBLE_INF;
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
