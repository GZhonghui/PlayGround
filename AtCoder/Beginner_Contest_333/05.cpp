#include<algorithm>
#include<cstdio>
#include<utility>
#include<unordered_map>
#include<cmath>
#include<stack>

const int maxn=2e5+10;

int n;
std::pair<int,int> events[maxn];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i+=1)
    {
        int t,v;
        scanf("%d %d",&t,&v);
        events[i].first=t;
        events[i].second=v;
    }

    int max_of_now=0,now=0;

    std::unordered_map<int,int> needs;
    std::stack<int> ops;

    for(int i=n;i>=1;i-=1)
    {
        int t=events[i].first,v=events[i].second;
        if(!needs.count(v)) needs[v]=0;
        if(t==2)
        {
            needs[v]+=1;
            now+=1;
            max_of_now=std::max(max_of_now,now);
        }else
        {
            if(needs[v]>0)
            {
                needs[v]-=1;
                now-=1;
                ops.push(1);
            }else
            {
                ops.push(0);
            }
        }
    }

    if(now>0) puts("-1");
    else
    {
        printf("%d\n",max_of_now);
        while(!ops.empty())
        {
            printf("%d ",ops.top());
            ops.pop();
        }
        puts("");
    }

    return 0;
}