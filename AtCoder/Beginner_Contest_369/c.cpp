#include<algorithm>
#include<iostream>
#include<cstdint>

const int64_t maxn = 2e5+1;

int64_t n,a[maxn];

inline int64_t add_ans(int64_t len)
{
    int64_t ans = 0;
    if(len >= 3)
    {
        ans += (1 + len - 2) * (len - 2) / 2;
    }

    return ans;
}

int main()
{
    std::cin >> n;

    for(int64_t i=1;i<=n;i+=1)
    {
        std::cin >> a[i];
    }

    if(n == 1)
    {
        std::cout << 1 << std::endl;
        return 0;
    }

    int64_t ans = n + (n - 1);

    int64_t diff = a[2] - a[1] + 1, len = 0;
    for(int64_t i=2;i<=n;i+=1)
    {
        int64_t _diff = a[i] - a[i-1];
        if(diff != _diff)
        {
            // add ans
            ans += add_ans(len);
            diff = _diff;
            len = 2;
        }else
        {
            len += 1;
        }
    }
    ans += add_ans(len);
    std::cout << ans << std::endl;

    return 0;
}