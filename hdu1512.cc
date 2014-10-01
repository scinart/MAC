// Time-stamp: <2014-10-01 16:08:56 scinart>
// created at 2014-10-01 15:45:52
// hdu1512.cc

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


// 杭电only
inline int ri(){int x;scanf("%d", &x);return x;}
inline double rd(){double x;scanf("%lf", &x);return x;}
#ifdef ONLINE_JUDGE
inline long long rll(){long long x;scanf("%I64d", &x);return x;}
#else
inline long long rll(){long long x;scanf("%lld", &x);return x;}
#endif

template <typename T>
void checkmin(T& a,const T& b){if(b<a)a=b;}
template <typename T>
void checkmax(T& a, const T& b){if(b>a)a=b;}
#define TT template<class T, class Op>
template<class T, class Op = less<T> >
struct Node {
    T key;
    int dist;
    Node<T, Op> *L;
    Node<T, Op> *R;
    Node():L(NULL),R(NULL){}
    Node(T k,int d=0):key(k),dist(d),L(NULL),R(NULL){}
};
TT void merge(Node<T, Op>* &A, Node<T, Op>* &B)
{
    if(A==NULL) {swap(A,B);return;}
    if(B==NULL) return;
    if(Op()(B->key,A->key))
        swap(A,B);
    merge(A->R,B);
    if((A->L==NULL) || (A->R!=NULL && A->R->dist>A->L->dist))
        swap(A->R,A->L);
    if(A->R==NULL)A->dist=0;
    else A->dist=A->R->dist+1;
    B=NULL;
}
TT void destroy(Node<T, Op>* &tree)
{
    if(tree->L)destroy(tree->L);
    if(tree->R)destroy(tree->R);
    delete tree;
    tree=NULL;
}
TT class LeftishTree;
TT void merge(LeftishTree<T, Op>&, LeftishTree<T, Op>&);
template<class T, class Op = less<T> >
class LeftishTree
{
    Node<T, Op>* root;
    size_t SZ;
    LeftishTree(const LeftishTree& rhs);
public:
    LeftishTree& operator=(LeftishTree& rhs){if(this==&rhs)return *this;clear();root=rhs.root;rhs.root=NULL;return *this;} //transfer ownership.
    T top() const { return root->key; }
    bool empty() const { return root == NULL; }
    size_t size() const { return SZ; }
    friend void merge<>(LeftishTree<T, Op>&, LeftishTree<T, Op>&);
    void pop();
    void insert(T val);
    LeftishTree():root(NULL),SZ(0){}
    LeftishTree(const T& elem):SZ(1){root=new Node<T,Op>(elem);}
    void clear(){if(root)destroy(root);SZ=0;}
    ~LeftishTree(){clear();}
};
TT void merge(LeftishTree<T, Op>& A, LeftishTree<T, Op>& B) {
    merge(A.root, B.root);
    A.SZ += B.SZ;
    B.SZ = 0;
}
TT void LeftishTree<T, Op>::insert(T val) {
    Node<T, Op>* newTree = new Node<T, Op>(val);
    merge(root, newTree);
    ++SZ;
}
TT void LeftishTree<T, Op>::pop() {
    merge(root->L, root->R);
    Node<T, Op>* newRoot = root->L;
    delete root;
    root = newRoot;
    --SZ;
}


namespace DSET {

const int MAXN = 100010;
int pre[MAXN],Rank[MAXN];
LeftishTree<int, greater<int> > tres[MAXN];
int degree;
void INIT(int n)
{
    degree=n;
    REP_1(i,n) pre[i]=i, Rank[i]=1;
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
int UNION(int a,int b)
{
    a=FIND(a);
    b=FIND(b);
    if(a==b) return a;
    degree--;
    if(Rank[a]>=Rank[b])
        return pre[b]=a, Rank[a]+=Rank[b], a;
    else
        return pre[a]=b, Rank[b]+=Rank[a], b;
}

}

int main()
{

#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif

    int N,M;
    while(scanf("%d", &N)!=EOF)
    {
        DSET::INIT(N);
        REP_1(i,N)
        {
            DSET::tres[i].insert(ri());
        }
        M=ri();
        REP(i,M)
        {
            int x=DSET::FIND(ri());
            int y=DSET::FIND(ri());
            if(x==y)
            {
                puts("-1");
            }
            else
            {
                DSET::tres[x].insert(DSET::tres[x].top()/2);
                DSET::tres[x].pop();
                DSET::tres[y].insert(DSET::tres[y].top()/2);
                DSET::tres[y].pop();
                int un = DSET::UNION(x, y);
                merge(DSET::tres[x],DSET::tres[y]);
                DSET::tres[un]=DSET::tres[x];
                printf("%d\n",(DSET::tres[un].top()));
            }
        }
        REP_1(i,N)DSET::tres[i].clear();
    }
}


