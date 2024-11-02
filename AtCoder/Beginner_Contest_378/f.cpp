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

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef uint64_t ull;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
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

ll n,d[maxn],v[maxn];

ll dfs(ll now)
{
    v[now] = 1;

    ll res = 0;

    for(ll to : g[now]) {
        if(!v[to] && d[to] == 3) {
            res += dfs(to);
        }
        if(d[to] == 2) res += 1;
    }

    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    memset(d,0,sizeof(d));
    memset(v,0,sizeof(v));

    cin >> n;
    rep(i,1,n-1) {
        static ll a,b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
        d[a] += 1;
        d[b] += 1;
    }

    ll ans = 0;
    rep(i,1,n) {
        if(!v[i] && d[i] == 3) {
            ll s = dfs(i);
            ans += s * (s-1) / 2;
        }
    }
    cout << ans << endl;

    return 0;
}