#include<algorithm>
#include<cstdio>
#include<cstdint>

typedef int64_t ll;

const ll maxn=1e5+1;

ll data[maxn],diff[maxn];

int main()
{
    ll n,q;
    scanf("%lld %lld",&n,&q);
    for(int i=1;i<=n;i+=1)
    {
        scanf("%lld",data + i);
        diff[i-1] = data[i-1] - data[i];
    }

    ll ans = 0;
    for(int i=1;i<n;i+=1)
    {
        ans += std::abs(diff[i]);
    }

    // printf("%d\n",ans);

    ll l,r,v;
    while(q--)
    {
        scanf("%lld %lld %lld",&l,&r,&v);
        if(l > 1)
        {
            ans -= std::abs(diff[l-1]);
            diff[l-1] -= v;
            ans += std::abs(diff[l-1]);
        }

        if(r < n)
        {
            ans -= std::abs(diff[r]);
            diff[r] += v;
            ans += std::abs(diff[r]);
        }

        // for(int i=1;i<n;i+=1) printf("%d%c",diff[i],i==(n-1)?'\n':' ');
        printf("%lld\n",ans);
    }
    return 0;
}