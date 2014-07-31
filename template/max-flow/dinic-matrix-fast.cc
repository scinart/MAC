#include <queue>
#include <cstdio>
#include <cstring>

// 使用前请把_C置0
const int MAXN = ...;
const int INF = 0x3f3f3f3f;

// 邻接矩阵版 0-indexed.
// 重边请特殊处理
int _N, _C[MAXN][MAXN], _F[MAXN][MAXN],_S,_T,_D[MAXN];
bool bfs () {
    queue<int> q;
    q.push(_S);
    memset(_D,-1,_N*sizeof _D[0]);
    _D[_S]=0;
    while(!q.empty()){
        int v=q.front();q.pop();
        for(int to=0;to<_N;++to)
            if(_D[to]==-1&&_F[v][to]<_C[v][to]){
                q.push(to);
                _D[to]=_D[v]+1; } }
    return _D[_T]!=-1;
}
int dfs(int v,int flow){
    if(!flow)return 0;
    if(v==_T)return flow;
    int total_pushed = 0;
    for(int to=0; to<_N; ++to){
        if(_D[to]!=_D[v]+1)continue;
        int pushed=dfs(to,min(flow,_C[v][to]-_F[v][to]));
        if(pushed){
            _F[v][to]+=pushed;
            _F[to][v]-=pushed;
            total_pushed+=pushed;
            flow -= pushed;
            if(flow == 0)
                break;
        }
    }
    return total_pushed;
}

int dinic(){
    int flow=0;
    memset(_F,0,sizeof(_F));
    while(bfs()){
        int pushed=dfs(_S,INF);
        flow+=pushed;
    }
    return flow;
}


