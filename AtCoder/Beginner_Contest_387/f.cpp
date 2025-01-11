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
#define pb push_back
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef uint64_t ull;
typedef long double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 2e3 + 200;
const ll mod = 998244353;
const ll inf = 1e9 + 8;
const f pi = acos(-1.0);
const f eps = 1e-6;

template<class T> struct point {
    T x,y;

    T dis2(const point &r) {
        T dx = x - r.x, dy = y - r.y;
        return dx * dx + dy * dy;
    }
};

typedef point<ll> pl;
typedef point<f> pf;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

ll n,m,a[maxn],dp[maxn][maxn];
bool is_root[maxn];

#include <atcoder/dsu>
using namespace atcoder;

dsu u(maxn);

void dfs(ll x) {
    rep(i,1,m) dp[x][i] = 1;
    for(ll i : g[x]) {
        if(is_root[i]) continue;
        dfs(i);
        ll sum = 0;
        rep(j,1,m) {
            sum += dp[i][j];
            sum %= mod;
            dp[x][j] *= sum;
            dp[x][j] %= mod;
        }
    }
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;
    rep(i,1,n) {
        cin >> a[i];
        g[a[i]].pb(i);
    }

    memset(is_root, false, sizeof(is_root));

    vector< vector<ll> > cs;

    rep(i,1,n) {
        if(u.same(i,a[i])) {
            ll _t = i;
            cs.pb(vector<ll>());
            do {
                is_root[_t] = true;
                cs.back().pb(_t);
                _t = a[_t];
            } while (_t != i);
        } else {
            u.merge(i,a[i]);
        }
    }

    ll ans = 1;
    for(vector<ll> &c : cs) {
        ll ans_c = 0;
        for(ll x : c) {
            dfs(x);
        }

        rep(i,1,m) {
            ll _t = 1;
            for(ll x : c) {
                _t = (_t * dp[x][i]) % mod;
            }
            ans_c += _t;
            ans_c %= mod;
        }

        ans = (ans * ans_c) % mod;
    }
    cout << ans << endl;

    return 0;
}