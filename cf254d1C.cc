// Time-stamp: <2014-07-19 15:12:57 scinart>
// created at 2014-07-18 21:23:12
// cf2541A.cc

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
#define ALL(x) x.begin(), x.end()

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

#include <cstddef>
//new segment tree.
//debug switchs
//#define DEBUG_QUERY_AID 0x01;
//#define DEBUG_UPDATE_AID 0x02;

template<typename T,typename V>
class IMarktype
{
protected:
    T v;
public:
    virtual operator bool()=0;//if mark exists
    virtual void clear()=0;// clear mark
    virtual IMarktype& merge(const IMarktype& parent)=0;//merge two marks; merge parent to child when pushDown.
    // ;; a.k.a. child.mark.merge(father.mark);
    virtual V withValue(const V& oldValue)=0;//return value of merging mark and value; aka. the value with mark applied.
    virtual ~IMarktype(){};
    const T get()const{return v;}
};

class LL_Mark : public IMarktype<ll,ll>
{
/*
mark 为区间加减，value为区间和。
*/
public:
    LL_Mark(){v=0;}
    LL_Mark(ll i){v=i;}
    operator bool(){return v;}
    void clear(){v=0;}
    IMarktype<ll,ll>& merge(const IMarktype<ll,ll>& parent){v+=parent.get(); return *this;}
    ll withValue(const ll& oldValue){return v+oldValue;}
    static bool MERGABLE;
    static bool OK_WITH_BOSS_WHEN_SET_MARK;
};
bool LL_Mark::MERGABLE = true;
bool LL_Mark::OK_WITH_BOSS_WHEN_SET_MARK = true;


template<typename T, typename Marktype>
class SegmentTree
{//zero indexed left close right open tree.
    typedef T (*fnmerge)(const T& a,const T& b);
    typedef T (*fninit)(int l);
public:
    struct Node
    {
        int l;
        int r;
        Marktype mark;
        T value;
        void setNode(int l_, int r_,const T& value_){l=l_;r=r_;value=value_;}
    };

    //¡important! Node[l,r) stores in the in-order index(zero indexed) of nedo.
    Node* nedo; //Nedo is Node
    fnmerge merge; //how two nodes merge
    fninit init; //init(0) is first segment's value, etc.

    SegmentTree(size_t N,
                fninit init_,
                fnmerge merge_):query_head(indexof(0,N))
    { //length of Segment.
        nedo = new Node[2*N-1];
        merge = merge_;
        init = init_;
        build_aid(0,N);
    }
    ~SegmentTree(){ delete[] nedo; }
    inline int indexof(int l,int r)
    {//Scinart way, my way.
        return (l-1+r)-((r-l==1)?0:((l+r)&1));
    }
    T query(int l,int r)
    {
        return query_aid(query_head,l,r);
    }
    void update(int l,int r,Marktype mark)
    {
        update_aid(query_head, l, r, mark);
    }
private:
    const int query_head;
    void build_aid(int l,int r)
    {//uses init
        if(l+1<r)
        {//if not elementary
            build_aid(l,(l+r)/2);
            build_aid((l+r)/2,r);
            nedo[indexof(l,r)].setNode(l,
                                       r,
                                       merge(nedo[indexof(l,(l+r)/2)].value,
                                             nedo[indexof((l+r)/2,r)].value));
        }
        else
        {
            nedo[indexof(l,r)].setNode(l,r,init(l));
        }
    }
    void pushDown(int which_node)
    {
        /*if this node is marked then pushDown and clear the mark.*/
        Marktype& mark = nedo[which_node].mark;
        if(mark)
        {
            int l=nedo[which_node].l;
            int r=nedo[which_node].r;
            if(r-l>1)
            {//not leaf, push down Mark;
                if(Marktype::MERGABLE)
                {
                    (nedo[indexof(l,(l+r)/2)]).mark.merge(mark);
                    (nedo[indexof((l+r)/2,r)]).mark.merge(mark);
                }
                else
                {
                    pushDown(indexof(l,(l+r)/2));
                    pushDown(indexof((l+r)/2,r));
                    (nedo[indexof(l,(l+r)/2)]).mark = mark;
                    (nedo[indexof((l+r)/2,r)]).mark = mark;
                }

            }
            nedo[which_node].value = (nedo[which_node].value) + (r-l)*mark.get();
            nedo[which_node].mark.clear();
        }
    }
    T query_aid(int which_node, int l,int r)
    {
        pushDown(which_node);
        int lbound = nedo[which_node].l;
        int rbound = nedo[which_node].r;
#ifdef DEBUG_QUERY_AID
        printf("query_aid [%d..%d) in [%d..%d).\n",l,r, lbound, rbound);
#endif
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            return nedo[which_node].value;
        }
        else
        {
            T ans;
            int mid = (lbound+rbound)/2;
            if(l<mid)
            {
                ans = query_aid(indexof(lbound,mid),l,r);
                if(r>mid)
                {
                    ans = merge(ans,query_aid(indexof(mid,rbound),l,r));
                }
            }
            else
            {
                ans = query_aid(indexof(mid,rbound),l,r);
            }
            return ans;
        }
    }
    void update_aid(int which_node, int l,int r,const Marktype& mark)
    {
        int lbound = nedo[which_node].l;
        int rbound = nedo[which_node].r;
#ifdef DEBUG_UPDATE_AID
        printf("updating [%d..%d) in [%d..%d) with mark %d\n",l,r, lbound, rbound, mark.get());
#endif
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            nedo[which_node].mark.merge(mark);
        }
        else
        {
            if(Marktype::OK_WITH_BOSS_WHEN_SET_MARK)
            {
                //nothing
            }
            else
            {
                pushDown(which_node);
            }
            int mid = (lbound+rbound)/2;
            if(l<mid)
            {
                update_aid(indexof(lbound,mid),l,r,mark);
                if(r>mid)
                {
                    update_aid(indexof(mid,rbound),l,r,mark);
                }
            }
            else
            {
                update_aid(indexof(mid,rbound),l,r,mark);
            }
            // this roll back is required.
            pushDown(indexof(lbound, mid));
            pushDown(indexof(mid, rbound));
            nedo[which_node].value = merge(nedo[indexof(lbound,mid)].value, nedo[indexof(mid, rbound)].value);
        }
#ifdef DEBUG_UPDATE_AID
#endif
    }

};

ll init_(int){return 0;}
ll merge_(const ll& a,const ll& b){return a+b;}


int main()
{
    std::ios::sync_with_stdio(false);

    // SegmentTree<LL, LL_Mark> sttest(10,init_,merge_);
    // sttest.update(0,5,1);
    // sttest.update(5,10,3);
    // sttest.update(3,7,10);
    // cout<<sttest.query(0,5)<<'\n';
    // return 0;

    int n,m;

    cin>>n>>m;

    map<int,int> mii;

    REP_1(i,n)
    {
        mii[i]=i;
    }

    SegmentTree<LL, LL_Mark> st(n+1,init_,merge_);

    REP(temp_214710,m)
    {
        int type;
        cin>>type;
        if(type==1)
        {
            int b,e,c;
            cin>>b>>e>>c;

            if((--mii.end())->first < b)
            {
                //b 和 e 都在结尾
                int old_val = mii.rbegin()->second;
                if(c==old_val)
                    continue;
                if(e==n)
                {
                    //e 在最尾
                    mii[b]=c;
                    st.update(b,e+1,abs(old_val-c));
                }
                else
                {
                    mii[b]=c;
                    mii[e+1]=old_val;
                    st.update(b,e+1,abs(old_val-c));
                }
            }
            else
            {
                {
                    map<int,int>::iterator bit = --mii.upper_bound(b);
                    map<int,int>::iterator eit = --mii.upper_bound(e);
                    int old_val = bit->second;
                    if(bit==eit)
                    {
                        // b 和 e 在一起
                        if(c==old_val)
                            continue;
                        if(e+1==mii.upper_bound(e)->first)
                        {//e在区间最尾
                            mii[b]=c;
                            st.update(b,e+1,abs(old_val-c));
                        }
                        else
                        {
                            mii[b]=c;
                            mii[e+1]=old_val;
                            st.update(b,e+1,abs(old_val-c));
                        }
                    }
                    else
                    {
                        if(old_val == c)
                        {
                            bit++;
                            b=bit->first;
                        }
                        else
                        {
                            st.update(b,((++bit)->first), abs(old_val-c));
                            mii[b]=c;
                            bit=mii.find(b);bit++;
                        }
                        while(bit!=eit)
                        {
                            int key_to_erase = bit->first;
                            bit++;
                            st.update(key_to_erase, bit->first, abs(mii[key_to_erase]-c));
                            mii.erase(key_to_erase);
                        }

                        map<int,int>::iterator enext = mii.upper_bound(e);
                        if(e==n || (enext!=mii.end() && e+1==enext->first))
                        {//e在区间最尾
                            st.update(bit->first,e+1,abs(bit->second-c));
                            mii.erase(bit);
                        }
                        else
                        {
                            int old___ = bit->second;
                            st.update(bit->first,e+1,abs(bit->second-c));
                            mii.erase(bit);
                            mii[e+1]=old___;
                        }
                        map<int,int>::iterator ori_bit = mii.find(b);
                        if(ori_bit != mii.begin() && ((--ori_bit)->second == c))
                        {
                            mii.erase(b);
                        }
                    }
                }
            }

        }
        else
        {
            int b,e;
            cin>>b>>e;

            cout<<st.query(b,e+1)<<'\n';
        }


        // EACH(it,mii)
        // {
        //     cout<<it->first<<"->"<<it->second<<'\n';
        // }
        // REP_1(j,n)
        // {
        //     cout<<st.query(j,j+1)<<' ';
        // }
        // cout<<'\n';


    }

    return 0;
}
