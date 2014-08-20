#include <cstdio>
const int maxn = 200100;
typedef int TreapType;
struct TreapNode {
    int left, right, sz, fa, we, prio;  //left, right, size, father, weight, prioity.
    TreapType val;
};
template <typename T> inline int jud(T a, T b){
    return (-1)+(a==b)+(a>b)+(a>b);
}

unsigned lfsrrand(void){
    static unsigned lfsr = 0xDeaDBeeFu;  // my favorite music player.
    for(int i=0;i<31;i++) if(lfsr&1) lfsr>>=1,lfsr^=0x48000000u; else lfsr>>=1;
    return lfsr;
}
// 不用初始化。
TreapNode arr[maxn];
int nxt[maxn];
class Treap {
public:
    int sz, root, treap_head, maxl;
    Treap():sz(0),root(-1),treap_head(0),maxl(0){}
    TreapNode* lower_bound(const TreapType& val, int no=-1)
    {
        if(no==-1)no=root;
        if(arr[no].val==val)
            return &arr[no];
        else if(val>arr[no].val)
            if(arr[no].right!=-1)
                return lower_bound(val,arr[no].right);
            else
                return NULL;
        else if(arr[no].left!=-1)
        {
            TreapNode* rec = lower_bound(val,arr[no].left);
            if(rec!=NULL)return rec;
            else return &arr[no];
        }
        else return &arr[no];
    }
    TreapNode* kth(int k, int no = -1)
    {
        if(no==-1) no=root;
        int left=arr[no].left;
        if(left!=-1)
        {
            if(arr[left].sz>=k)
            {
                return kth(k,left);
            }
            else k-=arr[left].sz;
        }
        if(arr[no].we>=k)
            return &arr[no];
        else
            k-=arr[no].we;
        if(arr[no].right!=-1)
        {
            return kth(k,arr[no].right);
        }
        else return NULL;
    }
    int getlt(TreapType val,bool orequal = false, int no = -1) {
        if(no == -1) no = root;
        int ans=0;
        if(sz == 0);
        else if(arr[no].val == val) {
            if (arr[no].left != -1) ans=arr[arr[no].left].sz;
            ans+=(orequal?arr[no].we:0);
        }
        else if(arr[no].val > val) {
            if(arr[no].left != -1) ans=getlt(val, orequal, arr[no].left);
        }
        else {
            if(arr[no].right != -1) ans=getlt(val, orequal, arr[no].right) - arr[arr[no].right].sz;
            ans+=arr[no].sz;
        }
        return ans;
    }
    void insert(TreapType val) {
        int ranmaxl = maxl;
        sz++;
        arr[treap_head].prio = lfsrrand();
        arr[treap_head].left = arr[treap_head].right = arr[treap_head].fa = -1;
        if(treap_head == maxl) {
            maxl++;
            nxt[treap_head] = maxl;
        }
        arr[treap_head].val = val;
        if(sz == 1) {
            root = treap_head;
            arr[treap_head].sz = 1;
            arr[treap_head].we = 1;
            treap_head = nxt[treap_head];
            return;
        }
        int no = root;
        while(no != -1) {
            if(arr[no].val == arr[treap_head].val) break;
            arr[treap_head].fa = no;
            if(arr[no].val < arr[treap_head].val) no = arr[no].right;
            else no = arr[no].left;
        }
        if(no != -1) {
            arr[no].we++;
            maxl = ranmaxl;
            relaxtofa(no);
            return;
        }
        arr[treap_head].we = 1; arr[treap_head].sz = 1;
        if(arr[treap_head].val < arr[arr[treap_head].fa].val) arr[arr[treap_head].fa].left = treap_head;
        else arr[arr[treap_head].fa].right = treap_head;
        while(arr[treap_head].fa != -1 && arr[treap_head].prio > arr[arr[treap_head].fa].prio) {
            if(arr[treap_head].val < arr[arr[treap_head].fa].val) right_rot(treap_head);
            else left_rot(treap_head);
        }
        if(arr[treap_head].fa == -1) root = treap_head;
        relaxtofa(treap_head);
        treap_head = nxt[treap_head];
    }
    void del(TreapType val) {
        if(sz == 0) return;
        int no = root;
        while(no != -1) {
            if(arr[no].val == val) break;
            if(arr[no].val > val) no = arr[no].left;
            else no = arr[no].right;
        }
        if(no == -1) return;
        sz--;
        if(sz == 0) {
            nxt[root] = treap_head;
            treap_head = root;
            root = -1;
            sz = 0;
            return;
        }
        arr[no].we--;
        if(arr[no].we != 0){
            relaxtofa(no);
            return;
        }
        while(arr[no].left != -1 || arr[no].right != -1) {
            if(arr[no].left == -1) left_rot(arr[no].right);
            else {
                if(arr[no].right == -1 || arr[arr[no].left].prio > arr[arr[no].right].prio) right_rot(arr[no].left);
                else left_rot(arr[no].right);
            }
        }
        int no1 = no;
        if(arr[arr[no].fa].left == no) arr[arr[no].fa].left = -1;
        else arr[arr[no].fa].right = -1;
        relaxtofa(arr[no].fa);
        nxt[no1] = treap_head;
        treap_head = no1;
    }
private:
    void relaxfa(int no) {
        if(arr[no].fa == -1) return;
        if(arr[arr[no].fa].val > arr[no].val) arr[arr[no].fa].left = no;
        else arr[arr[no].fa].right = no;
    }
    void relax(int no) {
        arr[no].sz = arr[no].we;
        if(arr[no].left != -1) arr[no].sz += arr[arr[no].left].sz;
        if(arr[no].right != -1) arr[no].sz += arr[arr[no].right].sz;
    }
    void relaxtofa(int no) {
        while(no != -1) {
            relax(no);
            root = no;
            no = arr[no].fa;
        }
    }
    void right_rot(int no) {
        int fa = arr[no].fa;
        arr[no].fa = arr[fa].fa;
        arr[fa].left = arr[no].right;
        if(arr[no].right != -1) arr[arr[no].right].fa = fa;
        arr[no].right = fa;
        arr[fa].fa = no;
        relax(fa);
        relaxfa(no);
        relax(no);
    }
    inline void left_rot(int no) {
        int fa = arr[no].fa;
        arr[no].fa = arr[fa].fa;
        arr[fa].right = arr[no].left;
        if(arr[no].left != -1) arr[arr[no].left].fa = fa;
        arr[no].left = fa;
        arr[fa].fa = no;
        relax(fa);
        relaxfa(no);
        relax(no);
    }
};

int main()
{
    {
        Treap tr;
        for(int i=0;i<4;i++)
        {
            tr.insert(2*i+i/2+1);
        }
        if(tr.lower_bound(5)!=NULL)printf("%d\n", tr.lower_bound(5)->val);

    }
}
