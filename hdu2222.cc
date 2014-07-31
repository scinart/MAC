// Time-stamp: <2014-07-24 01:50:55 scinart>
// created at 2014-07-24 00:27:09
// hdu2222.cc

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

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;
const int  Sigma = 26; //字母表大小
const char Alpha = 'a';//字母表首字母
class ACautomata
{
private:
    bool failPointerBuilt;
public:
    struct Node
    {
        Node* father;
        Node* fail;
        Node* child[Sigma];
        int point;
        int offset;//这个node是第几个node
        Node()
        {
            father = NULL;
            fail=NULL;
            memset(child,0,sizeof(child));
            point=0;
            offset = -1;
        }
    };
    Node* root; //¡important! root->fail MUST be NULL.
public:
    ACautomata(){root = new Node; failPointerBuilt=false;}
    void GC(Node*& n)
    {
        if(n==NULL) return;
        for(int i=0; i<Sigma; i++) GC(n->child[i]);
        delete n;
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
                p->child[where]=new Node;
            p->child[where]->father = p;
            p=p->child[where];
            p->offset = where;
        }
        p->point += num;
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
                    // end node p matched;
                    // Node* bt = t;
                    // string str_matched;
                    // do{
                    //     str_matched += string(1,char(Alpha + bt->offset));
                    //     bt = bt->father;
                    // }while(bt->father!=NULL);
                    // reverse(ALL(str_matched));
                    ans += t->point;
                    t->point = 0;
                }
                t=t->fail;
            }
        }
        return ans;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);


    int cases;cin>>cases;
    string s;
    REP(temp______i,cases)
    {
        ACautomata aca;
        int W;cin>>W;
        REP(i,W)
        {
            cin>>s;
            aca.insert(s);
        }
        cin>>s;
        cout<<aca.query(s)<<'\n';
    }
    return 0;
}
