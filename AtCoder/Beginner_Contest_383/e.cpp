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
    ll from,to,dis;

    bool operator<(const edge &e) const {
        return dis < e.dis;
    }
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

ll n,m,k,a[maxn],b[maxn],fa[maxn],cnt[maxn][2];

ll root(ll x) {
    return fa[x] == x ? x : fa[x] = root(fa[x]);
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m >> k;
    rep(i,1,m) {
        ll u,v,w;
        cin >> u >> v >> w;
        edges.pb((edge){u,v,w});
    }
    rep(i,1,k) cin >> a[i];
    rep(i,1,k) cin >> b[i];

    ll ans = 0;
    sort(edges.begin(), edges.end());
    memset(cnt, 0, sizeof(cnt));
    rep(i,1,n) fa[i] = i;
    rep(i,1,k) {
        cnt[a[i]][0] += 1;
        cnt[b[i]][1] += 1;
    }

    for(const edge &e : edges) {
        ll u = e.from, v = e.to, w = e.dis;
        ll ru = root(u), rv = root(v);
        if(ru == rv) continue;
        fa[ru] = rv;

        cnt[rv][0] = cnt[ru][0] + cnt[rv][0];
        cnt[rv][1] = cnt[ru][1] + cnt[rv][1];
        ll common = min(cnt[rv][0], cnt[rv][1]);
        ans += common * w;
        cnt[rv][0] -= common;
        cnt[rv][1] -= common;
    }

    cout << ans << endl;

    return 0;
}