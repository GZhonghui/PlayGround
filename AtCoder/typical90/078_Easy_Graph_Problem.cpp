#include<algorithm>
#include<iostream>
#include<cstring>

const int maxn = 100000 + 1;

int counter[maxn];

int main()
{
    memset(counter,0,sizeof(counter));

    int n,m;
    std::cin >> n >> m;
    for(int i=1;i<=m;i+=1)
    {
        int x,y;
        std::cin >> x >> y;
        counter[std::max(x,y)] += 1;
    }

    int ans = 0;
    for(int i=1;i<=n;i+=1)
    {
        if(counter[i] == 1) ans += 1;
    }
    std::cout << ans << std::endl;

    return 0;
}