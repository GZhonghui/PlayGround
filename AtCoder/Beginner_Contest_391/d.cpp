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

const ll maxn = 2e5 + 8;
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

ll n,w,q;

struct query {
    ll t,a;

    bool operator < (const query &r) const {
        return t < r.t;
    }
};

struct block {
    ll x,y,id;

    bool operator < (const block &r) const {
        return y < r.y;
    }
};

vector<query> queries;

vector<block> blocks_at_x[maxn];

ll destroy_times[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> w;
    memset(destroy_times, -1, sizeof(destroy_times));

    rep(i,1,n) {
        static ll x,y;
        cin >> x >> y;
        blocks_at_x[x].pb({x,y,i});
    }

    ll min_cnt_in_axis_y = inf;

    rep(i,1,w) {
        sort(blocks_at_x[i].begin(), blocks_at_x[i].end());
        min_cnt_in_axis_y = min(min_cnt_in_axis_y, (ll)blocks_at_x[i].size());
    }

    ll last_destroy_time = -1;
    rep(i,1,min_cnt_in_axis_y) {
        ll destroy_time = 0;

        if(last_destroy_time != -1) {
            destroy_time = last_destroy_time + 1;
        }
        rep(j,1,w) {
            destroy_time = max(destroy_time, blocks_at_x[j][i - 1].y);
        }
        rep(j,1,w) {
            destroy_times[blocks_at_x[j][i - 1].id] = destroy_time;
        }

        last_destroy_time = destroy_time;
    }

    cin >> q;
    rep(i,1,q) {
        static ll t,a;
        cin >> t >> a;
        queries.pb({t,a});
    }

    // sort(queries.begin(), queries.end());
    for(auto &q : queries) {
        // cout << q.t << " " << q.a << endl;
        if(destroy_times[q.a] == -1) {
            cout << "Yes" << endl;
        } else {
            cout << (q.t >= destroy_times[q.a] ? "No" : "Yes") << endl;
        }
    }

    return 0;
}