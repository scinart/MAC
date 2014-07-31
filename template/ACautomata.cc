#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

const int  Sigma = 26; //字母表大小
const char Alpha = 'a';//字母表首字母
class ACautomata
{
private:
    bool failPointerBuilt;
public:
    struct Node
    {
        Node* father;
        Node* fail;
        Node* child[Sigma];
        int point;
        Node()
        {
            father = NULL;
            fail=NULL;
            memset(child,0,sizeof(child));
            point=0;
        }
    };
    Node* root; //¡important! root->fail MUST be NULL.
public:
    ACautomata(){root = new Node; failPointerBuilt=false;}
    void GC(Node*& n)
    {
        if(n==NULL) return;
        for(int i=0; i<Sigma; i++) GC(n->child[i]);
        delete n;
    }
    ~ACautomata(){GC(root);}
public:
    void insert(const string& s,int num = 1)
    {
        failPointerBuilt = false;
        Node* p = root;
        int len = s.length();
        for (int i=0; i<len; i++)
        {
            int where=s[i]-'a';
            if (p->child[where]==NULL)
                p->child[where]=new Node;
            p->child[where]->father = p;
            p=p->child[where];
        }
        p->point += num;
    }
    void buildFailPoint()
    {
        failPointerBuilt = true;
        //bfs
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* now = q.front(); q.pop();
            for (int i=0;i<Sigma;++i)
                if (now->child[i]!=NULL) {
                    if (now==root)
                        now->child[i]->fail=root;
                    else {
                        Node *p=now->fail;
                        while (p!=NULL) {
                            if (p->child[i]!=NULL) {
                                now->child[i]->fail=p->child[i];
                                break; }
                            p=p->fail; }
                        if (p==NULL) now->child[i]->fail=root; }
                    q.push(now->child[i]); } }
    }
    int query(const string& queryString)
    {
        if(!failPointerBuilt) buildFailPoint();
        int ans=0;
        int len=queryString.length();
        Node *p=root;
        for (int i=0;i!=len;++i)
        {
            int index=queryString[i]-Alpha;
            while (p->child[index]==NULL && p!=root) p=p->fail;
            if (p->child[index]==NULL) continue;
            p=p->child[index];
            Node *t=p;
            while (t!=root)
            {
                if (t->point!=0)
                {
                    // end node p matched;;
                    ans += t->point;
                }
                t=t->fail;
            }
        }
        return ans;
    }
};


int main()
{
    ACautomata aca;

    aca.insert(string("abcd"));
    aca.insert(string("b"));
    cout<<aca.query("abc")<<'\n';
    return 0;
}
