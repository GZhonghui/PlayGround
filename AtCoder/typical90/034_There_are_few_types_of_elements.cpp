#include<algorithm>
#include<cstdio>
#include<unordered_set>
#include<unordered_map>

const int maxn=1e5+10;

int n,k,l=0,data[maxn];
std::unordered_map<int,int> counter;

inline void in(int a)
{
    if(!counter.count(a)) counter[a] = 0;
    counter[a] += 1;
}

inline void out()
{
    while(counter.size()>k)
    {
        l += 1;
        counter[data[l]] -= 1;
        if(counter[data[l]] <= 0)
        {
            counter.erase(data[l]);
        }
    }
}

int main()
{
    scanf("%d %d",&n,&k);

    int ans = 1;
    for(int i=1;i<=n;i+=1)
    {
        scanf("%d",&data[i]);
        in(data[i]);
        out();
        ans = std::max(ans, i-l);
    }
    printf("%d\n",ans);

    return 0;
}