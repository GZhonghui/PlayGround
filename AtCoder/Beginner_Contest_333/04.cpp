#include<algorithm>
#include<cstdio>
#include<vector>
#include<cmath>

const int maxn=3e5+10;

int n;
std::vector<int> g[maxn];

int dfs(int f,int now_node,int* max_sub)
{
    int sum=1;
    if(max_sub) *max_sub=0;
    for(int i=0,_size=g[now_node].size();i<_size;i+=1)
    {
        int target=g[now_node][i];
        if(f==target) continue;

        int ans=dfs(now_node,target,nullptr);
        if(max_sub)
        {
            *max_sub=std::max(*max_sub,ans);
        }
        sum+=ans;
    }

    return sum;
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

    int ans;
    int sum = dfs(-1,1,&ans);
    printf("%d\n",n-ans);

    return 0;
}