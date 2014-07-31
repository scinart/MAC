//nkoj 2225
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <cassert>
#include <vector>
#include <cstring>
#include <list>
#include <map>
#include <deque>
#include <bitset>

using namespace std;

class Card {
public:
    int a,b,c,d;
    Card(int a_,int b_,int c_):a(a_),b(b_),c(c_){d=(a-b)*c;}
};

// bool ltb(const Card& ca, const Card& cb) {return ca.b<cb.b;}
bool ltd(const Card& ca, const Card& cb)
{ //critical
    return ((ca.d<cb.d) ||
            ((ca.d==cb.d) && ca.b<cb.b));
/*
(or (< (ca.d, cb.d))
    (and (= ca.d cb.d)
         (< ca.b cb.b)))

*/
}

int main()
{
    vector<Card> v;
    int N,a,b,c;
    scanf("%d",&N);
    v.reserve(N);
    while(N--)
    {
        scanf(" %d %d %d",&a,&b,&c);
        v.push_back(Card(a,b,c));
    }

    sort(v.begin(), v.end(), ltd);

    int cnti = 0;
    int min_di___cnti = INT_MAX;
    for(vector<Card>::iterator it=v.begin(); it!=v.end(); it++)
    {
        min_di___cnti = min(min_di___cnti, it->d-cnti);
        cnti+=it->b;
    }
    // printf("%d\n", -min_di___cnti);
    printf("%d\n", min_di___cnti>0?0:-min_di___cnti);
    return 0;
}
