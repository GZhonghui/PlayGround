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
#define rep(i, n) for (int i = 1; i <= (n); i++)

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 100 + 8;
const ll max_sumb = 1510;
const ll max_avg = 510;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

// dp[2][x][x]这是一个重要的技巧
// 防止数据污染，所以0->1，然后1->0，如此往复
// 用1个变量p表示当前数据是0还是1，然后[p]->[1-p]
ll n,a[maxn],b[maxn],sum = 0,dp[2][max_avg][max_avg],p = 0;

int main()
{
    cin >> n;
    rep(i,n) {
        cin >> a[i] >> b[i];
        sum += b[i];
    }

    if(sum % 3) {
        cout << -1 << endl;
        return 0;
    }

    ll avg = sum / 3, local_sum = 0;
    rep(i, max_avg) rep(j, max_avg) dp[p][i-1][j-1] = inf;
    dp[p][0][0] = 0;
    rep(i,n) {
        local_sum += b[i];
        for(ll t1 = 0; t1 <= avg; t1++)
        for(ll t2 = 0; t2 <= avg; t2++) {
            ll t3 = local_sum - t1 - t2;
            dp[1-p][t1][t2] = inf;
            if(t3 < 0) {
                continue;
            }

            ll bt1 = t1, bt2 = t2, bt3 = t3;
            {
                ll bt1 = t1 - b[i];
                if(bt1 >= 0 && dp[p][bt1][bt2] < inf) {
                    dp[1-p][t1][t2] = min(dp[1-p][t1][t2], dp[p][bt1][bt2] + (a[i] == 1 ? 0 : 1));
                }
            }
            {
                ll bt2 = t2 - b[i];
                if(bt2 >= 0 && dp[p][bt1][bt2] < inf) {
                    dp[1-p][t1][t2] = min(dp[1-p][t1][t2], dp[p][bt1][bt2] + (a[i] == 2 ? 0 : 1));
                }
            }
            {
                ll bt3 = t3 - b[i];
                if(bt3 >= 0 && dp[p][bt1][bt2] < inf) {
                    dp[1-p][t1][t2] = min(dp[1-p][t1][t2], dp[p][bt1][bt2] + (a[i] == 3 ? 0 : 1));
                }
            }
        }
        p = 1 - p;
    }

    cout << (dp[p][avg][avg] == inf ? -1 : dp[p][avg][avg]) << endl;

    return 0;
}