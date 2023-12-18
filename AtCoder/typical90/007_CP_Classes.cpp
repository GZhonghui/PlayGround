#include<algorithm>
#include<cstdio>
#include<unordered_map>
#include<cstdint>

const int mmax=300000+10;

int64_t ns[mmax],qs[mmax],qs_sorted[mmax];
std::unordered_map<int64_t,int64_t> ans;

int main()
{
    int64_t n,q;
    scanf("%lld",&n);
    for(int i=0;i<n;i+=1) scanf("%lld",ns+i);
    std::sort(ns,ns+n);

    // for(int i=0;i<n;i+=1) printf("%lld,",ns[i]); puts("");

    scanf("%lld",&q);
    for(int i=0;i<q;i+=1) scanf("%lld",qs+i),qs_sorted[i]=qs[i];
    std::sort(qs_sorted,qs_sorted+q);

    int index=0;
    for(int i=0;i<q;i+=1)
    {
        int64_t now=qs_sorted[i];
        if(!ans.count(now)) ans[now]=std::abs(ns[index]-now);

        // printf("a com %d %d\n",now,ns[index]);

        while(index<n && ns[index]<now)
        {
            ans[now]=std::min(ans[now],std::abs(ns[index]-now));
            // printf("b com %d %d\n",now,ns[index]);
            index+=1;
        }
        if(index-1>=0)
        {
            ans[now]=std::min(ans[now],std::abs(ns[index-1]-now));
        }
        if(index<n)
        {
            ans[now]=std::min(ans[now],std::abs(ns[index]-now));
            // printf("c com %d %d\n",now,ns[index]);
        }
    }

    for(int i=0;i<q;i+=1)
    {
        printf("%lld\n",ans.count(qs[i])?ans[qs[i]]:0);
    }

    return 0;
}