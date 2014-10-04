// Time-stamp: <2014-08-27 18:24:34 scinart>
// created at 2014-08-26 23:19:25
// cf263d1E.cc

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
    #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
    #define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
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



const int MAXN = 100010;
const int Sigma = 4;
int gg[4][4];
bool pushed[MAXN<<1];
struct Node {
    Node* next[Sigma];
    Node* par; //parent
    vector<Node*> child;
    int val; //len
    bool pushed;
    bool end; //if it is final state.
}buffer[MAXN << 1]; //Note that the size of POOL should be doubled.
string endA,endB,endC,endD;
class SAM {
public:
    Node* data,*root,*last;
    SAM():data(buffer+1),root(buffer),last(buffer)
    {
        memset(buffer,0,sizeof(buffer));
    }
    set<char> bfs(Node* roo, int& depth)
    {
        memset(pushed,0,sizeof(pushed));
        set<char> ans;
        depth=1;
        queue<Node*> mq;
        queue<Node*> sq;
        mq.push(roo);
        Node* aid;
        bool touchend=false;
        while(!touchend)
        {
            depth++;
            while(!mq.empty())
            {
                aid=mq.front();mq.pop();
                REP(i,Sigma)
                {
                    if(!aid->next[i])
                    {
                        touchend=true;
                        ans.insert(char('A'+i));
                    }
                    else if(!pushed[aid->next[i]-root])
                    {
                        pushed[aid->next[i]-root]=true;
                        sq.push(aid->next[i]);
                    }
                }
            }
            swap(mq,sq);
        }
        return ans;
    }
    void add(int x) {
        Node *p = last, *np = data++;
        np->val = p->val + 1; np->end = false;
        while (p && !p->next[x])
        {
            p->next[x] = np;
            p = p->par;
        }
        if (p==0) {np->par = root;}
        else
        {
            Node *q = p->next[x];
            if (q->val == p->val+1)
            {
                np->par = q;
            }
            else
            {
                Node *nq = data++;
                nq->val = p->val + 1;
                memcpy(nq->next, q->next, sizeof q->next);
                nq->par = q->par;
                np->par = q->par = nq;
                while (p && p->next[x] == q)
                    p->next[x] = nq, p = p->par;
            }
        }
        last = np;
    }
    void buildfinal()
    { //use this to build final state.
        Node* p = last;
        while(p)
        {
            p->end=true;
            p=p->par;
        }
    }
    void buildchild()
    {
        for(Node* x=root; x!=data; x++)
        {
            if(x->par)
            {
                (x->par->child).push_back(x);
            }
        }
    }
};




int lenarr[4];
set<char> sarr[4];
vector<int> nodes;
vector<vector<int> > paths;

void dfs(int tt, int goal=-1)
{
    if(goal==-1)goal=tt;
//    REP(i,4){REP(j,4)cout<<gg[i][j];cout<<'\n';}
    nodes.push_back(tt);
    EACH(it,sarr[tt])
    {
        int x=*it-'A';
        if(find(ALL(nodes), x)!=nodes.end())
        {
//            if(x==goal)everloop=true;
            {
                paths.push_back(nodes);
                paths.back().push_back(x);
            }
        }
        else
        {
            dfs(x,goal);
        }
    }
    nodes.pop_back();
}


int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    ll n;string s;
    RD(n,s);

    SAM sam;
    int len=s.size();
    EACH(it,s)sam.add(*it-'A');

    sarr[0]=sam.bfs((sam.root)->next[0],lenarr[0]);
    sarr[1]=sam.bfs((sam.root)->next[1],lenarr[1]);
    sarr[2]=sam.bfs((sam.root)->next[2],lenarr[2]);
    sarr[3]=sam.bfs((sam.root)->next[3],lenarr[3]);

    int minlen = *min_element(lenarr,lenarr+4);

//    cout<<"minlen is "<<minlen<<'\n';
    REP(i,4)
    EACH(it,sarr[i])gg[i][*it-'A']=lenarr[i];

    REP(tt,4)
    {
        if(lenarr[tt]==minlen)
        {
            dfs(tt);
        }
    }

#ifdef DEBUG
    REP(i,4){
        REP(j,4)
        {
            cout<<gg[i][j]<<' ';
        }
        cout<<'\n';
    }
#endif

    long long bestans=1;
    n--;
    long long nn = n;
    //brute force
    {
        EACH(it,paths)
        {
            n=nn;
            long long ans=1,rem=0;
            if(it->front()!=it->back())
            {
                vector<int>::iterator fit = find(it->begin(), it->end(), it->back());
                for(vector<int>::iterator bbit=it->begin(); bbit!=fit; bbit++)
                {
                    if(n>=(lenarr[*bbit]-1))
                    {
                        ans++;
                        n-=(lenarr[*bbit]-1);
                    }
                    else break;
                }
                it->erase(it->begin(), fit);
            }
            EACH(jt,(*it))
            {
                if(jt+1==it->end())
                {
                    it->erase(jt);
                    break;
                }
                else
                {
                    *jt=lenarr[*jt];
                }
            }
            int sumn = 0;
            int sz=it->size();
            EACH(jt,(*it))
            {
                sumn+=*jt;
            }
            ans += (n)/(sumn-sz)*sz;
            rem = (n)%(sumn-sz);
            EACH(jt,(*it))
            {
                rem-=(*jt-1);
                if(rem<0)break;
                else ans++;
            }
//            cout<<ans<<'\n';
            checkmax(bestans,ans);
        }
    }
    cout<<bestans<<'\n';


    return 0;
}

