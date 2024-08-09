#include<iostream>
#include<cstdio>
#include<algorithm>

const int maxn = 11;
const int inf=0xffffff;

bool connect[maxn][maxn], used[maxn];
int assignment[maxn], data[maxn][maxn], n;

int dfs(int now, int cost)
{
    if(now >= n)
    {
        return cost;
    }

    int best = inf;
    for(int i=1;i<=n;i+=1)
    {
        if(!used[i] && ((now == 0) || (connect[assignment[now]][i])))
        {
            used[i] = true;
            assignment[now + 1] = i;
            int ans = dfs(now + 1, cost + data[i][now + 1]);
            used[i] = false;

            if(ans == -1) continue;

            best = std::min(best, ans);
        }
    }

    return (best == inf)? -1 : best;
}

int main()
{
    scanf("%d",&n);

    for(int i=1;i<=n;i+=1)
    {
        for(int j=1;j<=n;j+=1)
        {
            connect[i][j]=true;
            scanf("%d",&(data[i][j]));
        }
    }

    int m;
    scanf("%d",&m);

    for(int i=0;i<m;i+=1)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        connect[x][y] = connect[y][x] = false;
    }

    for(int i=1;i<=n;i+=1)
    {
        used[i] = false;
    }

    printf("%d",dfs(0, 0));

    return 0;
}


// https://acm.hdu.edu.cn/showproblem.php?pid=2544 最短路

/*
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int maxn=105;
const int inf=0xffffff;
struct Edge{
    int to,dis;
};
struct Node{
    int id,dis;
    bool operator< (const Node& r) const{
        return dis>r.dis;
    }
};
vector<Edge> edges;
vector<int> G[maxn];
int n,m,d[maxn];
bool done[maxn];
void init()
{
    for(int i=1;i<=n;i++) G[i].clear(),done[i]=false,d[i]=inf;
}

bool connect[maxn][maxn];
int direct_distance[maxn][maxn];

int main()
{
    scanf("%d",&n);
    init();

    for(int i=1;i<=n;i+=1)
    {
        for(int j=1;j<=n;j+=1)
        {
            connect[i][j]=true;
        }
    }

    for(int i=1;i<=n;i+=1)
    {
        for(int j=1;j<=n;j+=1)
        {
            scanf("%d",&(direct_distance[i][j]));
        }
    }

    scanf("%d",&m);

    for(int i=0;i<m;i+=1)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        connect[x][y] = false;
        connect[y][x] = false;
    }

    for(int i=1;i<=n;i+=1)
    {
        for(int j=1;j<=n;j+=1)
        {
            if(i!=j && connect[i][j])
            {
                Edge e={j,direct_distance[i][j]};
                edges.push_back(e);
                G[i].push_back(edges.size()-1);
            }
        }
    }

    d[1]=0;
    Node start={1,0};
    priority_queue<Node> Q;
    Q.push(start);
    while(!Q.empty())
    {
        Node now=Q.top();Q.pop();
        int x=now.id;
        if(done[x]) continue;
        done[x]=true;
        for(int i=0;i<G[x].size();i++)
        {
            Edge& e=edges[G[x][i]];
            if(d[e.to]>now.dis+e.dis)
            {
                d[e.to]=now.dis+e.dis;
                Node Ins={e.to,d[e.to]};
                Q.push(Ins);
            }
        }
    }
    printf("%d\n",d[n]);

    return 0;
}
*/