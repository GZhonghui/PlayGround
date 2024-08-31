#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdint>

const int64_t maxn = 2e5+1;

int64_t n,a[maxn];

int64_t mem[maxn][2],done[maxn][2];

int64_t dp(int64_t i, int64_t bit)
{
    if(done[i][bit]) return mem[i][bit];
    done[i][bit] = 1;

    int64_t ans = 0;
    if(i == 1)
    {
        if(bit == 1) ans = a[1];
        else if(bit == 0) ans = 0;
    }else
    {
        if(bit == 1)
        {
            ans = std::max(dp(i-1,1), dp(i-1,0) + a[i]);
        }else if(bit == 0)
        {
            ans = std::max(dp(i-1,0), dp(i-1,1) + a[i] * 2);
        }
    }

    return mem[i][bit] = ans;
}

int main()
{
    std::cin >> n;
    for(int64_t i=1;i<=n;i+=1)
    {
        std::cin >> a[i];
    }

    memset(done,0,sizeof(done));
    int64_t ans = std::max(dp(n,0),dp(n,1));
    std::cout << ans << std::endl;

    return 0;
}