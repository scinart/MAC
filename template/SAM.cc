const int MAXN = ...;
const int Sigma = 26;


struct Node {
    Node* next[Sigma];
    Node* par; //parent
    vector<Node*> child;
    int val; //len
    bool end; //if it is final state.
}buffer[MAXN << 1]; //Note that the size of POOL should be doubled.

class SAM {
public:
    Node* data,*root,*last;
    SAM():data(buffer+1),root(buffer),last(buffer)
    {
        memset(buffer,0,sizeof(buffer));
    }
    void add(int x) {
        Node *p = last, *np = data++;
        np->val = p->val + 1; np->end = false;
        while (p && !p->next[x])
        {
            p->next[x] = np;
            p = p->par;
        }
        if (p==0) {np->par = root;}
        else
        {
            Node *q = p->next[x];
            if (q->val == p->val+1)
            {
                np->par = q;
            }
            else
            {
                Node *nq = data++;
                nq->val = p->val + 1;
                memcpy(nq->next, q->next, sizeof q->next);
                nq->par = q->par;
                np->par = q->par = nq;
                while (p && p->next[x] == q)
                    p->next[x] = nq, p = p->par;
            }
        }
        last = np;
    }
    void buildfinal()
    { //use this to build final state.
        Node* p = last;
        while(p)
        {
            p->end=true;
            p=p->par;
        }
    }
    void buildchild()
    {
        for(Node* x=root; x!=data; x++)
        {
            if(x->par)
            {
                (x->par->child).push_back(x);
            }
        }
    }
};
