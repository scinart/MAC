//从零开始 左开右闭
typedef int Valtype;
typedef int Marktype;

const int maxn;
Valtype VAL[2*maxn];
Valtype INPUT[maxn];
int L[2*maxn];
int R[2*maxn];
Marktype MARK[2*maxn];

/*mark为区间加减，val为区间和
inline void mergeMark(Marktype& son, const Marktype& father){son+=father;}
inline void setMark(Marktype& where, const Marktype& what){where=what;}
inline Valtype mergeValVal(const Valtype& a,const Valtype& b){return a+b;}
inline const Valtype withValue(const Marktype& mark, const Valtype& val, int l, int r){return val+(r-l)*mark;}
inline void clearMark(Marktype& m){m=0;}
const bool MERGABLE = true;
*/

/* mark为区间重置，val为最大值
inline void mergeMark(Marktype& son, const Marktype& father){son=father;}
inline void setMark(Marktype& where, const Marktype& what){where=what;}
inline Valtype mergeValVal(const Valtype& a,const Valtype& b){return max(a,b);}
inline const Valtype withValue(const Marktype& mark, const Valtype& val, int l, int r){return mark;}
inline void clearMark(Marktype& m){m=0;}
const bool MERGABLE = true;
*/

/* mark为区间重置，val为区间和
inline void mergeMark(Marktype& son, const Marktype& father){son=father;}
inline void setMark(Marktype& where, const Marktype& what){where=what;}
inline Valtype mergeValVal(const Valtype& a,const Valtype& b){return a+b;}
inline const Valtype withValue(const Marktype& mark, const Valtype& val, int l, int r){return (r-l)*mark;}
inline void clearMark(Marktype& m){m=0;}
const bool MERGABLE = true;
*/

class SegmentTree
{//zero indexed left close right open tree.
public:
    SegmentTree(size_t N):query_head(indexof(0,N))
    { //length of Segment.
        // suppose node already has its value.
        build(0,N);
    }
    Valtype query(int l,int r)
    {
        return query_aid(query_head, l,r);
    }
    void update(int l,int r,const Marktype& mark)
    {
        update_aid(query_head, l, r, mark);
    }
private:
    const int query_head;
    inline int indexof(int l,int r)
    {//Scinart way, my way.
        return (l-1+r)-((r-l==1)?0:((l+r)&1));
    }
    void build(int l,int r)
    {
        int ind = indexof(l,r);
        if(l+1<r)
        {//if not elementary
            build(l,(l+r)>>1);
            build((l+r)>>1,r);
            L[ind]=l;
            R[ind]=r;
            VAL[ind]=mergeValVal(VAL[indexof(l,(l+r)/2)],VAL[indexof((l+r)/2,r)]);
        }
        else
        {
            L[ind]=l;
            R[ind]=r;
            VAL[ind]=INPUT[l];
        }
    }
    void pushDown(int which_node)
    {
        /*if this node is marked then pushDown and clear the mark.*/
        const Marktype& mark=MARK[which_node];
        if(mark)
        {
            int l=L[which_node];
            int r=R[which_node];
            if(r-l>1)
            {//not leaf, push down Mark;
                if(MERGABLE)
                {
                    mergeMark(MARK[indexof(l,(l+r)/2)], (mark));
                    mergeMark(MARK[indexof((l+r)/2,r)], (mark));
                }
                else
                {
                    pushDown(indexof(l,(l+r)/2));
                    pushDown(indexof((l+r)/2,r));
                    setMark(MARK[indexof(l,(l+r)/2)], (mark));
                    setMark(MARK[indexof((l+r)/2,r)], (mark));
                }

            }
            VAL[which_node] = withValue(mark,VAL[which_node], l,r);
            clearMark(MARK[which_node]);
        }
    }
    Valtype query_aid(int which_node, int l,int r)
    {
        pushDown(which_node);//necessary.
        int lbound = L[which_node];
        int rbound = R[which_node];
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            return VAL[which_node];
        }
        else
        {
            Valtype ans;
            int mid = (lbound+rbound)>>1;
            if(l<mid)
            {
                ans = query_aid(indexof(lbound,mid),l,r);
                if(r>mid)
                {
                    ans = mergeValVal(ans,query_aid(indexof(mid,rbound),l,r));
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
        int lbound = L[which_node];
        int rbound = R[which_node];
        if(l<=lbound && rbound<=r)
        {// l和r包含这个node
            if(MERGABLE)
            {
                mergeMark(MARK[which_node],(mark));
            }
            else
            {
                pushDown(which_node);
                mergeMark(MARK[which_node],(mark));
            }
        }
        else
        {
            pushDown(which_node);
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
            VAL[which_node] = mergeValVal(VAL[indexof(lbound,mid)], VAL[indexof(mid, rbound)]);
        }
    }
};

