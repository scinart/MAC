#include <iostream>
#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

// Class of Pairs

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

typedef PII<char> Pii;

using namespace std;


int main()
{
    freopen("poj3096.in", "r", stdin);
    string buf;
    while(cin>>buf)
    {
        if (buf == "*")
            break;
        if (buf.size()<=2)
            cout<<buf<<" is surprising.\n";
        else
        {
            int ss = buf.size();
            bool found = false;
            for(int i=0; i<ss-2 && !found; i++)
            {
                map<Pii, char> miic;
                for(int j=0; j<ss-1-i; j++)
                {
#ifdef SCI_DEBUG
                    cout<<"COMP: "<<buf[j]<<"    "<<buf[j+i+1]<<endl;
#endif
                    Pii pii(buf[j], buf[j+i+1]);
                    if (miic.find(pii) != miic.end())
                    {
                        found = true;
                        break;
                    }
                    else
                    {
                        miic[pii] = 't';
                    }
                }
            }
            if (found)
            {
                cout<<buf<<" is NOT surprising.\n";
            }
            else
            {
                cout<<buf<<" is surprising.\n";
            }
        }
    }
}
