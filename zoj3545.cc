// Time-stamp: <2014-08-08 20:57:56 scinart>
// created at 2014-08-08 17:48:35
// zoj3545.cc

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


const int  Sigma = 4;//字母表大小
const char Alpha = 'A';//字母表首字母
const int MAXN = 1005;
struct Node
{
    Node* father;
    Node* fail;
    Node* child[Sigma];
    int point;
    Node()
    {
        father = NULL;
        fail=NULL;
        memset(child,0,sizeof(child));
        point=0;
    }
    void* operator new(size_t, void* p){return p;}
} buffer[MAXN];


map<Node*, int> StateCompress;
int stateCnt;
class ACautomata;
struct STRUCT{
    bool hit;
    bool trueval;
    int val;
    STRUCT():hit(false),trueval(false),val(0){};
    void set(bool h,int v){hit=h;if(trueval)checkmax(val,v);else{val=v;trueval=true;}}
}pointget[2][MAXN][1024];

class Fur{
public:
    bool t;
    Fur():t(false){}
    operator int(){return t;}
    int operator+(int){return !t;}
    void operator++(int){t=!t;}
};

void dp(int lent)
{
    pointget[0][0][0].hit = true;
    Fur fir;
    for(int firfir=0; firfir<lent; firfir++,fir++)
    {
        for(int node=0; node<MAXN; node++)
        {
            for(int state=0;state<1024;state++)
            {
                if(pointget[fir][node][state].hit)
                {
                    Node* pn = &buffer[node];
                    int val = pointget[fir][state][state].val;
                    for(int ch=0; ch<4; ch++)
                    {
                        Node* p=pn;
                        if(p->child[ch])
                        {
                            p=p->child[ch];
                            if((StateCompress[p]&state) == 0)
                            {
                                pointget[fir+1][p-buffer][(StateCompress[p]|state)]
                                    .set(true,val+p->point);
                            }
                            else
                            {
                                pointget[fir+1][p-buffer][state].set(true,val);
                            }
                        }
                        else
                        {
                            while (p->child[ch]==NULL && p!=buffer) p=p->fail;
                            if (p->child[ch]==NULL)
                            {
                                pointget[fir+1][p-buffer][state].set(true,val);
                            }
                            else
                            {
                                p=p->child[ch];
                                if((StateCompress[p]&state) == 0)
                                    pointget[fir+1][p-buffer][state|StateCompress[p]].set(true,val+p->point);
                                else
                                    pointget[fir+1][p-buffer][state].set(true,val);
                            }
                        }
                    }
                }
            }
        }
    }
}

class ACautomata
{
private:
    bool failPointerBuilt;
public:
    Node* root; //¡important! root->fail MUST be NULL.
    Node* data;
public:
    ACautomata():data(buffer){memset(buffer,0,sizeof(buffer));root = new((void*) data++)Node; failPointerBuilt=false;}
    void GC(Node*& n)
    {
        // if(n==NULL) return;
        // for(int i=0; i<Sigma; i++) GC(n->child[i]);
        // delete n;
    }
    ~ACautomata(){GC(root);}
public:
    void insert(const string& s,int num = 1)
    {
        failPointerBuilt = false;
        Node* p = root;
        int len = s.length();
        for (int i=0; i<len; i++)
        {
            int where=s[i]-Alpha;
            if (p->child[where]==NULL)
                p->child[where]=new ((void*)data++) Node;
            p->child[where]->father = p;
            p=p->child[where];
        }
        p->point += num;
        StateCompress[p]=1<<(stateCnt++);
    }
    void buildFailPoint()
    {
        failPointerBuilt = true;
        //bfs
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* now = q.front(); q.pop();
            for (int i=0;i<Sigma;++i)
                if (now->child[i]!=NULL) {
                    if (now==root)
                        now->child[i]->fail=root;
                    else {
                        Node *p=now->fail;
                        while (p!=NULL) {
                            if (p->child[i]!=NULL) {
                                now->child[i]->fail=p->child[i];
                                break; }
                            p=p->fail; }
                        if (p==NULL) now->child[i]->fail=root; }
                    q.push(now->child[i]); } }
    }
    int query(const string& queryString)
    {
        if(!failPointerBuilt) buildFailPoint();
        int ans=0;
        int len=queryString.length();
        Node *p=root;
        for (int i=0;i!=len;++i)
        {
            int index=queryString[i]-Alpha;
            while (p->child[index]==NULL && p!=root) p=p->fail;
            if (p->child[index]==NULL) continue;
            p=p->child[index];
            Node *t=p;
            while (t!=root)
            {
                if (t->point!=0)
                {
                    // end node p matched;;
                    ans += t->point;
                }
                t=t->fail;
            }
        }
        return ans;
    }
};


int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    int n,len;
    while(cin>>n>>len){

        stateCnt=0;
        StateCompress.clear();
        ACautomata aca;
        REP(i,n)
        {
            string s;int val;
            cin>>s>>val;
            if(s.length()>n)
            {
                continue;
            }
            EACH(it,s)
            {
                switch(*it)
                {
                  case 'C':
                  {
                      (*it)--;
                      break;
                  }
                  case 'G':
                  {
                      *it='C';
                      break;
                  }
                  case 'T':
                  {
                      *it='D';
                      break;
                  }
                }
            }
            if(val)
                aca.insert(s, val);
        }

        aca.buildFailPoint();
        memset(pointget,0,sizeof(pointget));
        dp(len);

        len++;
        len%=2;
        int ans=-123456789;
        for(int i=0; i<MAXN; i++)
        {
            for(int state=0; state<1024; state++)
                if(pointget[len][i][state].hit)
                {
                    cout<<pointget[len][i][state].val<<'\n';
                    checkmax(ans,pointget[len][i][state].val);
                }
        }
        if(ans>=0)
            cout<<ans<<'\n';
        else
        {
            cout<<"No Rabbit after 2012!\n";
        }
    }
    return 0;
}
