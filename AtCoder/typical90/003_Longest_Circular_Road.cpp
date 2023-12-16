#include<algorithm>
#include<cstdio>
#include<vector>

const int maxn=100000+10;

int n;
std::vector<int> g[maxn];

void dfs(int f,int node_id,int now_depth,int& max_depth,int* side)
{
    if(now_depth>max_depth)
    {
        max_depth=now_depth;
        if(side) *side=node_id;
    }

    for(int i=0,_size=g[node_id].size();i<_size;i+=1)
    {
        int target=g[node_id][i];
        if(target!=f)
        {
            dfs(node_id,target,now_depth+1,max_depth,side);
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i+=1)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int max_depth=0,side=1;
    dfs(-1,1,0,max_depth,&side);
    // printf("%d\n",side);
    dfs(-1,side,0,max_depth,nullptr);
    printf("%d\n",max_depth+1);

    return 0;
}
