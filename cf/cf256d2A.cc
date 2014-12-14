#include <iostream>

using namespace std;
int main()
{
    int a,b,c,d,e,f,g;
    cin>>a>>b>>c>>d>>e>>f>>g;

    int aa = a+b+c;
    int bb = d+e+f;

    int cups_needed = (aa+4)/5;
    int medals_needed = (bb+9)/10;

    if(cups_needed + medals_needed <= g)
    {
        cout<<"YES\n";
    }
    else
    {
        cout<<"NO\n";
    }
    return 0;
}
