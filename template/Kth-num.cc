#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1e5;
const int LAYERS = 17+1; // \ceil{log_2^{MAXN}}+1
int n,INPUT[MAXN],M[LAYERS][MAXN];
inline int depth(unsigned x){return 31-__builtin_clz(x+1);}
int L[1<<LAYERS],first[1<<LAYERS];//length of node[i] and begin pos of node[i]
void generate(int node=0, int beg=0, int end=n){
    int d=depth(node);
    L[node] = end-beg;
    first[node] = beg;
    if(beg+1==end) M[d][beg] = INPUT[beg];
    else{
        int mid = (beg+end)/2;
        generate(2*node+1,beg,mid);
        generate(2*node+2,mid,end);
        int sz1 = mid-beg;
        int sz2 = end-mid;
        int s1 = beg;
        int s2 = mid;
        int cnt1 = 0,cnt2 = 0;
        while(cnt1<sz1 && cnt2<sz2){
            if(M[d+1][s1+cnt1]<M[d+1][s2+cnt2]){
                M[d][beg+cnt1+cnt2] = M[d+1][s1+cnt1];
                ++cnt1;
            }else{
                M[d][beg+cnt1+cnt2] = M[d+1][s2+cnt2];
                ++cnt2;
            }
        }
        if(cnt1==sz1){
            while(cnt2!=sz2){
                M[d][beg+cnt1+cnt2] = M[d+1][s2+cnt2];
                ++cnt2;
            }
        }else{
            while(cnt1!=sz1){
                M[d][beg+cnt1+cnt2] = M[d+1][s1+cnt1];
                ++cnt1;
            }
        }
    }
}

int num,ind[LAYERS<<1];
void get_nodes(int node, int beg, int end, int qb, int qe, bool inrec=false){
    if(!inrec) num=0;
    if(beg>=qe || end<=qb) return;
    if(beg>=qb && end<=qe)
        ind[num++] = node;
    else
    {
        int mid = (beg+end)/2;
        get_nodes(2*node+1,beg,mid,qb,qe,true);
        get_nodes(2*node+2,mid,end,qb,qe,true);
    }
}
int count_idx(int idx, int val){
    int d = depth(idx),s = first[idx],l = L[idx];
    if(M[d][s]>val) return 0;
    int low = 0,high = l;
    while(low+1<high){
        int mid = (low+high)/2;
        if(M[d][s+mid]<=val) low = mid;
        else high = mid;
    }
    if(M[d][s+low]<=val)low++;
    return low;
}
int get_Kth(int beg, int end, int k){
    get_nodes(0,0,n,beg,end);
    int low = 0,high = n;
    while(low+1<high){
        int mid = (low+high)/2;
        int cnt = 0;
        for(int i = 0;i<num;++i)
            cnt += count_idx(ind[i],M[0][mid]);
        if(cnt<k) low = mid;
        else high = mid;
    }
    return M[0][low+1];
}
int range_lte(int beg, int end, int val)
{
    get_nodes(0,0,n,beg,end);
    int cnt = 0;
    for(int i = 0;i<num;++i)
        cnt += count_idx(ind[i],val);
    return cnt;
}
int main(){
    int CC;scanf("%d", &CC);
    for(int i=0; i<CC; i++)
    {
        int m;
        scanf("%d %d",&n,&m);
        for(int i = 0;i<n;++i) scanf("%d",&INPUT[i]);
        generate();
        printf("Case %d:\n", i+1);
        for(int i = 0,b,e,k;i<m;++i){
            scanf("%d %d %d",&s,&e,&k);
            printf("%d\n",range_lte(b-1,e,k));
        }
    }
    return 0;
}
