#include<algorithm>
#include<cstdio>
#include<cstdint>
#include<iostream>

const uint64_t mod = 1e9+7;

uint64_t pow(uint64_t base, uint64_t times)
{
    if(times == 0) return 1;
    if(times == 1) return base;

    uint64_t ans = pow(base, times>>1) % mod;
    
    ans = ans * ans % mod;
    if(times % 2) ans = ans * base % mod;

    return ans;
}

int main()
{
    uint64_t n,k;
    // scanf("%lld %lld",&n,&k);
    std::cin >> n >> k;

    uint64_t a = k;
    uint64_t b = k-1;
    
    uint64_t ans = 1;
    // 边界条件好难考虑
    if(n == 1)
    {
        ans = k;
    }else if(n == 2)
    {
        if(k == 1)
        {
            ans = 0;
        }else if(k == 2)
        {
            ans = 2;
        }else
        {
            ans = a * b % mod;
        }
    }else
    {
        if(k == 1 || k == 2)
        {
            ans = 0;
        }else
        {
            uint64_t c = pow(k-2,n-2);
            ans = (a * b % mod) * c % mod;
        }
    }
    // printf("%lld\n",ans); // WA
    std::cout << ans << std::endl;

    return 0;
}