#include<algorithm>
#include<iostream>
#include<cstdint>

const uint64_t mod = 1e9+7;
const uint64_t inv2 = 500000004;

uint64_t l,r;

inline uint64_t max_number(uint64_t length)
{
    uint64_t ans = 0;
    while(length--) ans = ans * 10 + 9;
    return ans;
}

inline uint64_t min_number(uint64_t length)
{
    uint64_t ans = 1;
    while(--length) ans *= 10;
    return ans;
}

inline uint64_t number_length(uint64_t number)
{
    uint64_t ans = 0;
    while(number)
    {
        number = number / 10;
        ans += 1;
    }

    return ans;
}

int main()
{
    std::cin >> l >> r;

    uint64_t ll = number_length(l);
    uint64_t rr = number_length(r);

    uint64_t ans = 0;

    for(uint64_t i = ll; i <= rr; i += 1)
    {
        uint64_t sl = std::max(l, min_number(i));
        uint64_t sr = std::min(r, max_number(i));

        ans += ((sr + sl) % mod) * ((sr - sl + 1) % mod) % mod * inv2 % mod * i % mod;
        ans %= mod;
    }

    std::cout << ans << std::endl;

    return 0;
}