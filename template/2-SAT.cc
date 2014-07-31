const int maxn = 12345;
class TwoSAT
{
public:
    int n; //size
    vector<int> G[maxn*2];
    bool mark[maxn*2];
    int S[maxn*2], c;

    TwoSAT(int size){
        init(size);
    }
    bool dfs(int x)
    {
        if (mark[x^1]) return false;
        if (mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for (int i = 0; i < G[x].size(); i++)
            if (!dfs(G[x][i])) return false;
        return true;
    }

    void init(int n_)
    {
        n = n_;
        for (int i = 0; i < n*2; i++) G[i].clear();
        memset(mark, 0, sizeof(mark));
    }

    /// x AND y = 1
    void add_and_one(int x,int y)
    {
        G[x^1].push_back(y);
        G[y^1].push_back(x);
        G[x].push_back(y);
        G[y^1].push_back(x^1);
        G[y].push_back(x);
        G[x^1].push_back(y^1);
    }

    /// x AND y = 0
    void add_and_zero(int x,int y)
    {
        G[x].push_back(y^1);
        G[y].push_back(x^1);
    }

    /// x OR y = 1
    void add_or_one(int x,int y)
    {
        G[x^1].push_back(y);
        G[y^1].push_back(x);
    }

    /// x OR y = 0
    void add_or_zero(int x,int y)
    {
        G[x].push_back(y^1);
        G[y].push_back(x^1);
        G[x].push_back(y);
        G[y^1].push_back(x^1);
        G[x^1].push_back(y^1);
        G[y].push_back(x);
    }

    /// x XOR y = 1
    void add_xor_one(int x,int y)
    {
        G[x^1].push_back(y);
        G[y^1].push_back(x);
        G[x].push_back(y^1);
        G[y].push_back(x^1);
    }

    /// x XOR y = 0
    void add_xor_zero(int x,int y)
    {
        G[x^1].push_back(y^1);
        G[y].push_back(x);
        G[x].push_back(y);
        G[y^1].push_back(x^1);
    }

    /// x -> y
    void add_to(int x,int y)
    {
        G[x].push_back(y);
        G[y^1].push_back(x^1);
    }

    bool solve()
    {
        for(int i = 0; i < n*2; i += 2)
            if(!mark[i] && !mark[i+1])
            {
                c = 0;
                if(!dfs(i))
                {
                    while(c > 0) mark[S[--c]] = false;
                    if(!dfs(i+1)) return false;
                }
            }
        return true;
    }
};
