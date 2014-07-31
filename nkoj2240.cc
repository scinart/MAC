/*
#Include <cstdio>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

int main()
{
    int n;
    vector<char> v;
    vector<char> key;
    stringstream ss;
    while(cin>>n)
    {
        v.push_back(char(n));
    }
    for(char i='A'; i<='Z'; i++)
    {
        for(char j='A'; j<='Z'; j++)
        {
            for(char k='A'; k<='Z'; k++)
            {
                int res = 0;
                for(auto it = v.begin(); it!=v.end(); it++)
                {
                    char c = ((*it)^(((it-v.begin())%3==0?i:((it-v.begin())%3==1?j:k))));
                    if(!(isprint(c) || isspace(c)))
                    {
                        res++;
                        break;
                    }
                }
                if(res)
                    continue;
                else
                {
                    key.push_back(i);
                    key.push_back(j);
                    key.push_back(k);
                }
            }
        }
    }

    vector<char> newkey;
    for(int q=0; q<key.size();)
    {
        stringstream pro;
        char i=key[q++],j=key[q++],k=key[q++];
        for(auto it=v.begin(); it!=v.end(); it++)
        {
            char c = ((*it)^(((it-v.begin())%3==0?i:((it-v.begin())%3==1?j:k))));
            pro<<c;
        }
        if(string(pro.str()).find("main") != string::npos)
        {
            newkey.push_back(i);
            newkey.push_back(j);
            newkey.push_back(k);
        }
    }

    for_each(key.begin(), key.end(), [](char c){cout<<c;});
    cout<<endl;
    for_each(newkey.begin(), newkey.end(), [](char c){cout<<c;});
    cout<<endl;
    // now key is CHN
    return 0;
}
*/

/**************************
 *       NKPC 10          *
 *     Have fun :)        *
 **************************/

#include <algorithm>
#include <iostream>
#include <string>

void qsort(int *a, int l, int r)
{
    int mid = a[l + (r - l) / 2];
    int x = l, y = r;
    do {
        while (a[x] < mid) x++;
        while (a[y - 1] > mid) y--;
        if (x >= y) break;

        std::swap(a[x++], a[--y]);
    } while (true);

    if (x < r) qsort(a, x, r);
    if (y > l) qsort(a, l, y);
}

int main(int argc, char *argv[])
{
    int secret[] = {
        3616, 4865, 4019, 4400, 1108, 3704, 3411, 201, 1205, 2911,
        4432, 1977, 813, 1765, 4214, 4111, 2233, 4967, 1867, 2487,
        5077, 308, 4702, 1632, 72, 1405, 632, 2708, 4732, 4611,
        2214, 3316, 3832, 2601, 997, 1501, 2799, 511, 3101, 1302,
        2310, 2101, 917, 3009, 4308, 3432, 3132, 1600, 544, 408,
        5146, 3801
    };
    size_t secret_size = sizeof secret / sizeof secret[0];

    qsort(secret, 0, secret_size);

    std::string text;
    for (size_t i = 0; i < secret_size; i++) {
        text += secret[i] - i * 100;
    }

    std::cout << text << std::endl;

    return 0;
}
