#include<algorithm>
#include<cstdio>
#include<cstdint>

// 算一下时间复杂度

typedef int64_t ll;
const ll maxn = 101;

ll n,p,q,data[maxn];

int main()
{
    scanf("%lld %lld %lld",&n,&p,&q);
    for(ll i=0; i<n; i+=1)
    {
        scanf("%lld",&data[i]);
    }

    ll counter = 0;

    for(ll a1=0;a1<n;a1+=1)
    for(ll a2=0;a2<a1;a2+=1)
    for(ll a3=0;a3<a2;a3+=1)
    for(ll a4=0;a4<a3;a4+=1)
    for(ll a5=0;a5<a4;a5+=1)
    {
        ll ans = 1;
        ans = (ans * data[a1]) % p;
        ans = (ans * data[a2]) % p;
        ans = (ans * data[a3]) % p;
        ans = (ans * data[a4]) % p;
        ans = (ans * data[a5]) % p;

        if (ans == q) counter += 1;
    }

    printf("%lld\n", counter);

    return 0;
}