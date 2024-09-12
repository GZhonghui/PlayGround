// https://www.luogu.com.cn/problem/UVA437
// 202409洛谷提交代码要实名认证。。。
// 中国政府真的疯了。。。

// 此代码尚未经过测试

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
const ll maxn = 100;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll a[maxn],b[maxn],c[maxn];

// index [1,n] rot [1,3] -> [1, 3*n]
inline ll id(ll index, ll rot) { return (index - 1) * 3 + rot; }
inline pair<ll,ll> id_to_rot(ll id)
{
    return make_pair<ll,ll>((id-1) / 3 + 1, (id-1) % 3 + 1);
}
inline pair<ll,ll> id_to_wh(ll id)
{
    pair<ll,ll> rot = id_to_rot(id);
    if(rot.second == 1) return make_pair(a[rot.first],b[rot.first]);
    if(rot.second == 2) return make_pair(b[rot.first],c[rot.first]);
    if(rot.second == 3) return make_pair(c[rot.first],a[rot.first]);
}
inline ll id_to_value(ll id)
{
    pair<ll,ll> rot = id_to_rot(id);
    if(rot.second == 1) return c[rot.first];
    if(rot.second == 2) return a[rot.first];
    if(rot.second == 3) return b[rot.first];
}
inline bool a_is_min(pair<ll,ll> a, pair<ll,ll> b)
{
    return min(a.first,a.second) < min(b.first,b.second) && max(a.first,a.second) < max(b.first,b.second);
}

ll dp[maxn],n;

ll search(ll id)
{
    if(dp[id] != -1) return dp[id];

    ll ans = 0, count = 3*n;

    for(ll j=1;j<=count;j+=1)
    {
        if(id==j) continue;
        if(a_is_min(id_to_wh(j), id_to_wh(id)))
        {
            // i -> j
            ans = max(ans, search(j));
        }
    }

    return dp[id] = ans + id_to_value(id);
}

int main()
{
    ll case_count = 0;
    while(true)
    {
        cin >> n;
        if(!n) break;

        for(ll i=1;i<=n;i+=1)
        {
            cin >> a[i] >> b[i] >> c[i];
        }

        memset(dp,-1,sizeof(dp));

        ll count = 3*n;
        ll ans = 0;

        for(ll i=1;i<=count;i+=1)
        {
            ans = max(ans, search(i));
        }

        cout << "Case " << (++case_count) << ": maximum height = " << ans << endl;
    }
    return 0;
}