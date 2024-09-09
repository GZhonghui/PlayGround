#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdint>

int64_t n,k;
std::vector<int64_t> a;

int main()
{
    std::cin >> n >> k;
    for(int i=0;i<n;i+=1)
    {
        int _a,_b;
        std::cin >> _a >> _b;
        a.push_back(_b);
        a.push_back(_a - _b);
    }

    std::sort(a.begin(),a.end());

    int64_t count = k, ans = 0;
    for(int i=a.size()-1;i>=0;i-=1)
    {
        ans += a[i];
        if(--count <= 0) break;
    }

    std::cout << ans << std::endl;

    return 0;
}