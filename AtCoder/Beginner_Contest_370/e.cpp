// dp
// 还是自己一直想不到的那个点：DP[i]是对{i}的数据有要求的
// 在本题中，DP[i]是要求{i}位置一定被切断的

#include<algorithm>
#include<cstdio>
#include<cstdint>
#include<iostream>
#include<unordered_map>

const int64_t maxn = 2e5+1;
const int64_t mod = 998244353;

int64_t n,k,a[maxn],dp[maxn],sum[maxn],all = 0;
std::unordered_map<int64_t,int64_t> count_of_sum_is_k;

inline int64_t query_count_of_sum_is_k(int64_t k)
{
    return count_of_sum_is_k.count(k) ? count_of_sum_is_k[k] : 0;
}

int main()
{
    std::cin >> n >> k;
    for(int64_t i=1;i<=n;i+=1)
        std::cin >> a[i];

    dp[1] = 1, sum[1] = 0;
    count_of_sum_is_k[0] = 1, all = 1;
    for(int64_t i=2;i<=n+1;i+=1)
    {
        sum[i] = sum[i-1] + a[i-1];
        dp[i] = (mod + all - query_count_of_sum_is_k(sum[i] - k)) % mod;
        count_of_sum_is_k[sum[i]] = (query_count_of_sum_is_k(sum[i]) + dp[i]) % mod;
        all = (all + dp[i]) % mod;
    }

    std::cout << dp[n+1] << std::endl;

    return 0;
}