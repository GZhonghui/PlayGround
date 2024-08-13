#include<algorithm>
#include<cstdio>
#include<unordered_map>
#include<cstdint>

std::unordered_map<int,int> counter[3];

int main()
{
    int n;
    scanf("%d",&n);

    for(int j=0;j<3;j+=1)
    for(int i=0;i<n;i+=1)
    {
        int _v;
        scanf("%d",&_v);
        if(!counter[j].count(_v%46)) counter[j][_v%46] = 0;
        counter[j][_v%46] += 1;
    }

    int64_t ans = 0;
    for(int i=0;i<46;i+=1)
    for(int j=0;j<46;j+=1)
    for(int k=0;k<46;k+=1)
    {
        if((i+j+k)%46 == 0)
        {
            ans += (int64_t)counter[0][i] * counter[1][j] * counter[2][k];
        }
    }
    printf("%lld\n",ans);

    return 0;
}