#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cstdint>

const int maxn = 1e5+1;

int done[maxn];

inline int step(int v)
{
    int ans = v;
    while(v)
    {
        ans += v%10;
        v /= 10;
    }
    return ans % (int)1e5;
}

int solver(int n, int64_t k)
{
    memset(done,0,sizeof(done));

    bool first = true;
    int64_t index = done[n] = 1;
    while(index <= k) // TLE只有可能发生在这里
    {
        index += 1;
        n = step(n);

        if(done[n])
        {
            if(first) // 如果不加这里（first判定Do Once）会TLE，为什么？还没有想明白是什么情况会TLE
            // 难道是数据超范围了？
            // 这里确实应该有first，否则计算出来的loop是不对的，但是为什么会TLE就不懂了
            // AtCoder能看数据就好了
            {
                int64_t loop = index - done[n];
                index += ((k-index) / loop) * loop;
                first = false;
            }
        }else
        {
            done[n] = index;
        }
    }
    printf("%d\n",n);

    return 0;
}

int main()
{
    int n;
    int64_t k;
    scanf("%d %lld",&n,&k);
    solver(n,k);

    // solver(0,k);
    for(int i=0;i<1e5;i+=1) printf("i = %d,",i),solver(i,k);

    return 0;
}