//poj3299
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

// humidex = temperature + h
// h = (0.5555)× (e - 10.0)
// e = 6.11 × exp [5417.7530 × ((1/273.16) - (1/(dewpoint+273.16)))]

// Sample Input
// T 30 D 15
// T 30.0 D 25.0
// E

// Sample Output

// T 30.0 D 15.0 H 34.0
// T 30.0 D 25.0 H 42.3
int main()
{
    double D;
    double H;
    double T;
    const double C=273.16;
    char j=' ';
    char k=' ';
    while(1)
    {
        scanf(" %c", &j);
        if (j=='E')
            break;
        double a,b;
        scanf(" %lf %c %lf", &a, &k, &b);

        switch ((j<<1)+k)
        {
          case (('D'<<1)+'H'):
          {
              D=a;
              H=b;
              double e= 6.11 * exp(5417.7530 * ((1/273.16) - (1/(D+273.16))));
              double h=0.5555*(e-10.0);
              T=H-h;
              break;
          }
          case (('H'<<1)+'D'):
          {
              D=b;
              H=a;
              double e= 6.11 * exp(5417.7530 * ((1/273.16) - (1/(D+273.16))));
              double h=0.5555*(e-10.0);
              T=H-h;
              break;
          }
          case (('D'<<1)+'T'):
          {
              D=a;
              T=b;
              double e= 6.11 * exp(5417.7530 * ((1/273.16) - (1/(D+273.16))));
              double h=0.5555*(e-10.0);
              H=T+h;
              break;
          }
          case (('T'<<1)+'D'):
          {
              D=b;
              T=a;
              double e= 6.11 * exp(5417.7530 * ((1/273.16) - (1/(D+273.16))));
              double h=0.5555*(e-10.0);
              H=T+h;
              break;
          }
          case (('H'<<1)+'T'):
          {
              H=a;
              T=b;
              double h = H-T;
              double e = h/0.5555+10;
              double mid1 = log(e/6.11)/5417.7530;
              double mid2 = mid1-1/273.16;
              D = -1/mid2-273.16;
              break;
          }
          case (('T'<<1)+'H'):
          {
              H=b;
              T=a;
              double h = H-T;
              double e = h/0.5555+10;
              double mid1 = log(e/6.11)/5417.7530;
              double mid2 = mid1-1/273.16;
              D = -1/mid2-273.16;
              break;
          }

        }
        printf("T %.1f D %.1f H %.1f\n",T,D,H);
    }
    return 0;
}
