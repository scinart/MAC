#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;

int N; //1<=N<=500;


int B[500][500];

int XOR[500][500];

int CPUA[500];
int CPUB[500][500];

//#define EXITNO() do{printf("NO %d\n", __LINE__); return 0;}while(0)
#define EXITNO() do{printf("NO\n"); return 0;}while(0)
#define EXITYES() do{printf("YES\n"); return 0;}while(0)

void calculate()
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(i==j)
                CPUB[i][j]=0;
            else if(( i&1) && (j&1))
                CPUB[i][j]=CPUA[i]|CPUA[j];


            else if (((!(i&1)) && (!(j&1))))
                CPUB[i][j]=CPUA[i]&CPUA[j];
            else
                CPUB[i][j]=CPUA[i]^CPUA[j];
        }
    }
}

bool CMPOK()
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(CPUB[i][j]!=B[i][j])
                return false;
        }
    }
    return true;
}
bool CMPMASKOK(int mask)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if((CPUB[i][j] | mask)!=(B[i][j] | mask))
                return false;
        }
    }
    return true;

}
int maint();
int main()
{
    while(maint() == 0)
    {

    }
    return 0;
}
int maint()
{
    if(scanf("%d", &N) == EOF)
    {
        return -1;
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            scanf(" %d", &B[i][j]);
        }
    }

    for(int i=0; i<N; i++)
    {
        for(int j=i+1; j<N; j++)
        {
            if((i&1)^(j&1))
            {
                XOR[i][j]=B[i][j];
            }
            else
            {
                XOR[i][j]=B[i][i+1]^B[i+1][j];
            }
        }
    }

    if(N==1)
    {
        if(B[0][0]==0)
        {
            EXITYES();
        }
        else
        {
            EXITNO();
        }
    }
    else if (N==2)
    {
        if(B[0][0]==0 && B[1][1]==0 && (B[0][1]==B[1][0]))
            EXITYES();
        else
            EXITNO();
    }
    else if (N==3)
    {
        if(XOR[0][2]&B[0][2])
        {
            EXITNO();
        }
        if(B[0][0]==0 &&
           B[1][1]==0 &&
           B[2][2]==0 &&
           (B[0][1]==B[1][0]) &&
           (B[0][2]==B[2][0]) &&
           (B[1][2]==B[2][1]))
        {
            EXITYES();
        }
        else
            EXITNO();

    }
    else if (N==4)
    {
//test 02 NO 11
        if(XOR[0][2]&B[0][2])
        {
            EXITNO();
        }
//test 13 NO 10
        if(XOR[1][3]&(~B[1][3]))
        {
            EXITNO();
        }
//test XORs
        if((XOR[0][1]^XOR[1][2]^XOR[2][3]) != XOR[0][3])
        {
            EXITNO();
        }
//test ZEROs and SYMMETRIC

        if (B[0][0] |
            B[1][1] |
            B[2][2] |
            B[3][3])
        {
            EXITNO();
        }
        if((B[0][1]!=B[1][0]) ||
           (B[0][2]!=B[2][0]) ||
           (B[0][3]!=B[3][0]) ||
           (B[1][2]!=B[2][1]) ||
           (B[1][3]!=B[3][1]) ||
           (B[2][3]!=B[3][2]))
        {
            EXITNO();
        }


        bitset<32> A0,A1;
        bitset<32> mask02,mask13;

// 1 is for mask, using or

        for(int i=0; i<32; i++)
        {
            if((1&(B[0][2]>>i)) == 1)
            {
                A0.set(i,1);
            }
            else if ((1&(XOR[0][2]))==0)
            {
                A0.set(i,0);
            }
            else
            {
                mask02.set(i,1);
            }

            if((1&(B[1][3]>>i)) == 0)
            {
                A1.set(i,0);
            }
            else if ((1&(XOR[1][3]>>i)) == 0)
            {
                A1.set(i,1);
            }
            else
            {
                mask13.set(i,1);
            }

            if(mask02.test(i) && (!mask13.test(i)))
            {
                mask02.set(i,0);
                A0.set(i, A1.test(i)^(1&((XOR[0][1])>>i)));
            }
        }

        CPUA[0] = (int)A0.to_ulong();

        for(int i=1; i<N; i++)
        {
            CPUA[i]=CPUA[0]^XOR[0][i];
        }

        calculate();
        bool res=CMPMASKOK((int)mask02.to_ulong());

        if(res)
        {
            EXITYES();
        }
        else
        {
            EXITNO();
        }

    }
    /*
      XOR OK
      for(int i=0; i<N; i++)
      {
      for(int j=i+1; j<N; j++)
      {
      printf("%x ",XOR[i][j]);
      }
      printf("\n");
      }
    */

    bitset<32> A0,A2,A4;

    if(XOR[0][2]&B[0][2])
    {
        EXITNO();
    }
    if(XOR[0][4]&B[0][4])
    {
        EXITNO();
    }
    if(XOR[2][4]&B[2][4])
    {
        EXITNO();
    }

    int a0__a2, a0__a4, a2__a4;

    a0__a2 = XOR[0][2]&(~B[0][2]);
    a0__a4 = XOR[0][4]&(~B[0][4]);
    a2__a4 = XOR[2][4]&(~B[2][4]);

    //OK:    printf("%x\n%x\n%x\n", a0__a2, a0__a4, a2__a4);

    bitset<32> A02(a0__a2), A04(a0__a4), A24(a2__a4);

    if(a0__a2&a0__a4&a2__a4)
    {
        EXITNO();
    }


    for(int i=0; i<32; i++)
    {
        if(((a0__a2>>i)&1)==0)
        {
            A0.set(i,(B[0][2]>>i)&1);
            A2.set(i,(B[0][2]>>i)&1);
            A4.set(i,1&(A0[i]^(1&(XOR[0][4]>>i))));
            continue;
        }
        if(((a2__a4>>i)&1)==0)
        {
            A2.set(i,(B[2][4]>>i)&1);
            A4.set(i,(B[2][4]>>i)&1);
            A0.set(i,1&(A4[i]^(1&(XOR[0][4]>>i))));
            continue;
        }
        if(((a0__a4>>i)&1)==0)
        {
            A0.set(i,(B[0][4]>>i)&1);
            A4.set(i,(B[0][4]>>i)&1);
            A2.set(i,1&(A2[i]^(1&(XOR[0][2]>>i))));
            continue;
        }
    }

    int reala0 = (int)A0.to_ulong();
    CPUA[0] = reala0;

    for(int i=1; i<N; i++)
    {
        CPUA[i]=CPUA[0]^XOR[0][i];
    }

    calculate();
    bool res=CMPOK();

    if(res)
    {
        EXITYES();
    }
    else
    {
        EXITNO();
    }
}
