//problem 2210
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

template <typename T>
class PII
{
public:
    T first;
    T second;
    PII (T a, T b){
        first = a;
        second = b;
    }
    PII& operator=(const PII& rhs)
    {
        first = rhs.first;
        second = rhs.second;
    }
    bool operator==(const PII& rhs)const
    {
        return first==rhs.first && second == rhs.second;
    }
    bool operator<(const PII& rhs)const
    {
        return first<rhs.first || (first==rhs.first && second < rhs.second);
    }
};

typedef vector<vector<short> > VVS;
typedef PII<short> PSS;
VVS vsi;
short* arr;
short N;

bool conflict(short m, short n)
{

    map<PSS, bool> memo;
    if (memo.find(PSS(m,n)) != memo.end())
    {
        return memo[PSS(m,n)];
    }
    else
    {
        memo[PSS(m,n)] = ! ! arr[m*N+n];
        return ! ! arr[m*N+n];
    }
}
bool yaconflict(vector<short>& a, short n)
{
    for(vector<short>::iterator i=a.begin(); i!=a.end(); i++)
    {
        if(conflict(*i,n))
            return true;
    }
    return false;
}
short f(short pos, VVS& vsi)
{
    int ss = vsi.size();
    //printf("dealing-with pos: %hi, N: %hi, ss: %d\n", pos, N, ss);
    //cin.get();

    if(pos==N)
        return ss;
    int mix = N;
    for(int i=0; i<ss; i++)
    {
        if(!(yaconflict(vsi[i],pos)))
        {//if not conflict adding pos to this group.
            vsi[i].push_back(pos);
            int ret = f(pos+1, vsi);
            mix=ret<mix?ret:mix;
            vsi[i].pop_back();
        }
    }
    vector<short> vs;
    vs.push_back(pos);
    vsi.push_back(vs);

    int ret = f(pos+1, vsi);
    mix=ret<mix?ret:mix;

    vsi.pop_back();
    return mix;
}
int main()
{

    freopen("nkoj2210.in", "r", stdin);

    scanf("%hi", &N);

    arr = new short[N*N];
    for(short i=0; i<N*N; i++)
    {
        scanf("%hi", &arr[i]);
    }
    //freopen("/dev/tty","r",stdin);
    vector<short> vs;
    vs.push_back(0);
    vsi.push_back(vs);
    printf("%hi\n", f(1,vsi));

}
