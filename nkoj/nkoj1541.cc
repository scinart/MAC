//nkoj1541.cc
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <cstring>
#include <list>
#include <map>
#include <deque>
#include <cstddef>
using namespace std;
//debug switchs
//#define DEBUG_QUERY_AID 0x01;
//#define DEBUG_UPDATE_AID 0x02;

// Class of Pairs

int fnmerge(const int &a,const int& b)
{
    return a+b;
}
int fninit(int)
{
    return 1;
}
int fnmark1(bool)
{
    return 0;
}

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
    fnmerge merge; //how two nodes merge
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
        /*if this node is marked then pushDown and clear the mark.*/
        Marktype& mark = nedo[which_node].mark;
        if(mark)
        {
            int l=nedo[which_node].l;
            int r=nedo[which_node].r;
            if(r-l>1)
            {//not leaf, push down Mark;
                pushDown(indexof(l,(l+r)/2));
                pushDown(indexof((l+r)/2,r));

                (nedo[indexof(l,(l+r)/2)]).mark = mark;
                (nedo[indexof((l+r)/2,r)]).mark = mark;
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
#endif
    }

};

int main()
{
    int L,M;
    while(cin>>L>>M)
    {
        SegmentTree<int,bool> si(L+1,fnmerge,fninit,fnmark1);
        while(M--)
        {
            int a,b;
            cin>>a>>b;
            si.update(a,b+1,true);
        }
        cout<<si.query(0,L+1)<<endl;
    }
}
