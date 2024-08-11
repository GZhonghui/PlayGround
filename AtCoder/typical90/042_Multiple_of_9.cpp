#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdint>
#include<cstring>

// 组合数是不行的，没有办法可以限制单个数字的范围在[1,9]

using namespace std;
typedef int64_t ll;

const ll maxn = 100000 + 10;
const ll global_mod = 1e9+7;

struct Quick_C
{
    ll Jc[maxn],mod;
    void pre_cal()
    {
        Jc[0]=Jc[1]=1;
        for(ll i=2;i<maxn;i++)
            Jc[i]=Jc[i-1]*i%mod;
    }
    void exgcd(ll a,ll b,ll &x,ll &y)
    {
        if(!b) x=1,y=0;
        else
        {
            exgcd(b,a%b,y,x);
            y-=x*(a/b);
        }
    }
    ll niYuan(ll a,ll b)
    {
        ll x,y;
        exgcd(a,b,x,y);
        return (x+b)%b;
    }
    ll cal_C(ll a,ll b)
    {
        return Jc[a]*niYuan(Jc[b],mod)%mod*niYuan(Jc[a-b],mod)%mod;
    }
}solver;

ll mem[maxn];

ll dp(int remain)
{
    if(mem[remain] != -1) return mem[remain];

    ll ans = -1;

    if(remain == 1 || remain == 0)
    {
        ans = 1;
    }else
    {
        ans = 0;
        for(ll i = 1; i <= std::min(9, remain); i += 1)
        {
            ans = (ans + dp(remain - i)) % global_mod;
        }
    }

    return mem[remain] = ans;
}

int main()
{
    // solver.mod = global_mod;
    // solver.pre_cal();

    memset(mem,-1,sizeof(ll)*maxn);

    ll k;
    scanf("%lld",&k);
    
    if(k%9)
    {
        printf("0\n");
        return 0;
    }

    /*
    ll l = k/9-1, r=k-1;
    ll ans = 0;
    for(ll i=l;i<=r;i+=1)
    {
        ans = (ans + solver.cal_C(k-1,i) % global_mod) % global_mod;
    }
    printf("%lld\n",ans);
    */

   printf("%lld\n",dp(k));

    return 0;
}
