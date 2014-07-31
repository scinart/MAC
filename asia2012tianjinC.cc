// tianjin asia 2012
// Time-stamp: <2014-08-01 00:32:07 scinart>
// 一看就是DP，这样肯定过不了。
#include <iostream>
#include <fstream>
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
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
bool piig(const pii& a, const pii& b)
{
    return a.first<b.first || (a.first == b.first && a.second<b.second);
}


template <class T> inline T abs1(T a) {return a < 0 ? -a : a;}
template <class T> inline T max1(T a, T b) { return a > b ? a : b; }
template <class T> inline T max1(T a, T b, T c) { return max1(max1(a, b), c); }
template <class T> inline T max1(T a, T b, T c, T d) { return max1(max1(a, b, c), d); }
template <class T> inline T max1(T a, T b, T c, T d, T e) { return max1(max1(a, b, c, d), e); }
template <class T> inline T min1(T a, T b) { return a < b ? a : b; }
template <class T> inline T min1(T a, T b, T c) { return min1(min1(a, b), c); }
template <class T> inline T min1(T a, T b, T c, T d) { return min1(min1(a, b, c), d); }
template <class T> inline T min1(T a, T b, T c, T d, T e) { return min1(min1(a, b, c, d), e); }


#define LOOP(var, times) for (int var=0; var<(times); var++)
#define ITER(c, it) for (typeof((c).begin()) it=(c).begin(); it!=(c).end(); it++)

#define FOR(i, b, e) for ((i)=(int)(b); (i)<(int)(e); (i)++)

#define RS(X) scanf(" %s", (X))
#define RI(X) scanf(" %d", &(X))
#define R2I(X, Y) scanf(" %d %d", &(X), &(Y))
#define R3I(X, Y, Z) scanf(" %d %d %d", &(X), &(Y), &(Z))
#define R4I(W, X, Y, Z) scanf(" %d %d %d %d", &(W), &(X), &(Y), &(Z))
#define MS0(X) memset((X), 0, sizeof((X)))
#define MS1(X) memset((X), -1, sizeof((X)))


#define DEBUG
// #undef DEBUG

template<typename T>
T mod(T N, T M)
{
    // return canonical N%M
    if((M>0 && N>0) || (M<0 && N<0))
    {
        return N%M;
    }
    else if (M*N<0)
    {
        return N%M+((N%M)?M:0);
    }
    else
        return 0;
}

int dis(char a, char b)
{ //verified.
  //+5 -4
    if (a<b)
    {
        if(b-a<=5)
        {//forward
            return b-a;
        }
        else
        {//backward
            return b-a-10;
        }
    }
    else//a>=b
    {
        if(a-b<5)
        {//backward
            return -(a-b);
        }
        else
        {//forward
            return 10-(a-b);
        }
    }
}

int disup(char a, char b)
{//roll up from a to b. 3..4..5..6
    if(a<=b)
    {
        return b-a;
    }
    else
    {
        return b+10-a;
    }
}
int disdown(char a, char b)
{// roll down from b to a.
 // 6..5..4..3
    if(a>=b)
    {
        return -(a-b);
    }
    else
    {
        return -(a+10-b);
    }
}
bool contains(char a, char b, int d)
{//a go upto d or downto d contains b.
    if(d>0)
    {//roll grows
        return (d>=disup(a,b));
    }
    else if (d<0)
    {
        return (d<=disdown(a,b));
    }
    else
    {
        return a==b;
    }
}

char move(char a, int d)
{
    return mod((a-'0'+d),10)+'0';
}

bool judgedirect(const string& a, const string& b, int pos)
{
    int tmp = dis(a[pos],b[pos]);
    if(tmp!=5 && tmp!=0)
    {
        return tmp>0;
    }
    else
    {
        int ttmp = dis(a[pos+1],b[pos+1]);
        return ttmp>0;
    }
}
int main()
{

    string a;string b;

    while(cin>>a>>b)
    {

        a+="000";
        b+="000";
        int critical_points = 0;
        int cp = critical_points;
        int loop = 0;
        int whichcp = 0;
        int minstep=INT_MAX;

        while (loop<(1<<cp))
        {
            deque<int> dpas; //pas to next generation
            deque<int> dbar; //barren.
#define SHOW() {printf("%d %d %d\n%d %d %d\n", dpas[0], dpas[1], dpas[2], dbar[0], dbar[1], dbar[2]);}
            dpas.push_back(0);
            dpas.push_back(0);
            dpas.push_back(0);
            dbar.push_back(0);
            dbar.push_back(0);
            dbar.push_back(0);

            int sumstep=0;

            int slen = a.length();
            for(int i=0; i<slen-2; i++)
            {
                //if the first range contains target
                int absdistmov,absdistori;
                absdistmov = abs1(dis(move(a[i],dpas[0]+dbar[0]),b[i]));
                absdistori = abs1(dis(a[i],b[i]));
#ifdef DEBUG
                printf("mov, ori: %d %d\n", absdistmov, absdistori);
                SHOW();
#endif

                if (contains(a[i],b[i],dpas[0]+dbar[0]))
                {
#ifdef DEBUG
                    printf("contains");
#endif

                    if(contains(a[i],b[i],dpas[0]))
                    {
                        dpas[1]=0;
                        assert(abs1(dpas[0])>=abs1(dis(a[i],b[i])));
                        dbar[1]=dis(a[i],b[i]);//???
                        sumstep+=0;
                    }
                    else
                    {
                        dpas[1]=0;
                        dbar[1]=dpas[0];
                        sumstep+=0;
                    }
#ifdef DEBUG
                    printf(" +0 \n");
#endif

                }
                else if //(abs1(dis(move(a[i],dpas[0]+dbar[0]),b[i])) < abs1(dis(a[i],b[i])))
                    ((absdistmov < absdistori)
                     ||
                     ((absdistmov == absdistori) &&
                      (judgedirect(a,b,i+1)*2-1)*(dpas[1]+dbar[1])>0))
                {
#ifdef DEBUG
                    printf("tomove");
#endif

                    int togo = (dis(move(a[i],dpas[0]+dbar[0]),b[i]));
                    dpas[1]=togo;
                    dbar[2]=dpas[1];
                    dbar[1]=dpas[0];

                    sumstep += abs1(togo);
#ifdef DEBUG
                    printf("+%d\n", togo);
#endif

                }
                else// if(!(dpas[0]==0 && dbar[0]==0 && dis(a[i],b[i]) == 5))
                {

#ifdef DEBUG
                    printf("origin");
#endif

                    int togo = dis(a[i],b[i]);
                    dpas[1]=togo;
                    dbar[2]=togo;
                    dbar[1]=0;
                    sumstep += abs1(togo);
#ifdef DEBUG
                    printf("+%d\n", togo);
#endif

                }
//                 ifdef
//                 {
// #endif DEBUG
//                     printf("critical\n");
// #endif
//                     // cp++;///////////////////////////////////

//                     int after = dis(a[i+1],b[i+1]);
//                     int choice = (loop>>whichcp)&1;
//                     if(after==0)
//                     {
//                         choice = 0; //random;
//                     }
//                     else if (after == 5)
//                     {
//                         int aftter = dis(a[i+2],b[i+2]);
//                         choice = (aftter>0);
//                     }
//                     else
//                     {
//                         choice = (after>0);
//                     }

//                     if(choice)
//                     {
//                         dpas[1]=5;
//                         dbar[1]=0;
//                         dbar[2]=5;
//                         sumstep+=5;
//                     }
//                     else
//                     {
//                         dpas[1]=-5;
//                         dbar[1]=0;
//                         dbar[2]=-5;
//                         sumstep+=5;
//                     }
//                 }
                dpas.pop_front();
                dbar.pop_front();
                dpas.push_back(0);
                dbar.push_back(0);
            }

            minstep = min1(minstep, sumstep);
            loop++;
        }
        cout<<minstep<<endl;
    }
    return 0;
}
