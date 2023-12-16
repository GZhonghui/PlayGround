#include<algorithm>
#include<cstdio>
#include<cstdint>

const int64_t mmax = 100000+10;

int64_t k,l,n;
int64_t p[mmax];

inline bool solve(int64_t test)
{
    int64_t nowk=0,ll=0;
    for(int64_t i=1;i<=n;i+=1)
    {
        int64_t len=p[i]-ll;
        if(len>=test)
        {
            nowk+=1;
            ll=p[i];
        }
    }
    if(l-ll<test) nowk-=1;

    // printf("%lld %s\n",test,nowk>=k?"Y":"N");

    return nowk>=k;
}

int main()
{
    scanf("%lld %lld %lld",&n,&l,&k);
    for(int64_t i=1;i<=n;i+=1)
    {
        scanf("%lld",&p[i]);
    }

    int64_t ll=1,rr=l;
    while(rr-ll>3)
    {
        int64_t m = (rr+ll)>>1;
        if(solve(m)) ll=m;
        else rr=m-1;
    }

    for(int64_t ans=rr;ans>=ll;ans-=1)
    {
        if(solve(ans))
        {
            printf("%lld\n",ans);
            break;
        }
    }

    return 0;
}
