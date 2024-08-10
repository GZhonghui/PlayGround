#include<algorithm>
#include<cstdio>
#include<vector>
#include<queue>

const int maxn = 1e5+1;

int n;
std::vector<int> G[maxn];
std::vector<int> ans_1, ans_2;

void dfs(int now, int fa, int depth)
{
    if(depth % 2) ans_1.push_back(now);
    else ans_2.push_back(now);

    for(int i=0;i<G[now].size();i+=1)
    {
        int j=G[now][i];
        if(j==fa) continue;

        dfs(j,now,depth+1);
    }
}

inline void print(const std::vector<int>& data)
{
    for(int i=0;i<std::min(n>>1,(int)data.size());i+=1)
    {
        printf("%d ",data[i]);
    }
    puts("");
}

int main()
{
    scanf("%d",&n);

    int x,y;
    for(int i=1;i<n;i+=1)
    {
        scanf("%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }

    dfs(1, -1, 1);
    
    print((ans_1.size()>=(n>>1))?ans_1:ans_2);

    return 0;
}

/*
struct Node
{
    int _id,_connect;
    bool operator<(const Node& other) const
    {
        return _connect>other._connect;
    }
};

std::vector<int> G[maxn];
std::priority_queue<Node> Q;

int n,connect[maxn];
bool done[maxn];

inline void init()
{
    for(int i=1;i<=n;i+=1)
    {
        G[i].clear();
        done[i] = false;
        connect[i] = 0;
    }
}

inline void build()
{
    for(int i=1;i<=n;i+=1)
    {
        Node _node{i,connect[i]};
        Q.push(_node);
    }
}

inline int get()
{
    if(Q.empty()) return -1;

    auto head = Q.top();
    Q.pop();

    while(done[head._id])
    {
        if(Q.empty()) return -1;
        head = Q.top();
        Q.pop();
    }
    done[head._id] = true;

    for(int i=0;i<G[head._id].size();i+=1)
    {
        int j = G[head._id][i];
        done[j] = true;
        for(int k=0;k<G[j].size();k+=1)
        {
            int l = G[j][k];
            connect[l] -= 1;
            if(head._id == l || done[l]) continue;

            Node _node{l,connect[l]};
            Q.push(_node);
        }
        
    }

    return head._id;
}

int main()
{
    scanf("%d",&n);
    init();

    int x,y;
    for(int i=1;i<n;i+=1)
    {
        scanf("%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
        connect[x] += 1;
        connect[y] += 1;
    }
    build();

    for(int i=0;i<(n>>1);i+=1)
    {
        printf("%d ",get());
    }

    return 0;
}

*/