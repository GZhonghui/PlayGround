// C++ >= 17

#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <random>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <cmath>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include <atcoder/all>

#define mk make_pair
#define pb push_back
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)

using namespace std; // only in algorithm contests
using namespace atcoder;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double f; // may cause WA...

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 300 + 8;
const ll maxq = 2e5 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e12 + 8;
const f pi = acos(-1.0);
const f eps = 1e-6;

// lazysegtree BEGIN

struct S_both {
    ll sum;
    ll max;
    ll len;
};

struct F_both {
    ll add;
    ll set;
    bool is_set;
};

S_both op_both(S_both a, S_both b) {
    return S_both{
        a.sum + b.sum,
        max(a.max, b.max),
        a.len + b.len
    };
}

S_both e_both() {
    return S_both{0, (ll)-1e18, 0};
}

S_both mapping_both(F_both f, S_both s) {
    if (f.is_set) {
        return S_both{
            f.set * s.len,
            f.set,
            s.len
        };
    } else {
        return S_both{
            s.sum + f.add * s.len,
            s.max + f.add,
            s.len
        };
    }
}

F_both composition_both(F_both new_op, F_both old_op) {
    if (new_op.is_set) {
        return new_op;
    } else if (old_op.is_set) {
        return F_both{new_op.add + old_op.add, old_op.set + new_op.add, true};
    } else {
        return F_both{new_op.add + old_op.add, 0, false};
    }
}

F_both id_both() {
    return F_both{0, 0, false};
}

inline void lazy_segtree_toolkit() {
    vector<S_both> initial(8, {0, 0, 1}); // avaliable range: [0, 8)
    lazy_segtree<S_both, op_both, e_both, F_both, mapping_both, composition_both, id_both> seg(initial);

    // set data of pos x
    seg.set(1, {5, 5, 1});
    // get data of pos x
    S_both res_single = seg.get(1);

    // apply operation to range [l, r)
    seg.apply(1, 5, F_both{3, 0, false}); // [1, 5)
    // query data of range [l, r)
    S_both res_range = seg.prod(2, 6); // [2, 6)
}

// lazysegtree END

// geometry BEGIN

template<class T> struct point {
    T x,y;

    T dis2(const point &r) {
        T dx = x - r.x, dy = y - r.y;
        return dx * dx + dy * dy;
    }
};

typedef point<ll> pl;
typedef point<f> pf;

// geometry END

// graph BEGIN

struct edge {
    ll from,to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

// graph END

struct query {
    ll t,x,y;
};

ll n,m,q,enable_edges[maxn * maxn], ans[maxq];
vector<query> qs;

ll dis[maxn][maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m >> q;

    edges.pb({0,0,0});
    rep(i,1,m) {
        ll u,v,w;
        cin >> u >> v >> w;
        edges.pb({u,v,w});
        enable_edges[i] = 1;
    }

    qs.pb({0,0,0});
    rep(i,1,q) {
        ll t,x,y;
        cin >> t;
        if(t == 1) {
            cin >> x;
            enable_edges[x] = 0;
        } else if(t == 2) {
            cin >> x >> y;
        }
        qs.pb({t,x,y});
    }

    rep(i,1,n) {
        rep(j,1,n) {
            dis[i][j] = i == j ? 0 : inf;
        }
    }

    rep(i,1,m) {
        if(enable_edges[i]) {
            ll u = edges[i].from, v = edges[i].to, w = edges[i].dis;
            dis[u][v] = dis[v][u] = min(dis[u][v], w);
        }
    }

    // floyd
    rep(k,1,n) {
        rep(i,1,n) {
            rep(j,1,n) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    rre(i,1,q) {
        query q = qs[i];
        // add edge
        if(q.t == 1) {
            enable_edges[q.x] = 1;
            ll u = edges[q.x].from, v = edges[q.x].to, w = edges[q.x].dis;
            // update shortest distance dynamically
            rep(a,1,n) {
                rep(b,a+1,n) {
                    dis[a][b] = dis[b][a] = min(dis[a][b], min(dis[a][u] + w + dis[v][b], dis[a][v] + w + dis[u][b]));
                }
            }
        } else if(q.t == 2) {
            ll x = q.x, y = q.y;
            ans[i] = dis[x][y];
        }
    }

    rep(i,1,q) {
        if(qs[i].t == 2) {
            if(ans[i] == inf) cout << -1 << endl;
            else cout << ans[i] << endl;
        }
    }

    return 0;
}