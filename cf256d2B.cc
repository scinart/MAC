#include <iostream>
#include <vector>
using namespace std;




#ifdef __GNUC__
  #if __cplusplus >= 201103L
    #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
    #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
  #else
    #ifdef __STRICT_ANSI__
      #define EACH(it,A) for (__typeof__(A.begin()) it=A.begin(); it!=A.end(); ++it)
      #define REACH(it,A) for (__typeof__(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
    #else
      #define EACH(it,A) for (typeof(A.begin()) it=A.begin(); it!=A.end(); ++it)
      #define REACH(it,A) for (typeof(A.rbegin()) it=A.rbegin(); it!=A.rend(); ++it)
    #endif
  #endif
#else
  #define EACH(it,A) for (auto it=A.begin(); it!=A.end(); ++it)
  #define REACH(it,A) for (auto it=A.rbegin(); it!=A.rend(); ++it)
#endif



int main()
{

    std::ios::sync_with_stdio(false);

    string a,b;

    cin>>a>>b;

    if(b.size()>a.size())
    {
        cout<<"need tree\n";
        return 0;
    }

    vector<int> ba(26,0),bb(26,0);

    EACH(it,a)ba[*it-'a']++;
    EACH(it,b)bb[*it-'a']++;

    for(int i=0; i<26; i++)
    {
        if(bb[i]>ba[i])
        {
            cout<<"need tree\n";
            return 0;
        }
    }

    string::iterator ita=a.begin(), itb=b.begin();
    bool at=true;
    while(itb!=b.end())
    {
        if(*ita==*itb)
        {
            ita++;itb++;
        }
        else if(ita==a.end())
        {
            at=false;
            break;
        }
        else
        {
            ita++;
        }
    }
    if(at)
    {
        cout<<"automaton\n";
        return 0;
    }
    if (a.size()==b.size())
    {
        cout<<"array\n";
        return 0;
    }
    cout<<"both\n";

    return 0;
}
