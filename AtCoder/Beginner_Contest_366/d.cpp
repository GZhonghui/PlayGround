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
const ll maxn = 100 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,q,a[maxn][maxn][maxn],sum[maxn][maxn][maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i, 1, n) rep(j, 1, n) rep (k, 1, n) cin >> a[i][j][k];

    memset(sum,0,sizeof(sum));
    rep(i, 1, n) {
        rep(j, 1, n) rep(k, 1, n) {
            sum[i][j][k] = sum[i][j-1][k] + sum[i][j][k-1] - sum[i][j-1][k-1] + a[i][j][k];
        }
    }

    cin >> q; while(q--) {
        static ll li,ri,lj,rj,lk,rk;
        cin >> li >> ri >> lj >> rj >> lk >> rk;

        ll ans = 0;
        rep(i, li, ri) {
            ans += sum[i][rj][rk] + sum[i][lj-1][lk-1] - sum[i][lj-1][rk] - sum[i][rj][lk-1];
        }
        cout << ans << endl;
    }

    return 0;
}