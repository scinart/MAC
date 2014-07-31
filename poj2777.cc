//poj 2777
#include <iostream>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;
/*
长度为L的线段

1. "C A B C" Color the board from segment A to segment B with color C.
2. "P A B" Output the number of different colors painted between segment A and segment B (including).

颜色有color 1, color 2, ... color T.
开始的时候线段为color 1.

Input
First line of input contains L 长度 (1 <= L <= 100000), T 颜色个数 (1 <= T <= 30) and O 操作个数. (1 <= O <= 100000).
Here O denotes the number of operations. Following O lines,
each contains "C A B C" or "P A B" (here A, B, C are integers, and A may be larger than B) as an operation defined previously.

Output
Ouput results of the output operation in order, each line contains a number.
*/

#include <cstddef>
//debug switchs
//#define DEBUG_QUERY_AID 0x01;
//#define DEBUG_UPDATE_AID 0x02;

template<typename T, typename Marktype>
class SegmentTree
{//zero indexed left close right open tree.
    typedef T (*fnmerge)(const T& a,const T& b);
    typedef T (*fninit)(int l);
    typedef T (*fnmark1)(Marktype m);
    typedef T (*fnmark2)(Marktype m, const T& oldValue);
public:
    struct Node
    {
        int l;
        int r;
        Marktype mark;
        T value;
        void setNode(int l_, int r_,Marktype mark_, const T& value_){l=l_;r=r_;mark=mark_;value=value_;}
    };

    //¡important! Node[l,r) stores in the in-order index(zero indexed) of nedo.
    Node* nedo; //Nedo is Node
    fnmerge merge; //how two nodes merge, merge should be very fast.
    fninit init; //init(0) is first segment's value, etc.
    fnmark1 fn_mark1;
    fnmark2 fn_mark2;

    SegmentTree(size_t N, fnmerge merge_, fninit init_, fnmark1 fn_mark1_=NULL, fnmark2 fn_mark2_=NULL):query_head(indexof(0,N))
    { //length of Segment.
        nedo = new Node[2*N-1];
        merge = merge_;
        init = init_;
        fn_mark1 = fn_mark1_;
        fn_mark2 = fn_mark2_;
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
                                       Marktype(0),
                                       merge(nedo[indexof(l,(l+r)/2)].value,
                                             nedo[indexof((l+r)/2,r)].value));
        }
        else
        {
            nedo[indexof(l,r)].setNode(l,r,Marktype(0),init(l));
        }
    }
    void pushDown(int which_node)
    {
        /**/
        Marktype& mark = nedo[which_node].mark;
        if(mark)
        {
            int l=nedo[which_node].l;
            int r=nedo[which_node].r;
            if(r-l>1)
            {//not leaf, push down Mark;
                (nedo[indexof(l,(l+r)/2)]).mark = mark;
                (nedo[indexof((l+r)/2,r)]).mark = mark;
                pushDown(indexof(l,(l+r)/2));
                pushDown(indexof((l+r)/2,r));
            }
            if(fn_mark1)
            {
                nedo[which_node].value = fn_mark1(mark);
            }
            else if(fn_mark2)
            {
                nedo[which_node].value = fn_mark2(mark, nedo[which_node].value);
            }
            nedo[which_node].mark = 0;
        }
    }
    T query_aid(int which_node, int l,int r)
    {
        pushDown(which_node);
        int lbound = nedo[which_node].l;
        int rbound = nedo[which_node].r;
#ifdef DEBUG_QUERY_AID
        printf("query_aid [%d %d) with [%d %d).\n", lbound, rbound, l ,r);
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
    void update_aid(int which_node, int l,int r,Marktype mark)
    {
        int lbound = nedo[which_node].l;
        int rbound = nedo[which_node].r;
#ifdef DEBUG_UPDATE_AID
        printf("updating [%d..%d) with mark %d\n", lbound, rbound, mark);
#endif
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            nedo[which_node].mark = mark;
        }
        else
        {
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
            pushDown(indexof(lbound, mid));
            pushDown(indexof(mid, rbound));
            // this roll back is required.
            nedo[which_node].value = merge(nedo[indexof(lbound,mid)].value, nedo[indexof(mid, rbound)].value);
        }
#ifdef DEBUG_UPDATE_AID
        printf("and now [%d..%d) has mark: %d with size %d\n", lbound, rbound, nedo[which_node].mark, nedo[which_node].value.size());
#endif
    }

};

// typedef T (*fnmerge)(const T& a,const T& b);
// typedef T (*fninit)(int l);
// typedef T (*fnmark1)(int m);
// typedef T (*fnmark2)(int m, const T& oldValue);
typedef set<short> ssh;
typedef SegmentTree<ssh,int> ssst;

ssh fnmerge(const ssh& a, const ssh& b)
{
    ssh s = a;
    s.insert(b.begin(), b.end());
    return s;
}
ssh fninit(int l)
{
    ssh a;
    a.insert(1);
    return a;
}
ssh fnmark(int m)
{
    ssh a;
    a.insert(m);
    return a;
}

int main()
{
    //should tle
#ifndef ONLINE_JUDGE
    //    freopen("poj2777.in.big", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    size_t L,T,O;
    while(cin>>L>>T>>O)
    {
        ssst segt(L,fnmerge, fninit, fnmark);

        char command;
        int a,b,c,d,e;
        while(O--)
        {
            cin>>command;
            switch(command)
            {
              case 'C':
              {
                  cin>>a>>b>>c;
                  d=min(a,b);
                  e=max(a,b);
                  segt.update(d-1,e,c);
                  break;
              }
              case 'P':
              {
                  cin>>a>>b;
                  d=min(a,b);
                  e=max(a,b);
                  cout<<segt.query(d-1,e).size()<<'\n';
                  break;
              }
            }
        }
    }
}
