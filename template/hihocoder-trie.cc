//
// Time-stamp: <2014-07-12 22:00:23 scinart>

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

#define REP(i, n) for (int  i=0; i<(n); ++i)
#define FOR(i, b, e) for (int i=(b); i<(e); ++i)
#ifdef __GNUC__
  #if __cplusplus >= 201103L
    #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
  #else
    #ifndef __STRICT_ANSI__
      #define EACH(it,A) for (typeof(A.begin()) it=A.begin(); it!=A.end(); ++it)
    #else
      #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
    #endif
  #endif
  #if __cplusplus >= 201103L
      #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
  #else
    #ifndef __STRICT_ANSI__
      #define REACH(it,A) for (typeof(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
    #else
      #define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
    #endif
  #endif
#else
  #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
  #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
#endif
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

typedef unsigned int uint;
typedef unsigned long long ULL;
typedef long long LL;
typedef pair<int, int> PII;
typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;

bool PIIfs(const PII& a, const PII& b){return a.first<b.first || (a.first == b.first && a.second<b.second);}
bool PIIsf(const PII& a, const PII& b){return a.second<b.second || (a.second == b.second && a.first<b.first);}
bool PIIFS(const PII& a, const PII& b){return a.first>b.first || (a.first == b.first && a.second>b.second);}
bool PIISF(const PII& a, const PII& b){return a.second>b.second || (a.second == b.second && a.first>b.first);}
bool PIIfS(const PII& a, const PII& b){return a.first<b.first || (a.first == b.first && a.second>b.second);}
bool PIIsF(const PII& a, const PII& b){return a.second<b.second || (a.second == b.second && a.first>b.first);}
bool PIIFs(const PII& a, const PII& b){return a.first>b.first || (a.first == b.first && a.second<b.second);}
bool PIISf(const PII& a, const PII& b){return a.second>b.second || (a.second == b.second && a.first<b.first);}

template <typename T> inline T max(T a, T b, T c) { return max(max(a, b), c); }
template <typename T> inline T max(T a, T b, T c, T d) { return max(max(a, b, c), d); }
template <typename T> inline T max(T a, T b, T c, T d, T e) { return max(max(a, b, c, d), e); }
template <typename T> inline T min(T a, T b, T c) { return min(min(a, b), c); }
template <typename T> inline T min(T a, T b, T c, T d) { return min(min(a, b, c), d); }
template <typename T> inline T min(T a, T b, T c, T d, T e) { return min(min(a, b, c, d), e); }

template <typename T> inline istream& RD(T& x){return cin>>x;}
template <typename T, typename U> inline istream& RD(T& a, U& b){return cin>>a>>b;}
template <typename T, typename U, typename V> inline istream& RD(T& a, U& b, V& c){return cin>>a>>b>>c;}
template <typename T, typename U, typename V, typename W>
inline istream& RD(T& a, U& b, V& c,W& d){return cin>>a>>b>>c>>d;}
template <typename T, typename U, typename V, typename W, typename X>
inline istream& RD(T& a, U& b, V& c,W& d,X& e){return cin>>a>>b>>c>>d>>e;}


class TrieNode{
public:
    char c;
    int count;
    map<char,TrieNode> child;
    TrieNode():c(0),count(0){}
    TrieNode(char c_, int count_):c(c_),count(count_){}
    bool operator==(const TrieNode& rhs)const{return c==rhs.c;}
};


void p (TrieNode& t, int dep)
{
    string s(dep,' ');
    cout<<s<<t.c<<':'<<t.count<<'\n';
    EACH(it,t.child){p(it->second,dep+2);}
}
void addTrie(TrieNode& trie, const string& s, int pos)
{
    trie.count++;
    if(pos==s.size());
    else
    {
        if(trie.child.find(s[pos])!=trie.child.end())
        {
            addTrie((trie.child[s[pos]]), s, pos+1);
        }
        else
        {
            trie.child[s[pos]] = TrieNode(s[pos],0);
            addTrie(trie.child[(s[pos])], s, pos+1);
        }
    }
}

int query(TrieNode& trie, const string& s, int pos)
{
    TrieNode* t = &trie;

    while(pos!=s.length())
    {
        if(t->child.find(s[pos]) != t->child.end())
        {
            t = &(t->child[(s[pos])]);
            pos++;
        }
        else
        {
            return 0;
        }

    }
    return t->count;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int N;
    string s;

    cin>>N;
    TrieNode head;
    while(N--)
    {
        cin>>s;

        addTrie(head,s,0);
    }

    // p(head,0);
    cin>>N;
    while(N--)
    {
        cin>>s;
        cout<<query(head,s,0)<<'\n';
    }
    return 0;
}
