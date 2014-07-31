//nkoj 2219
#include <iostream>
#include <cstdio>
#include <climits>
#include <cstddef>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

/*
现有一长为n的整数列：d1, d2, d3, ......, dn。
求满足下列条件的最长子序列（子序列指连续的若干个数）的长度：
该子序列中最大值与最小值之差不超过k
*/

template<typename T>
class PII
{ // Pair of int, short, long, etc.
public:
    T first;
    T second;
    PII (){}
    PII (T a, T b){
        first = a;
        second = b;
    }
    PII& operator=(const PII& rhs)
    {
        first = rhs.first;
        second = rhs.second;
        return *this;
    }
    bool operator==(const PII& rhs)const
    {
        return first==rhs.first && second == rhs.second;
    }
    bool operator<(const PII& rhs)const
    {
        return first<rhs.first || (first==rhs.first && second < rhs.second);
    }
};

template<typename T>
/*public final*/ class SegmentTree
{//zero indexed left close right open tree.
public:
    struct Node
    {
        int l;
        int r;
        int mark;
        T value;
        void setNode(int l_, int r_,const T& value_){l=l_;r=r_;value=value_;}
    };

    typedef T (*fnmerge)(const T& a,const T& b);
    typedef T (*fninit)(int l);

    //¡important! Node[l,r) stores in the in-order index(zero indexed) of nedo.
    Node* nedo; //Nedo is Node
    fnmerge merge; //how two node merges
    fninit init; //init(0) is first segment's value, etc.
    int query_head;

    SegmentTree(size_t N, fnmerge merge_, fninit init_)
    { //length of Segment.
        nedo = new Node[2*N-1];
        query_head = indexof(0,N);
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
private:
    void build_aid(int l,int r)
    {//uses init
        if(l+1<r)
        {//if not elementary
            build_aid(l,(l+r)/2);
            build_aid((l+r)/2,r);
            nedo[indexof(l,r)].setNode(l,r,merge(nedo[indexof(l,(l+r)/2)].value,
                                                 nedo[indexof((l+r)/2,r)].value));
        }
        else
        {
            nedo[indexof(l,r)].setNode(l,r,init(l));
        }
    }
    T query_aid(int which_node, int l,int r)
    {
        int lbound = nedo[which_node].l;
        int rbound = nedo[which_node].r;
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

};

typedef PII<int> Pii;
typedef SegmentTree<Pii> STree;

Pii piimerge(const Pii& a, const Pii& b)
{
    return Pii(min(a.first, b.first), max(a.second, b.second));
}

int* arr;
Pii piiinit(int l)
{
    return Pii(arr[l], arr[l]);
}

int main()
{
    freopen("nkoj2219.in", "r", stdin);
    int n,k;
    while(scanf("%d %d",&n,&k) != EOF)
    {
        arr = new int[n];
        for(int i=0; i<n; i++)
        {
            scanf("%d",&arr[i]);
        }
        STree st(n, piimerge, piiinit);

        int curlen=1;
        Pii query;

        for(int i=1; i<n; i++)
        {
            query = st.query(i-curlen,i+1);
            if(query.second-query.first<=k)
            {
                curlen++;
            }
        }

        printf("%d\n",curlen);
        delete[] arr;
    }
}





// Local Variables:
// eval:(progn (hs-minor-mode t) (let ((hs-state '((968 1116 hs) (1659 1659 hs) (1949 2329 hs) (2381 3043 hs))) (the-mark 'scinartspecialmarku2npbmfydfnwzwnpywxnyxjr)) (dolist (i hs-state) (if (car i) (progn (goto-char (car i)) (hs-find-block-beginning) (hs-hide-block-at-point nil nil))))) (goto-char 1892) (recenter-top-bottom))
// End:
