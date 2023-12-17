#include<algorithm>
#include<cstdio>
#include<cstdint>

int64_t c[3],n;

int main()
{
    scanf("%lld %lld %lld %lld",&n,c+0,c+1,c+2);
    std::sort(c,c+3);

    int64_t mmax=9999;
    int64_t ans=mmax;
    for(int i=mmax;i>=0;i-=1)
    {
        for(int j=mmax;j>=0;j-=1)
        {
            int64_t sum=c[2]*i+c[1]*j;
            if(sum<=n)
            {
                int64_t error=n-sum;
                if(error%c[0]==0)
                {
                    ans=std::min(ans,error/c[0]+i+j);
                }
            }
        }
    }

    printf("%lld\n",ans);

    return 0;
}
