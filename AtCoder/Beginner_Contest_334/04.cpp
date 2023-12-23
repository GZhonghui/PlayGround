#include<algorithm>
#include<cstdio>
#include<cmath>
#include<unordered_map>
#include<cstdint>

const int64_t maxn=2e5+10;

std::unordered_map<int64_t,int64_t> ans;
int64_t n,q,r[maxn],qs[maxn],qs_sorted[maxn];

int main()
{
    scanf("%lld %lld",&n,&q);
    for(int64_t i=1;i<=n;i+=1)
    {
        scanf("%lld",r+i);
    }
    for(int64_t i=1;i<=q;i+=1)
    {
        scanf("%lld",qs+i);
        qs_sorted[i]=qs[i];
    }

    std::sort(r+1,r+1+n);
    std::sort(qs_sorted+1,qs_sorted+1+q);

    int64_t need=0;
    int qs_index=1;
    for(int64_t i=1;i<=n;i+=1)
    {
        need+=r[i];
        while(qs_index<=q&&qs_sorted[qs_index]<need)
        {
            ans[qs_sorted[qs_index]]=i-1;
            qs_index+=1;
        }
    }

    for(int64_t i=1;i<=q;i+=1)
    {
        int64_t q_number=qs[i];
        printf("%lld\n",ans.count(q_number)?ans[q_number]:n);
    }

    return 0;
}