// 第一道数位DP 庆祝！
// 自己推的公式，算到半夜才算清楚
// 非常重要和典型的一道例题
// 另外，可以看一下，官方的题解，是递推法
// 虽然能理解，但是不知道为什么递推可以保证顺序是正确的
// 所以自己用的是记忆化搜索
// 这道题用记忆化搜索，会有一个很麻烦的地方，需要倒推
// 看看bj10_t这里，是需要倒推的
// 另外，数位DP中，很关键的一个技巧是“是否沿着上界”
// 也就是搜索函数中的参数k
// 1表示沿着上界，则后面不能随便取
// 0表示没有沿着上界，则后面可以取0-9任意数字
// 总之，数位DP，后面继续学习吧

#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <cmath>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#define mk make_pair
#define rep(i, n) for (ll i = 1; i <= (n); i++)

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,len=0,num[32],dp[16][160][160][2];

ll se(ll d, ll i, ll j, ll k, ll s)
{
    if(dp[d][i][j][k] != -1) return dp[d][i][j][k];
    ll &ans = dp[d][i][j][k];

    ans = 0;
    if(d == 0)
    {
        if(i == 0 && j == 0 && k == 1) ans = 1;
        else ans = 0;
    }
    else 
    {
        for(ll t = 0; t <= 9; t += 1)
        {
            if(i >= t)
            {
                for(ll cs = 0;;cs += 1)
                {
                    ll bj10_t = j + cs * s;
                    ll bj10 = bj10_t - t;

                    if(bj10 > 10 * s) break;
                    if(bj10 >= 0 && bj10 % 10 == 0 && bj10 / 10 < s)
                    {
                        ll bj = bj10 / 10;
                        if(k == 1)
                        {
                            if(t == num[d])
                                ans += se(d-1, i-t, bj, 1, s);
                        }
                        else
                        {
                            if(t == num[d])
                                ans += se(d-1, i-t, bj, 0, s);
                            else if(t > num[d])
                                ans += se(d-1, i-t, bj, 0, s);
                            else if(t < num[d])
                                ans +=
                                    se(d-1, i-t, bj, 0, s) +
                                    se(d-1, i-t, bj, 1, s);
                        }
                    }
                }
            }
        }
    }

    return ans;
}

int main()
{
    // freopen("in.txt", "r", stdin);

    cin >> n;
    while(n) {
        num[++len] = n % 10;
        n /= 10;
    }
    rep(i, len) {
        ll j = len - i + 1;
        if(i < j) swap(num[i], num[j]);
    }

    ll ans = 0;
    rep(s, 14 * 9)
    {
        memset(dp,-1,sizeof(dp));
        ans += se(len,s,0,1,s) + se(len,s,0,0,s);
    }

    cout << ans << endl;

    return 0;
}