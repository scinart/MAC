// nkoj 2016
// Time-stamp: <2014-06-30 21:36:05 scinart>
#include <stdio.h>
char ca[] = {'F','E','D','C','B','A','9','8','7','6','5','4','3','2','1','0'};
signed char mk[16] = {0};
unsigned st[]= {32432400,2162160,154440,11880,990,90,9,1};
char maxn(int wh)
{
    int i=-1; wh++;
    while(wh) { i++; if(mk[i]==0) wh--; }
    mk[i]=1;
    return ca[i];
}
int main()
{
    unsigned a;
    char x[9];
    x[8]='\n';
    scanf("%u", &a);
    a--;
    int bit=0, j=8;
    while(j--)
    {
        int this_bit = a/st[bit];
        a%=st[bit];
        x[bit] = maxn(this_bit);
        bit++;
    }
    for(a=0; a<9; a++)
    {
        printf("%c", x[a]);
    }
    return 0;
}
