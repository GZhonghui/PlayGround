#include<algorithm>
#include<cstdio>
#include<cstdint>

int main()
{
    int64_t n;
    scanf("%lld",&n);

    int ans=0;
    while(n)
    {
        if(n%2) break;
        n=n>>1; ans+=1;
    }

    printf("%d\n",ans);

    return 0;
}