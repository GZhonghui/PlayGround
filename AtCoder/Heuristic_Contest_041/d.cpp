// C++ >= 17

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
#include <random>

#include <atcoder/all>

#define mk make_pair
#define pb push_back
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)

using namespace std; // only in algorithm contests
using namespace atcoder;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 1e3 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 8;
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
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

// graph END

struct node {
    ll id, a;

    bool operator < (const node &r) const {
        return a < r.a;
    }
};

ll n,m,h,a[maxn],fa[maxn];
pl p[maxn];
vector<ll> sons[maxn],subg[maxn];
bool done[maxn];

vector<node> nodes;

ll dfs(ll x, ll f, ll depth, ll root) {
    if(depth > h) return depth;

    fa[x] = f;
    if(f != -1) sons[f].pb(x);
    subg[x].pb(f);
    subg[f].pb(x);
    done[x] = true;
    ll ans = depth;

    vector<ll> neighbors(g[x].begin(), g[x].end());
    sort(neighbors.begin(), neighbors.end(), [&](ll id_a, ll id_b) {
        return (depth > (h >> 1)) ? a[id_a] > a[id_b] : a[id_a] < a[id_b];
    });
    
    for(ll to : neighbors) {
        if(to == f || done[to]) continue;
        ans = max(ans, dfs(to, x, depth + 1, root));

        // if(ans > h) break;
    }

    return ans;
}

priority_queue<ll> sons_max_depth[maxn];
ll sum_a[maxn],max_ans,max_ans_root;

ll rebuild_dfs(ll x, ll f, ll depth) {

    ll _sum_a = a[x];

    ll max_depth = depth;

    max_ans += (depth + 1) * a[x];

    for(ll son : sons[x]) {
        ll _son_max_depth = rebuild_dfs(son, x, depth + 1);
        max_depth = max(max_depth, _son_max_depth);
        sons_max_depth[x].push(_son_max_depth);

        _sum_a += sum_a[son];
        
    }

    sum_a[x] = _sum_a;

    return max_depth;
}

void try_x_as_root(ll x, ll f, ll max_depth_via_fa, ll sum_a_via_fa, ll fa_as_root_ans) {
    if(f != -1) {
        // calc ans
        bool depth_is_ok = max_depth_via_fa < h;

        if(depth_is_ok) {
            ll _ans = fa_as_root_ans - sum_a[x] + sum_a_via_fa;
            if(_ans > max_ans) {
                max_ans = _ans;
                max_ans_root = x;
            }

            for(ll son : sons[x]) {
                try_x_as_root(son, x, max_depth_via_fa + 1, sum_a_via_fa + sum_a[x], _ans);
            }
        }
    } else {
        for(ll son : sons[x]) {
            try_x_as_root(son, x, sons_max_depth[x].top(), sum_a[x] - sum_a[son], fa_as_root_ans);
        }
    }
    
}

void recalc_fa(ll x, ll f) {
    fa[x] = f;
    for(ll to : subg[x]) {
        if(to == f) continue;
        recalc_fa(to, x);
    }
}

void rebuild_tree(ll root) {
    max_ans = 0;
    max_ans_root = root;

    sum_a[root] = a[root];
    ll max_depth = rebuild_dfs(root, -1, 0);
    
    try_x_as_root(root, -1, -1, -1, max_ans);

    recalc_fa(max_ans_root, -1);
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    memset(done, 0, sizeof(done));

    cin >> n >> m >> h;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, n) fa[i] = -1;

    rep(i, 1, m) {
        ll u,v;
        cin >> u >> v;
        u++, v++;
        g[u].pb(v);
        g[v].pb(u);
    }
    rep(i, 1, n) {
        ll x,y;
        cin >> x >> y;
        p[i] = {x, y};
    }

    rep(i,1,n) {
        nodes.pb({i, a[i]});
    }
    sort(nodes.begin(), nodes.end());
    
    for(auto _n : nodes) {
        ll i = _n.id;
        if (!done[i]) {
            dfs(i, -1, 0, i);
        }
    }

    memset(sum_a, 0, sizeof(sum_a));
    rep(i,1,n) {
        if(fa[i] == -1) {
            rebuild_tree(i);
        }
    }

    rep(i, 1, n) {
        cout << ((fa[i] == -1) ? -1 : fa[i] - 1) << " ";
    }
    cout << endl;
    return 0;
}