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
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll maxm = 1e6 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,m,a[maxn],d[maxn << 2],count_remain[maxm];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    memset(count_remain,0,sizeof(count_remain));

    cin >> n >> m;
    rep(i,1,n) cin >> a[i];

    d[1] = 0;
    rep(i, 2, n * 3) {
        ll ii = i - 1; while(ii > n) ii -= n;
        d[i] = d[i-1] + a[ii];
    }

    rep(i, 1, n) {
        count_remain[d[i] % m] += 1;
    }

    ll ans = 0;
    rep(i, 1, n) {
        ans += count_remain[d[i] % m] - 1;
        
        ll ii = i + n;
        count_remain[d[i] % m] -= 1;
        count_remain[d[ii] % m] += 1;
    }

    cout << ans << endl;

    return 0;
}

// 读错题目了...方向是确定的
int main_bck()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    memset(count_remain,0,sizeof(count_remain));

    cin >> n >> m;
    rep(i,1,n) cin >> a[i];

    d[1] = 0;
    rep(i, 2, n * 3) {
        ll ii = i - 1; while(ii > n) ii -= n;
        d[i] = d[i-1] + a[ii];
    }

    ll left_idx = 1;
    rep(i, 1, n) {
        count_remain[d[i] % m] += 1;
    }

    ll ans = 0;
    rep(idx, n+1, n << 1) {
        if(idx > left_idx + n - 1) {
            count_remain[d[idx] % m] += 1;
            count_remain[d[left_idx] % m] -= 1;
            left_idx += 1;
        }

        while(left_idx < idx) {
            ll right_idx = left_idx + n;
            ll left_dis = d[idx] - d[left_idx];
            ll right_dis = d[right_idx] - d[idx];
            if(left_dis > right_dis) {
                count_remain[d[left_idx] % m] -= 1;
                count_remain[d[right_idx] % m] += 1;
                left_idx += 1;
            }
            else break;
        }

        ans += count_remain[d[idx] % m] - 1;

    }

    cout << (ans >> 0) << endl;

    return 0;
}
