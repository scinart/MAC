//nkoj 1131
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

// Levenshtein Distance

// Dynamic Programming.

#define MAXN 2000

char stra[MAXN];
char strb[MAXN];

int main()
{
    while (scanf ("%s %s", stra, strb)==2)
    {
        int alen = strlen(stra);
        int blen = strlen(strb);
        char* sa;
        char* sb;
        // make sa bigger.
        if(alen<blen)
        {
            sa=strb;sb=stra;
            swap(alen,blen);
        }
        else
        {
            sa=stra;sb=strb;
        }

        vector<int> memo(alen+1);
        vector<int> memo2(alen+1);
        for(int i=0; i<alen+1; i++)
        {
            memo[i]=i;
        }
        /*
          sasasasasasasasasasasasasasasasasasasasasasasasasasasa
          b
          s
          b
          s
          b

        */

        for(int i=1; i<=blen; i++)
        {
            memo2[0] = i;
            for(int j=1; j<=alen; j++)
            {
                bool nocost = (sa[j-1]==sb[i-1]);
                int minimum =  min(memo[j], memo2[j-1]) + 1;
                if(memo[j-1]+(nocost?0:1) < minimum)
                    minimum = memo[j-1]+(nocost?0:1);
                memo2[j] = minimum;
            }
            memo.swap(memo2);
        }
        printf("%d\n", memo[alen]);
    }
}

