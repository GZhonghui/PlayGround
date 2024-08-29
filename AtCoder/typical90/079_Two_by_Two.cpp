// 思维题，没有想出来

// 按照一下顺序进行修改：（1，1）（1，2）（1，W），（2，1），（2，2），（2，W）
// 到此为止，没有“最优化”的部分（都是必须进行的步骤，策略没有优化的空间）

// todo 有一组数据是不对的

#include<algorithm>
#include<iostream>

const int maxn = 101;

int h,w,a[maxn][maxn],b[maxn][maxn];

int main()
{
    std::cin >> h >> w;
    for(int i=1;i<=h;i+=1)
    {
        for(int j=1;j<=w;j+=1)
        {
            std::cin >> a[i][j];
        }
    }

    for(int i=1;i<=h;i+=1)
    {
        for(int j=1;j<=w;j+=1)
        {
            std::cin >> b[i][j];
        }
    }

    int ans = 0;
    for(int i=1;i<h;i+=1)
    {
        for(int j=1;j<w;j+=1)
        {
            int diff = b[i][j] - a[i][j];
            a[i][j] += diff;
            a[i+1][j] += diff;
            a[i][j+1] += diff;
            a[i+1][j+1] += diff;
            ans += std::abs(diff);
        }
    }
    
    for(int i=1;i<=h;i+=1)
    {
        if(a[i][w] != b[i][w])
        {
            std::cout << "No" << std::endl;
            return 0;
        }
    }
    for(int j=1;j<=w;j+=1)
    {
        if(a[h][j] != b[h][j])
        {
            std::cout << "No" << std::endl;
            return 0;
        }
    }
    std::cout << "Yes" << std::endl;
    std::cout << ans << std::endl;

    return 0;
}