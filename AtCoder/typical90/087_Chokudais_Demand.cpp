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
const ll maxn = 50;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll dist[maxn][maxn],dist_bck[maxn][maxn],n,p,k;

inline void floydWarshall(ll selected_value) {
    memcpy(dist,dist_bck,sizeof(ll)*maxn*maxn);
    for(ll i=1;i<=n;i+=1) for(ll j=1;j<=n;j+=1)
        dist[i][j] = (dist[i][j] == -1) ? selected_value : dist[i][j];

    for (ll k = 1; k <= n; ++k) {
        for (ll i = 1; i <= n; ++i) {
            for (ll j = 1; j <= n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

inline ll check(ll selected_value)
{
    floydWarshall(selected_value);

    ll count = 0;
    for(ll i=1;i<n;i+=1)
    {
        for(ll j=i+1;j<=n;j+=1)
        {
            if(dist[i][j] <= p) count += 1;
        }
    }

    return count;
}

inline ll search(ll k)
{
    ll l = 0, r = 1e9 + 100;
    while(r - l > 3)
    {
        ll mid = (l + r) >> 1;
        ll count = check(mid);
        if(count < k)
        {
            r = mid - 1;
        }else l = mid;
    }

    ll r_to = r;
    while(r_to >= l)
    {
        if(check(r_to) >= k) break;
        r_to -= 1;
    }

    return r_to;
}

int32_t main() {
    cin >> n >> p >> k; // 正好有K组 P是距离限制

    for(ll i=1;i<=n;i+=1)
    {
        for(ll j=1;j<=n;j+=1)
        {
            cin >> dist_bck[i][j];
        }
    }

    if(check(1e9 + 100) > k) {
        cout << 0 << endl;
        return 0;
    }

    if(check(1e9 + 100) == k)
    {
        cout << "Infinity" << endl;
        return 0;
    }

    ll l = search(k+1) + 1, r = search(k);
    /*
    while(check(l) > k) l += 1;
    while(l-1 >= 0 && check(l-1) <= k) l -= 1;

    while(check(r) < k) r -= 1;
    while(check(r+1) >= k) r += 1;
    */
    /*
    if(l > 1e9 + 1)
    {
        cout << 0 << endl;
    }else if(r > 1e9 + 1)
    {
        cout << "Infinity" << endl;
    }else cout << r - l << endl;
    */
    cout << r - l + 1 << endl;

    return 0;
}
