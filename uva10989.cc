//
// Time-stamp: <2014-07-27 14:12:46 scinart>

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
#include <memory>
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
    void add_bidirectional_edge(int u,int v,int w)
    {
        Net[u] = new((void*) data++) edge(v, w, Net[u]);
        Net[v] = new((void*) data++) edge(u, w, Net[v]);
        Net[u]->rev = Net[v];
        Net[v]->rev = Net[u];
    }
    void reset()
    {
        for(int i=0; i<maxnode;i++)
        {
            edge* this_ = Net[i];
            while(this_)
            {
                this_->cap += this_->flow;
                this_->flow = 0;
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
    int n,m, u, v, w,cases;
    scanf("%d", &cases);
    for(int cc=1;cc<=cases;cc++)
    {
        scanf("%d%d", &n,&m);
        Network net(n,m);
        for(int i=0; i<m; i++)
        {
            scanf("%d %d %d", &u, &v, &w);
            net.add_bidirectional_edge(u,v,w);
        }
        int ans=INT_MAX;
        for(int i=1; i<n;i++)
        {
            checkmin(ans,net.maxflow(i,n));
            net.reset();
        }
        printf("Case #%d: %d\n",cc,ans);
    }
    return 0;
}


