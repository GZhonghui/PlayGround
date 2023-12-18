#include<algorithm>
#include<cstdio>

int n;
char ans[32];

void dfs(int now,int l,int r)
{
    if(now>=n)
    {
        if(l==r)
        {
            printf("%s\n",ans);
        }
        return;
    }

    ans[now]='(';
    dfs(now+1,l+1,r);
    if(r<l)
    {
        ans[now]=')';
        dfs(now+1,l,r+1);
    }
}

int main()
{
    scanf("%d",&n);
    dfs(0,0,0);

    return 0;
}