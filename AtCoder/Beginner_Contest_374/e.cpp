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

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 110;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,x,a[maxn],p[maxn],b[maxn],q[maxn];

void min_weight(ll n, ll value_limit, ll* weights, ll* values, ll* ans)
{
    for(ll i=1; i<=value_limit; i+=1)
    {
        ans[i] = inf;
    }
    ans[0] = 0;

    for(ll i=1; i<=n; i+=1)
    {
        for(ll j=value_limit; j>=1; j-=1)
        {
            if(j >= values[i] && ans[j - values[i]] < inf && ans[j - values[i]] + weights[i] < ans[j])
            {
                ans[j] = ans[j - values[i]] + weights[i];
            }
        }
    }
}

bool check(ll target)
{
    // cout << target << endl;
    ll cost = 0;
    for(ll i=1;i<=n;i+=1)
    {
        // >= target min_cost is ?

        // 这里用背包的思路做会太慢
        /*
        ll dp[maxn];
        ll weights[2] = {p[i],q[i]};
        ll values[2] = {a[i],b[i]};
        min_weight(2,target,weights,values,dp);
        */

        // 这个思路很巧妙呢
        ll local_cost = INT64_MAX;
        for(ll j=0;j<=b[i];j+=1) {
            ll offset = target - a[i] * j;
            if(offset < 0) continue;
            ll other_count = (offset / b[i]) + ((offset % b[i]) ? 1 : 0);
            local_cost = min(local_cost, p[i] * j + q[i] * other_count);
        }

        for(ll j=0;j<=a[i];j+=1) {
            ll offset = target - b[i] * j;
            if(offset < 0) continue;
            ll other_count = (offset / a[i]) + ((offset % a[i]) ? 1 : 0);
            local_cost = min(local_cost, p[i] * other_count + q[i] * j);
        }
        cost += local_cost;
    }

    return cost <= x;
}

int main()
{
    cin >> n >> x;
    for(ll i=1;i<=n;i+=1)
    {
        cin >> a[i] >> p[i] >> b[i] >> q[i];
    }

    ll l = 0, r = 1e12;
    while(r - l > 3)
    {
        ll mid = (l+r) >> 1;
        if(check(mid)) l = mid;
        else r = mid -1;
    }

    for(ll i=r;i>=l;i-=1)
    {
        if(check(i)) {
            cout << i << endl;
            break;
        }
    }

    return 0;
}