#include<algorithm>
#include<cstdio>
#include<iostream>

const int maxn = 100 + 1;

int a[maxn][maxn];

int main()
{
    int n;
    std::cin >> n;
    for(int i=1;i<=n;i+=1)
    {
        for(int j=1;j<=i;j+=1)
        {
            std:: cin >> a[i][j];
        }
    }

    int ans = 1;
    for(int i=1;i<=n;i+=1)
    {
        ans = a[std::max(i,ans)][std::min(i,ans)];
    }
    std::cout << ans << std::endl;

    return 0;
}