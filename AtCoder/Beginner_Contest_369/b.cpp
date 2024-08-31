#include<algorithm>
#include<iostream>

int main()
{
    int ans = 0, l = -1, r = -1, n;
    std::cin >> n;
    while(n--)
    {
        int a;
        char s;
        std::cin >> a >> s;
        if(s=='L')
        {
            if(l != -1) ans += std::abs(a - l); l = a;
        }
        if(s=='R')
        {
            if(r != -1) ans += std::abs(a - r); r = a;
        }
    }
    std::cout << ans << std::endl;

    return 0;
}