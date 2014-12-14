//
// Time-stamp: <2014-08-09 20:11:10 scinart>

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

const int MAXN = 50010;
struct Node {
    Node *next[26], *par; int val, end; // 26 is volatile
}buffer[MAXN << 1]; //Note that the size of POOL should be doubled.

class SAM {
public:
    Node* data,*root,*last,*cur;
    int curmax;
    SAM():data(buffer+1),last(buffer),root(buffer),cur(buffer)
    {
        curmax=0;
        memset(buffer,0,sizeof(buffer));
    }
    void add(int x) {
        Node *p = last, *np = data++;
        np->val = p->val + 1; np->end = false;
        while (p && !p->next[x])
            p->next[x] = np, p = p->par;
        if (p == 0) {
            np->par = root;
        } else {
            Node *q = p->next[x];
            if (q->val == p->val + 1) {
                np->par = q;
            } else {
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
    void buildend()
    {
        Node* p = last;
        while(p)
        {
            p->end=true;
            p=p->par;
        }
    }
    bool eat(int v, int cnt)
    {
        if(cur->next[v]!=NULL)
        {
            cur=cur->next[v];
            if(cur->end)
            {
                cout<<cnt<<'\n';
                curmax=cnt;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    int res()
    {
        return curmax;
    }
};


int main()
{
    std::ios::sync_with_stdio(false);

    string sa,sb;
    while(cin>>sb>>sa)
    {
        SAM sam;
        EACH(it,sa)
        {
            sam.add(*it-'a');
        }
        sam.buildend();
        int cnt=0;
        EACH(it,sb)
        {
            if(sam.eat(*it-'a',++cnt))
            {
            }
            else break;
        }
        cnt=sam.res();
        if(cnt)cout<<sb.substr(0,cnt)<<' '<<cnt<<'\n';
        else cout<<"0\n";
    }

    return 0;
}
