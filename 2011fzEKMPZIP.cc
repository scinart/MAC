// Time-stamp: <2014-08-04 20:46:15 scinart>
// created at 2014-08-04 16:14:51
// 2011fzE.cc
// non recursize dfs, OK
// Accepted.

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


const int MAXT = 1200100;
const int MAXP = 7010;
char P[MAXP], T[MAXT];

int Pi[MAXP], lenP, lenT;

struct node{
    node* l,*r,*p;
    int val;
    void* operator new(size_t, void* p){return p;}
    node():l(NULL),r(NULL),p(NULL),val(0){}
    node(node* l_, node* r_, node* p_, int v):l(l_),r(r_),p(p_),val(v){}
} buffer[600010];

int cccnt;
class Fake;
class Tree
{
public:
    node* data;
    node* root;
    int cnt;
    map<int,node*> minode;

    Tree():data(buffer),cnt(0)
    {
        root = new ((void*)data++)node();
    }

    void insert_val(int v)
    {
        if(cnt==0)
        {
            root->val=v;
            minode[v]=root;
        }
        else
        {
            map<int,node*>::iterator up = minode.upper_bound(v);
            int op=2;
            if(up==minode.end())
            {
                up--;
                op=2;
            }
            else if(up->second->l == NULL)
            {
                op=1;
            }
            else
            {
                up--;
                op=2;
            }

            if(op==1)
            {
                up->second->l = new ((void*)data)node(NULL,NULL,up->second, v);
            }
            else
            {
                up->second->r = new ((void*)data)node(NULL,NULL,up->second,v);
            }
            minode[v]=data;
            data++;
        }
        cnt++;
    }

//     void dfs(const Fake& s)// non recursive.
//     {
//         node* cur = root;
//         while(true)
//         {
//             while(cur->l)
//             {
//                 char va=2+cur->val%2;
//                 s+=va;
//                 cur=cur->l;
//             }
//             char va=2+cur->val%2;
//             s+=va;
//             if(cur->r)
//             {
//                 cur=cur->r;
//                 continue;
//             }
//             else
//             {
// TT:             node* parent = cur->p;
//                 if(parent->l == cur && parent->r)
//                 {
//                     s+=char(2+parent->val%2);
//                     cur = parent->r;
//                     continue;
//                 }
//                 else
//                 {
//                     cur = cur->p;
//                     char va=2+cur->val%2;
//                     s+=va;
//                     if(cur==root) return;
//                     goto TT;
//                 }
//             }
//         }
//     }

    void dfs()// non recursive.
    {
        node* cur = root;
        while(true)
        {
            while(cur->l)
            {
                char va=2+cur->val%2;
                T[cccnt++]=va;
                cur=cur->l;
            }
            char va=2+cur->val%2;
            T[cccnt++]=va;
            if(cur->r)
            {
                cur=cur->r;
                continue;
            }
            else
            {
TT:             node* parent = cur->p;
                if(parent->l == cur && parent->r)
                {
                    T[cccnt++]=char(2+parent->val%2);
                    cur = parent->r;
                    continue;
                }
                else
                {
                    cur = cur->p;
                    char va=2+cur->val%2;
                    T[cccnt++]=va;
                    if(cur==root) return;
                    goto TT;
                }
            }
        }
    }

};


class Fake{
public:
    int cnt;
    Fake():cnt(0){}
    void operator+=(char s)
    {
        T[cnt++]=s;
    }
};


void ComputePrefix()
{
    //lenP = strlen(P);
    memset(Pi, -1, sizeof(Pi));
    //Pi[0] = -1;
    int k = -1;
    for (int q = 1; q < lenP; q++)
    {
        while (k >= 0 && P[k+1] != P[q]) k = Pi[k];
        if (P[k+1] == P[q]) k++;
        Pi[q] = k;
    }
    return;
}

int CalcT()
{
    int res = 0;
    int q = -1;
    for (int i = 0; i < lenT; i++)
    {
        while (q >= 0 && P[q+1] != T[i]) q = Pi[q];
        if (P[q+1] == T[i]) q++;
        if (q+1 == lenP) res++, q = Pi[q];
    }
    return res;
}

int init(string& pp, int cc)
{
    sprintf(P,"%s", pp.c_str());
    lenP = pp.length();
    lenT = cccnt;

    //REP(i,lenP)cout<<char(P[i]+'0'-2);cout<<'\n';
    //REP(i,lenT)cout<<char(T[i]+'0'-2);
    ComputePrefix();
    int ansans = CalcT();
    cout<<"Case #"<<cc<<": "<<ansans<<'\n';
    return 0;
}



int main()
{

#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    int cases;cin>>cases;
    REP_1(cc,cases)
    {
        int NN;
        cccnt=0;
        cin>>NN;
        Tree tre;
        VI vi(NN);
        REP(i,NN)cin>>vi[i];

        REP(i,NN)
        {
            tre.insert_val(vi[i]);
        }

        tre.dfs();
        string y;cin>>y;
        EACH(it,y)*it-=('0'-2);
        init(y,cc);
    }

    return 0;
}

