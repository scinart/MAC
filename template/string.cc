#include <string>
#include <iostream>
using namespace std;

string trim_head(const string& str, const string& whitespace = " \t")
{
    int b = str.find_first_not_of(whitespace);
    return (b==string::npos)?"":str.substr(b, str.size()-b);
}
string trim_end(const string& str, const string& whitespace = " \t")
{
    int e = str.find_last_not_of(whitespace);
    return (e==string::npos)?"":str.substr(0, e+1);
}

inline void STL_Reverse(std::string& str)
{
    reverse(str.begin(), str.end());
}

int main()
{
    string s = "         t t           ";
    cout<<trim_head(s)<<"0\n";
    cout<<trim_end(s)<<"0\n";
    cout<<trim_end(trim_head(s))<<"0\n";
}
