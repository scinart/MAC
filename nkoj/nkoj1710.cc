#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <stack>
#include <cmath>
#include <climits>
#include <vector>
#include <cstring>
#include <map>
#include <time.h>
using namespace std;

#define MAX 51

int woman[MAX][MAX]; //woman 的优先列表
int man[MAX][MAX]; //man 的优先列表

int main()
{
    freopen("nkoj1710.in", "r", stdin);
    int n;
    int cases = 0;
    while (scanf("%d", &n) != EOF)
    {
        cases++;
        for (int i=1; i<=n; i++)
        {
            man[0][i]=0;
            man[i][0]=0;
            woman[0][i]=0;
            woman[i][0]=0;
        }
        int sca;

        //scan woman's preference list
        for (int i=1; i<=n; i++)
        {
            for (int j=1; j<=n; j++)
            {
                scanf("%d", &sca);
                woman[i][j]=sca;
                // woman[i][j] means woman[i] sees jth man as rank w[i][j];
            }
        }

        //scan man's preference list
        for (int i=1; i<=n; i++)
        {
            for (int j=1; j<=n; j++)
            {
                scanf("%d", &sca);
                man[i][sca]=j;
                // man[i][j] means man[i] see (rank j)'s woman is sca.
            }
        }

        stack<int> freeman;
        for (int i=1; i<=n; i++)
        {
            freeman.push(i);
        }

        while(!freeman.empty())
        {
            int whichman = freeman.top();
            freeman.pop();

            int whichwoman = man[whichman][++man[whichman][0]]; //man's nth woman.
            if(woman[whichwoman][0]) //if this woman is dating with someone
            {
                if (woman[whichwoman][woman[0][whichwoman]] > woman[whichwoman][whichman])
                {//lucky man.
                    freeman.push(woman[0][whichwoman]); //poor man becomes free.
                    woman[0][whichwoman] = whichman; //woman's dating with this man.
                }
                else
                {//unsuccessful date.
                    freeman.push(whichman);//still free.
                }
            }
            else //if this woman is free.
            {
                woman[whichwoman][0] = 1; //change the woman's state to engaging.
                woman[0][whichwoman] = whichman; //woman's dating with this man.
            }
        }

        printf("Case %d:\n", cases);
        for (int i=1; i<=n-1; i++)
        {
            printf("%d ",man[i][man[i][0]]);
        }
        printf("%d",man[n][man[n][0]]);
        printf("\n");
    }

    return 0;
}
