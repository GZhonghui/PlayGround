#include <algorithm>
#include <iostream>
#include <cstdint>

const int maxn = 1e5 + 1;

int64_t n,a[maxn];

inline int64_t q_a(int64_t id)
{
    while(id > n) id -= n;
    return a[id];
}

int main()
{
    int64_t sum = 0;
    std::cin >> n;
    for(int i=1;i<=n;i+=1)
    {
        std::cin >> a[i];
        sum += a[i];
    }

    if(sum % 10)
    {
        std::cout << "No" << std::endl;
        return 0;
    }

    int64_t target = sum / 10;
    int64_t now = 0, l = 1, r = 0;
    while(l <= n)
    {
        r += 1;
        now += q_a(r);
        while(now > target)
        {
            now -= q_a(l);
            l += 1;
        }
        if(now == target)
        {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }
    std::cout << "No" << std::endl;

    return 0;
}