//problem 2214
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

#define MMAX 401
typedef bitset<MMAX> inner;
typedef vector<inner> outer;

bool cross(int i,int j,int k, int l)
{// return true if (i,j) affects (k,l)
    if ((i+j)==(k+l)
        ||
        (i-j)==(k-l))
        return true;
    else return false;
}
int create_matrix(int size, outer& vvi)
{ // generate affect matrix size*size by size*size.
  // assert(size%2==0);
    vvi.clear();
    vvi.reserve(size*size);
    inner vi;

    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size; j++)
        {
            for (int k=0; k<size; k++)
            {
                for (int l=0; l<size; l++)
                {
                    vi.set(MMAX-1-(k*size+l),cross(k,l,i,j));
                }
            }
            vvi.push_back(vi);
        }
    }
    return 0;
}

//#define SCIDEBUG
void gauss(outer& vvi, int sqrtofsize)
{
    //vector<pair<int,int> > pairs;
    inner backup;
    int ss = vvi.size();
    int cascade = 0;// cascade is the number of free variable.
    for(int i=0; i<ss-cascade; i++)
    {
        if(vvi[i].test(MMAX-1-(i+cascade)))
        {
            backup = vvi[i];
            for(outer::iterator j=vvi.begin(); j!=vvi.end(); j++)
            {
                if(j->test(MMAX-1-(i)))
                    (*j)^=backup;
            }
            vvi[i]=backup;
            #ifdef SCIDEBUG
            debug_matrix(vvi);
            cin.get();
            #endif
        }
        else
        {//换
            bool findd = false;
            int j;
            for(j=i+1; j<ss; j++)
            {
                if(vvi[j].test(MMAX-1-(i+cascade)))
                {
                    findd = true;
                    break;
                }
            }
            if (findd)
            {
                swap(vvi[i],vvi[j]);
                #ifdef SCIDEBUG
                debug_matrix(vvi);
                cin.get();
                #endif
                backup = vvi[i];
                for(outer::iterator j=vvi.begin(); j!=vvi.end(); j++)
                {
                    if(j->test(MMAX-1-(i)))
                        (*j)^=backup;
                }
                vvi[i]=backup;
                #ifdef SCIDEBUG
                debug_matrix(vvi);
                cin.get();
                #endif
                //pairs.push_back(pair<int,int>(i,j));
            }
            else
            {//one more free variable.
                cascade++;
                i--;
            }
        }
    }

    //printf("cascade is %d\n", cascade);
    //debug_matrix(vvi);

    for(int i=1; i<=cascade; i++)
    {
        if (vvi[ss-i].test(MMAX-1-(ss)))
        {
            printf("-1");
            return;
        }
    }

    /*for (auto i = pairs.rbegin(); i!=pairs.rend(); i++)
    {
        printf("%d %d\n", i->first, i->second);
        swap(vvi[i->first], vvi[i->second]);
    }*/
    //debug_matrix(vvi,ss);
    for (int i=0; i<ss; i++)
    {
        printf("%d ", vvi[i].test(MMAX-1-ss));
        if ((i+1)%sqrtofsize==0) printf("\n");
    }
}

int main()
{
    //freopen("input", "r", stdin);

    short size;
    scanf("%hi", &size);

    outer vvi;

    create_matrix(size, vvi);

    short a;

    for(int i=0; i<size*size; i++)
    {
        scanf("%hi", &a);
        vvi[i].set(MMAX-1-size*size, !a);
    }//now vvi is augment matrix.

#ifdef SCIDEBUG
    debug_matrix(vvi);
    freopen("/dev/tty","r",stdin);
    stdin = fopen(0,"r");
#endif

    gauss(vvi,size);

    return 0;
}
