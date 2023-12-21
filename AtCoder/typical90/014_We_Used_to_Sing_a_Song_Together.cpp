#include<algorithm>
#include<cstdio>
#include<cstdint>
#include<cmath>

const int maxn=100000+10;

int64_t a[maxn],b[maxn],n;

int main()
{
    scanf("%lld",&n);
    for(int i=0;i<n;i+=1) scanf("%lld",a+i);
    for(int i=0;i<n;i+=1) scanf("%lld",b+i);
    std::sort(a,a+n);
    std::sort(b,b+n);
    
    int64_t ans=0;
    for(int i=0;i<n;i+=1) ans+=std::abs(a[i]-b[i]);
    printf("%lld\n",ans);

    return 0;
}