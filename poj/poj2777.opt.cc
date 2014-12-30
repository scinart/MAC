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
// #define DEBUG_QUERY_AID 0x01;
// #define DEBUG_UPDATE_AID 0x02;

typedef int ssc;
typedef signed char sc;

template<typename T, typename Marktype>
class SegmentTree
{//zero indexed left close right open tree.
public:
    struct Node
    {
        int l;
        int r;
        Marktype mark;
        T value;
        void setNode(int l_, int r_){l=l_;r=r_;value=ssc(1);}
    };

    //¡important! Node[l,r) stores in the in-order index(zero indexed) of nedo.
    Node* nedo; //Nedo is Node

    SegmentTree(size_t N):query_head(indexof(0,N))
    { //length of Segment.
        nedo = new Node[2*N-1];
        build_aid(0,N);
    }
    ~SegmentTree(){ delete[] nedo;
    }
    inline int indexof(int l,int r)
    {//Scinart way, my way.
        return (l-1+r)-((r-l==1)?0:((l+r)&1));
    }
    T query(int l,int r)
    {
        return query_aid(query_head,l,r);
    }
    void update(int l,int r,const Marktype& mark)
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
                                       r);
        }
        else
        {
            nedo[indexof(l,r)].setNode(l,r);
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
                (nedo[indexof(l,(l+r)/2)]).mark=(mark);
                (nedo[indexof((l+r)/2,r)]).mark=(mark);
            }
            nedo[which_node].value = (1<<(mark-1));
            mark=0;
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
                    ans |= query_aid(indexof(mid,rbound),l,r);
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
            //TODO: Mergable seems meaningless.
            nedo[which_node].mark=(mark);
        }
        else
        {
            int mid = (lbound+rbound)/2;
            int ilm=indexof(lbound, mid);
            int imr=indexof(mid,rbound);
            pushDown(which_node);
            if(l<mid)
            {
                update_aid(ilm,l,r,mark);
                if(r>mid)
                {
                    update_aid(imr,l,r,mark);
                }
            }
            else
            {
                update_aid(imr,l,r,mark);
            }
            // this roll back is required.
            pushDown(indexof(lbound, mid));
            pushDown(indexof(mid, rbound));
            nedo[which_node].value = (nedo[ilm].value | nedo[imr].value);
        }
    }
};

unsigned int Count(unsigned int m)
{ //from des
    unsigned int ans = 0;
    while(m > 0)
    {
        m -= (m & -m);
        ans++;
    }
    return ans;
}

int main()
{
    //should tle
    std::ios::sync_with_stdio(false);
    size_t L,T,O;
    while(cin>>L>>T>>O)
    {
        SegmentTree<ssc,int> segt(L);
        char command;
        int a,b,c,d,e;
        while(O--)
        {
            cin>>command>>a>>b;
            d=min(a,b);
            e=max(a,b);
            if(command=='C')
            {
                cin>>c;
                segt.update(d-1,e,c);
            }
            else
            {
                cout<<Count(segt.query(d-1,e))<<'\n';
            }
        }
    }
    return 0;
}
