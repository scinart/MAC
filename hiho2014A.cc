
//
// Time-stamp: <2014-07-29 00:56:55 scinart>

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
#include <memory>
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

#define REP(i, n) for (int  i=0; i<(n); ++i)
#define FOR(i, b, e) for (int i=(b); i<(e); ++i)
#ifdef __GNUC__
  #if __cplusplus >= 201103L
    #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
  #else
    #ifndef __STRICT_ANSI__
      #define EACH(it,A) for (typeof(A.begin()) it=A.begin(); it!=A.end(); ++it)
    #else
      #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
    #endif
  #endif
  #if __cplusplus >= 201103L
      #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
  #else
    #ifndef __STRICT_ANSI__
      #define REACH(it,A) for (typeof(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
    #else
      #define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
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

const int  Sigma = 26; //字母表大小
const char Alpha = 'a';//字母表首字母
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
};

Node buffer[1234567];
Node* data;
class ACautomata
{
public:
    Node* root; //¡important! root->fail MUST be NULL.
public:
    void* operator new(size_t, void *p){return p;}
    ACautomata(){data=&buffer[0]; root = new((void*)data++) Node;}
public:
    void insert(const string& s,int num = 1)
    {
        Node* p = root;
        int len = s.length();
        for (int i=0; i<len; i++)
        {
            int where=s[i]-'a';
            if (p->child[where]==NULL)
                p->child[where]=new((void*)data++) Node;
            p->child[where]->father = p;
            p=p->child[where];
        }
        p->point += num;
    }
    void buildFailPoint()
    {
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
        buildFailPoint();
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
                    cout<<"YES\n";exit(0);
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
    ACautomata aca;
    int n;cin>>n;
    string s;
    REP(i,n)
    {
        cin>>s;
        aca.insert(s);
    }
    cin>>s;
    aca.query(s);
    cout<<"NO\n";
    return 0;
}
