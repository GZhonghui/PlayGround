// 回忆一下，紫书上面的，开头介绍的那道“思维的体操”，关于蚂蚁的题目

#include<algorithm>
#include<iostream>
#include<cstdint>

const int maxn = 1e5+1;

int x[maxn],y[maxn],n;

int main()
{
    std::cin >> n;

    for(int i=1;i<=n;i+=1)
    {
        std::cin >> x[i] >> y[i];
    }

    std::sort(x+1,x+1+n);
    std::sort(y+1,y+1+n);

    int xx = x[(n+1)>>1], yy = y[(n+1)>>1];

    int64_t ans = 0;
    for(int i=1;i<=n;i+=1)
    {
        ans += (int64_t)std::abs(xx - x[i]) + std::abs(yy - y[i]);
    }
    std::cout << ans << std::endl;

    return 0;
}