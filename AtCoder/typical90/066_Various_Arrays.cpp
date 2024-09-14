// 猪脑过载

#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
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
const ll maxn = 103;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,l[maxn],r[maxn];

int main()
{
    cin >> n;
    for(ll i=1;i<=n;i+=1)
    {
        cin >> l[i] >> r[i];
    }

    f ans = 0;
    for(ll i=1;i<n;i+=1)
    {
        for(ll j=i+1;j<=n;j+=1)
        {
            // i<j
            // 这一段的区间计算，需要再好好想想，梳理一下，有点复杂，写的时候猪脑爆炸了
            ll l1 = l[i], r1 = r[i], l2 = l[j], r2 = r[j];
            ll total = (r1 - l1 + 1) * (r2 - l2 + 1);
            l1 = max(l1, l2), r2 = min(r2, r1);
            if(l1 > r1) continue;
            if(l1 > r2) { ans +=1; continue; }

            ll up = 0;
            ll a1 = l1 - l2;
            ll count = r2 - l1 + 1;
            up += (((a1 + a1 + count - 1) * count) >> 1) + max(r1 - r2, (ll)0) * (r2 - l2 + 1);
            ans += (f)up / total;

            // cout << i << " " << j << ": " << up << " / " << total << endl;
        }
    }

    cout << fixed << setprecision(10) << ans << endl;
    return 0;
}