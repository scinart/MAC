// Time-stamp: <2014-08-04 14:51:53 scinart>
// created at 2014-08-04 13:38:14
// 2011fzA.cc

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cassert>
#include <list>
#include <iomanip>
#include <cmath>
#include <deque>
#include <utility>
#include <map>
#include <set>
#include <bitset>
#include <numeric>
#include <climits>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <sstream>

using namespace std;

#define REP(i, n) for (int  i=0; i<(int)(n); ++i)
#define REP_1(i, n) for (int i=1; i<=(int)(n); ++i)
#define FOR(i, b, e) for (int i=(b); i<(int)(e); ++i)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define DWN(i, b, e) for (int i=(b); i>(int)(e); --i)
#define ALL(c) c.begin(), c.end()

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
#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

typedef unsigned int uint;
typedef unsigned long long ULL;
typedef long long LL;
typedef long long ll;
typedef pair<int, int> PII;
typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<vector<int> > VVI;

bool PIIfs(const PII& a, const PII& b){return a.first<b.first || (a.first == b.first && a.second<b.second);}
bool PIIsf(const PII& a, const PII& b){return a.second<b.second || (a.second == b.second && a.first<b.first);}
bool PIIFS(const PII& a, const PII& b){return a.first>b.first || (a.first == b.first && a.second>b.second);}
bool PIISF(const PII& a, const PII& b){return a.second>b.second || (a.second == b.second && a.first>b.first);}
bool PIIfS(const PII& a, const PII& b){return a.first<b.first || (a.first == b.first && a.second>b.second);}
bool PIIsF(const PII& a, const PII& b){return a.second<b.second || (a.second == b.second && a.first>b.first);}
bool PIIFs(const PII& a, const PII& b){return a.first>b.first || (a.first == b.first && a.second<b.second);}
bool PIISf(const PII& a, const PII& b){return a.second>b.second || (a.second == b.second && a.first<b.first);}

template <typename T> inline T max(T a, T b, T c) { return max(max(a, b), c); }
template <typename T> inline T max(T a, T b, T c, T d) { return max(max(a, b, c), d); }
template <typename T> inline T max(T a, T b, T c, T d, T e) { return max(max(a, b, c, d), e); }
template <typename T> inline T min(T a, T b, T c) { return min(min(a, b), c); }
template <typename T> inline T min(T a, T b, T c, T d) { return min(min(a, b, c), d); }
template <typename T> inline T min(T a, T b, T c, T d, T e) { return min(min(a, b, c, d), e); }

template <typename T> inline istream& RD(T& x){return cin>>x;}
template <typename T, typename U> inline istream& RD(T& a, U& b){return cin>>a>>b;}
template <typename T, typename U, typename V> inline istream& RD(T& a, U& b, V& c){return cin>>a>>b>>c;}
template <typename T, typename U, typename V, typename W>
inline istream& RD(T& a, U& b, V& c,W& d){return cin>>a>>b>>c>>d;}
template <typename T, typename U, typename V, typename W, typename X>
inline istream& RD(T& a, U& b, V& c,W& d,X& e){return cin>>a>>b>>c>>d>>e;}

template <typename T>
void checkmin(T& a,const T& b){if(b<a)a=b;}
template <typename T>
void checkmax(T& a, const T& b){if(b>a)a=b;}

// G general
// R Castel
// H Knight
// C cannon

char board[20][20];
bool attack[20][20];
inline bool inboard(int x,int y)
{
    return x>=1 && x<=9 && y>=1 && y<=9;
}
inline bool instrictboard(int x,int y)
{
    return x>=1 && x<=3 && y>=4 && y<=6;
}

#define CHECK(x,y) do{if(inboard(x,y)) attack[x][y]=true;}while(0)
#define EMPTY(x,y) (inboard(x,y) && board[x][y]==0)

int main()
{
#ifdef ECLIPSE
    freopen("in.txt", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    int num, row,col;
    while(cin>>num>>row>>col && num)
    {
        memset(board,0,sizeof(board));
        memset(attack,0,sizeof(attack));
        REP(i,num)
        {
            char C;
            int x,y;
            cin>>C>>x>>y;
            board[x][y]=C;
        }


        {
            int state = 0;
            int special = 0;
            for(int ii=row+1; ii<=10; ii++)
            {
                if(state==0)
                {
                    if(board[ii][col]=='G')
                    {
                        special=1;
                    }
                    else if(board[ii][col])
                    {
                        state=1;
                    }
                }
            }
            if(special)
            {
                cout<<"NO\n";
                continue;
            }
        }


        REP_1(i,10)
        {
            REP_1(j,9)
            {
                if(board[i][j])
                {
                    switch(board[i][j])
                    {
                      case 'G':
                      {
                          int state = 0;
                          for(int ii=i-1; ii>=1; ii--)
                          {
                              if(state==0)
                              {
                                  if(board[ii][j])
                                  {
                                      attack[ii][j]=true;
                                      state=1;
                                  }
                                  else
                                  {
                                      attack[ii][j]=true;
                                  }
                              }
                          }
                          break;
                      }
                      case 'R': //Castel;
                      {
                          int xstate = 1;
                          for(int jj=j-1; jj>=1; jj--)
                          {
                              if (xstate==1)
                              {
                                  if(!board[i][jj])
                                  {
                                      attack[i][jj]=true;
                                  }
                                  else
                                  {
                                      xstate=2;
                                      attack[i][jj]=true;
                                  }
                              }
                          }
                          xstate = 1;
                          for(int jj=j+1; jj<=9; jj++)
                          {
                              if (xstate==1)
                              {
                                  if(!board[i][jj])
                                  {
                                      attack[i][jj]=true;
                                  }
                                  else
                                  {
                                      xstate=2;
                                      attack[i][jj]=true;
                                  }
                              }
                          }
                          int ystate = 1;
                          for(int ii=i-1; ii>=1; ii--)
                          {
                              if (ystate==1)
                              {
                                  if(!board[ii][j])
                                  {
                                      attack[ii][j]=true;
                                  }
                                  else
                                  {
                                      attack[ii][j]=true;
                                      ystate=2;
                                  }
                              }
                          }
                          ystate = 1;
                          for(int ii=i+1; ii<=10; ii++)
                          {
                              if (ystate==1)
                              {
                                  if(!board[ii][j])
                                  {
                                      attack[ii][j]=true;
                                  }
                                  else
                                  {
                                      attack[ii][j]=true;
                                      ystate=2;
                                  }
                              }
                          }
                          break;
                      }
                      case 'H': //Knight;
                      {
                          //up
                          if(EMPTY(i-1,j))
                          {
                              CHECK(i-2,j-1);
                              CHECK(i-2,j+1);
                          }
                          //left
                          if(EMPTY(i,j-1))
                          {
                              CHECK(i-1,j-2);
                              CHECK(i+1,j-2);
                          }
                          //down;
                          if(EMPTY(i+1,j))
                          {
                              CHECK(i+2,j-1);
                              CHECK(i+2,j+1);
                          }
                          //right;
                          if(EMPTY(i,j+1))
                          {
                              CHECK(i-1,j+2);
                              CHECK(i+1,j+2);
                          }
                          break;
                      }
                      case 'C': //Cannon
                      {
                          int xstate = 0;
                          for(int jj=j-1; jj>=1; jj--)
                          {
                              if(xstate==0)
                              {
                                  if(board[i][jj])
                                  {
                                      xstate=1;
                                  }
                              }
                              else if (xstate==1)
                              {
                                  if(!board[i][jj])
                                  {
                                      attack[i][jj]=true;
                                  }
                                  else
                                  {
                                      attack[i][jj]=true;
                                      xstate=2;
                                  }
                              }
                          }
                          xstate = 0;
                          for(int jj=j+1; jj<=9; jj++)
                          {
                              if(xstate==0)
                              {
                                  if(board[i][jj])
                                  {
                                      xstate=1;
                                  }
                              }
                              else if (xstate==1)
                              {
                                  if(!board[i][jj])
                                  {
                                      attack[i][jj]=true;
                                  }
                                  else
                                  {
                                      attack[i][jj]=true;
                                      xstate=2;
                                  }
                              }
                          }
                          int ystate = 0;
                          for(int ii=i-1; ii>=1; ii--)
                          {
                              if(ystate==0)
                              {
                                  if(board[ii][j])
                                  {
                                      ystate=1;
                                  }
                              }
                              else if (ystate==1)
                              {
                                  if(!board[ii][j])
                                  {
                                      attack[ii][j]=true;
                                  }
                                  else
                                  {
                                      attack[ii][j]=true;
                                      ystate=2;
                                  }
                              }
                          }
                          ystate = 0;
                          for(int ii=i+1; ii<=10; ii++)
                          {
                              if(ystate==0)
                              {
                                  if(board[ii][j])
                                  {
                                      ystate=1;
                                  }
                              }
                              else if (ystate==1)
                              {
                                  if(!board[ii][j])
                                  {
                                      attack[ii][j]=true;
                                  }
                                  else
                                  {
                                      attack[ii][j]=true;
                                      ystate=2;
                                  }
                              }
                          }

                      }
                    }
                }
            }
        }

        {
            bool ok=false;
            col--;
            if(instrictboard(row,col) && attack[row][col]==false)
            {
                ok=true;
            }
            col++;col++;
            if(instrictboard(row,col) && attack[row][col]==false)
            {
                ok=true;
            }
            col--;row--;
            if(instrictboard(row,col) && attack[row][col]==false)
            {
                ok=true;
            }
            row++;row++;
            if(instrictboard(row,col) && attack[row][col]==false)
            {
                ok=true;
            }
            if(ok)
            {
                cout<<"NO\n";
            }
            else cout<<"YES\n";
        }


        // {
        //     REP_1(i,10)
        //     {
        //         REP_1(j,9)
        //         {
        //             cout<<attack[i][j];
        //         }
        //         cout<<'\n';
        //     }
        // }
    }


    return 0;
}
