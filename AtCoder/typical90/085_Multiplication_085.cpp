#include <algorithm>
#include <iostream>
#include <cmath>

// 比想象的简单
// 计数相关的问题，可以大概估计一下结果的范围
// 比如结果如果要取模，就不可能【直接搜索计数】（每次+1+1的计数）
// 结果范围如果比较小的话，有可能可以直接搜索

int main()
{
    int64_t k;
    std::cin >> k;

    int64_t ans = 0;

    for(int64_t a = 1; a*a*a <= k; a += 1)
    {
        for(int64_t b = a; a*b*b <= k; b += 1)
        {
            if(k % (a*b) == 0)
            {
                ans += 1;
            }
        }
    }

    std::cout << ans << std::endl;

    return 0;
}