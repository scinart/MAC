//problem 2106
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
class Eert;
//typedef deque<Eert> vv;
typedef map<int,vector<Eert> > vv;
//      map<accept, nodes>;

class Eert
{
    //Eert means the revert of tree;
public:
    int node; //Eert node value;
    int dist; //distance from root.
    int step;
    //int accept;
    bool operator<(const Eert& rhs)
    {
        return dist+step<rhs.dist+rhs.step;
    }
    Eert(int pnode, int pstep, int pdist)
    {
        node = pnode;
        step = pstep;
        dist = pdist;
    }
    Eert& stepforward()
    {
        node += step;
        dist++;
        return *this;
    }
};

int main()
{
    freopen("input", "r", stdin);
    vv qE;
    vector<int> vE;
    map<int, int> ashash;

    short sca;
    while (scanf("%hi", &sca) != EOF)
    {
        vE.clear();
        qE.clear();
        vE.reserve(sca);
        //qE.reserve(sca);
        int num;
        int maxdist = sca>=2?2:1;

        for (short i = 0; i<sca; i++)
        {
            scanf("%d", &num);
            ashash.clear();
            //iterator map
            vv::iterator qEfindit = qE.find(num);
            if(qEfindit != qE.end())
            {
                for (vector<Eert>::iterator vEit = (qEfindit->second).begin(); vEit != (qEfindit->second).end(); vEit++)
                {
                    ashash[vEit->node] = 1;
                    vEit->stepforward();
        //printf("Steping Forward %d\n", vEit->node-vEit->step);
                    qE[vEit->node+vEit->step].push_back(*vEit);
                    if(maxdist < vEit->dist)
                        maxdist = vEit->dist;
                }
                (qEfindit->second).clear();
            }

            for (vector<int>::iterator vit = vE.begin(); vit != vE.end(); vit++)
            {
                if (//(num-(*vit) < 1000000000/maxdist) &&
                    (ashash.find((*vit)) == ashash.end()))
                {
                    Eert nnE(num, num-(*vit),2);
                    int newacc = 2*num-(*vit);
                    map<int, vector<Eert> >::iterator mivEit = qE.find(newacc);
               //     printf("Pushing to %d, %d\n", newacc, nnE.node);
                    qE[newacc].push_back(nnE);
                }
            }
            vE.push_back(num);
        }

//
//        for (vv::iterator qit = qE.begin(); qit != qE.end(); qit++)
//        {
//            if (((qit)->dist) > maxdist)
//            {
//                maxdist = (qit)->dist;
//            }
//        }
        printf("%d\n", maxdist);
    }

    return 0;
}
