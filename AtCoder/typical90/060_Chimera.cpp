#include <algorithm>
#include <iostream>
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const ll dx[4] = {0,0,1,-1};
const ll dy[4] = {1,-1,0,0};

const ll mod = 1e9+7;
const ll maxn = 300000 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

// 自己写的版本
// todo 求lis的下标序列
// numbers[0,numbers_count)
int lis(int numbers_count, int* numbers, int* dp, bool allow_equal = true)
{
    int buffer[numbers_count + 1];
    buffer[0] = 1, buffer[1] = numbers[0], dp[0] = 1;

    for(int i = 1; i < numbers_count; i += 1)
    {
        int index = allow_equal
            ?std::upper_bound(buffer+1, buffer+1+buffer[0], numbers[i]) - buffer - 1
            :std::lower_bound(buffer+1, buffer+1+buffer[0], numbers[i]) - buffer - 1;
        if(index >= buffer[0])
        {
            buffer[0] += 1;
            buffer[buffer[0]] = numbers[i];
        }else
        {
            buffer[index+1] = numbers[i];
        }
        dp[i] = index + 1;
    }

    return buffer[0];
}

int n,nums[2][maxn],dp[2][maxn];

int main()
{
    cin >> n;
    for(int i=0;i<n;i+=1)
    {
        cin >> nums[0][i];
        nums[1][n-1-i] = nums[0][i];
    }
    lis(n,nums[0],dp[0],false);
    lis(n,nums[1],dp[1],false);

    int ans = 0;
    for(int i=0;i<n;i+=1)
    {
        ans = max(ans, dp[0][i] + dp[1][n-1-i]);
    }
    cout << ans - 1 << endl;

    return 0;
}