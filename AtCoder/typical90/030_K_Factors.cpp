// 需要素数筛
// 关于时间复杂度，有点疑问，为什么这么快

#include<algorithm>
#include<cstdio>
#include<vector>
#include<cstring>

using namespace std;

const int maxn=1e7+10;
struct Sieve
{
    bool check[maxn],is_prime[maxn];
    vector<int> prime;
    void init()
    {
        memset(check,0,sizeof(check));
        memset(is_prime,0,sizeof(is_prime));
        prime.clear();
    }
    void calc(int n)
    {
        for(int i=2;i<=n;i++)
        {
            if(!check[i]) prime.push_back(i),is_prime[i]=true;
            for(int j=0;j<prime.size();j++)
            {
                if(i*prime[j]>n) break;
                check[i*prime[j]]=true;
                if(i%prime[j]==0) break;
            }
        }
    }
}solver;

int counter[maxn];

int main()
{
    int n,k;
    scanf("%d %d",&n,&k);
    solver.init();
    solver.calc(n);

    memset(counter,0,sizeof(counter));

    for(int i=0;i<solver.prime.size();i+=1)
    {
        int _value = solver.prime[i];
        for(int j=_value;j<=n;j+=_value)
        {
            counter[j] += 1;
        }
    }

    int ans = 0;
    for(int i=2;i<=n;i+=1)
    {
        if(counter[i]>=k) ans += 1; // printf("%d\n",i);
    }
    printf("%d\n",ans);

    return 0;
}