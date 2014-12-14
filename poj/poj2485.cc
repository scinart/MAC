// Time-stamp: <2014-08-08 00:11:45 scinart>
// created at 2014-08-07 23:14:40
// hdu1102.cc

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


const int maxnode = 550;

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


namespace DSET {

const int MAXN = 550;
int pre[MAXN],Rank[MAXN];
int degree;
// default is 1-indexed
int base;
void INIT(int n, int base=1) /* 初始化函数 */
{
    degree=n;
    FOR(i,base,n+base) pre[i]=i, Rank[i]=1;
}

int FIND(int x)
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

inline int TEST(int x,int y)
{
    return FIND(x)==FIND(y);
}
void UNION(int a,int b)
{
    a=FIND(a);
    b=FIND(b);
    if(a==b) return;
    if(Rank[a]>=Rank[b])
        pre[b]=a, Rank[a]+=Rank[b];
    else
        pre[a]=b, Rank[b]+=Rank[a];
    degree--;
}

}

template <typename T>
class PTTT
{
public:
    T first;
    T second;
    T third;
    PTTT (T a, T b,T c){
        first = a;
        second = b;
        third = c;
    }
    PTTT& operator=(const PTTT& rhs)
    {
        first = rhs.first;
        second = rhs.second;
        third=rhs.third;
        return *this;
    }
    bool operator==(const PTTT& rhs)const
    {
        return first==rhs.first && second == rhs.second && third==rhs.third;
    }
    bool operator<(const PTTT& rhs)const
    {
        return third<rhs.third;
    }
};

int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    

// krustral
// 3
// 0 990 692
// 990 0 179
// 692 179 0
// 1
// 1 2

    int n,cases;
    scanf("%d", &cases);
    while(cases--)
    {
        scanf("%d", &n);
        Graph g(n,n*n);
        vector<PTTT<int> >tri;
        REP(i,n)
        {
            REP(j,n)
            {
                int w;
                scanf("%d", &w);
                tri.push_back(PTTT<int>(i,j,w));
            }
        }
        DSET::INIT(n, 0);
        int ans=0;
        sort(ALL(tri));
        vector<PTTT<int> >::iterator it=tri.begin();
        while(DSET::degree!=1)
        {
            if(!DSET::TEST(it->first, it->second))
            {
                DSET::UNION(it->first, it->second);
                ans=it->third;
            }
            it++;
        }
        printf("%d\n", ans);
    }



    return 0;
}
