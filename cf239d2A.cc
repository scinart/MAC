//codeforces 408 A
//第一次忘了初始化new的东西了，坑。。
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <cstring>
#include <list>
#include <map>
#include <deque>

using namespace std;


int main()
{
    int cashiers; // 1≤cashiers≤100;
    scanf("%d", &cashiers);
    int* k = new int[cashiers]; //how many people in a cashier.
    for(int i=0; i<cashiers; i++)
    {
        scanf("%d", &k[i]);
    }
    int* items = new int[cashiers];// total items in queue at cashiers.
    for(int i=0; i<cashiers; i++) //initialize;
    {
        items[i]=0;
    }
    int temp;
    for(int i=0; i<cashiers; i++) //sum how many items per cashier.
    {
        for(int j=0; j<k[i]; j++)
        {
            scanf("%d", &temp);
            items[i]+=temp;
        }
    }
    
//debug
    for(int i=0; i<cashiers; i++)
    {
        printf("%d %d\n",k[i],items[i]);
    }
    printf("\n");
//end dedug
    int mini = INT_MAX;
    for(int i=0; i<cashiers; i++) //iterate to see which is minimum.
    {
        int costi = 15*k[i] + 5*items[i];
        mini = min(mini,costi);
    }
    printf("%d\n",mini);
}
