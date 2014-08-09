// Time-stamp: <2014-08-08 12:50:22 scinart>
// created at 2014-08-04 11:25:44
// hdu2680.cc

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

const int maxnode = 1010;

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
enum Color {WHITE,GREY,BLACK};
struct node{
    int indegree;
    int outdegree;
    int dis;
    Color color;
    node():indegree(0),outdegree(0),dis(0x3FFFFFFF),color(WHITE){}
    void reset(){indegree=0;outdegree=0;color=WHITE;dis=0x3FFFFFFF;}
} Node[maxnode];

struct Graph{
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
    ~Graph()
    {
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
#define EACH_EDGE(e,node) for(edge* e=node; e; e=e->next)
};



template <typename T>
class PTT
{
public:
    T first;
    T second;
    PTT (T a, T b){
        first = a;
        second = b;
    }
    PTT& operator=(const PTT& rhs)
    {
        first = rhs.first;
        second = rhs.second;
        return *this;
    }
    bool operator==(const PTT& rhs)const
    {
        return first==rhs.first && second == rhs.second;
    }
    bool operator<(const PTT& rhs)const
    {
        return second>rhs.second;
    }
};

bool poped[maxnode];
int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    int n,m,s;
#ifdef ONLINE_JUDGE
    while(cin>>n>>m>>s)
#else
        cin>>n>>m>>s;
#endif
    {
        Graph g(n, m);
        memset(poped,0,sizeof(poped));
        REP(i,m)
        {
            int u,v,c;
            cin>>u>>v>>c;
            g.add_edge(v, u, c);
        }
        set<int> dest;
        int x;cin>>x;
        REP(i,x)
        {
            int y;cin>>y;
            dest.insert(y);
        }

        typedef PTT<int> BI;
        priority_queue<BI> pq;
        pq.push(BI(s,0));
        Node[s].dis=0;
        bool ok=false;
        while(!pq.empty())
        {
            int x=pq.top().first;
            int dis = Node[x].dis;
            pq.pop();
            if(poped[x]) continue;
            poped[x]=true;
            if(dest.find(x)!=dest.end())
            {
                cout<<dis<<'\n';
                ok=true;
                break;
            }
            EACH_EDGE(e, Net[x])
            {
                if(!poped[e->ver] && e->cap)
                {
                    checkmin(Node[e->ver].dis, dis+e->cap);
                    pq.push(BI(e->ver,Node[e->ver].dis));
                }
            }
        }
        if(!ok)cout<<"-1\n";
    }

    return 0;
}
