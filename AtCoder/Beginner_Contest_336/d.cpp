#include<algorithm>
#include<cstdio>
#include<cstdint>

const int maxn=2e5+10;
int n,A[maxn],l[maxn],r[maxn];

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i+=1)
    {
        scanf("%d",A+i);
    }

    l[0]=0;
    for(int i=1;i<=n;i+=1)
    {
        l[i]=std::min(l[i-1]+1,A[i]);
    }

    r[n+1]=0;
    for(int i=n;i>=1;i-=1)
    {
        r[i]=std::min(r[i+1]+1,A[i]);
    }

    int ans=1;
    for(int i=1;i<=n;i+=1)
    {
        ans=std::max(ans,std::min(l[i],r[i]));
    }

    printf("%d\n",ans);
    return 0;
}
