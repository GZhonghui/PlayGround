// C++ >= 17, all 1-indexed (except atcoder library)

// #pragma GCC optimize ("-O3") // use it only when in need

#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <random>
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include <atcoder/all>

#define mk make_pair
#define pb push_back
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)
#define bit_q1(S, k) (S & (1LL << (k - 1))) // query bit k is 1 or not
#define bit_s0(S, k) (S & (~(1LL << (k - 1)))) // set bit k to 0
#define bit_s1(S, k) (S | (1LL << (k - 1))) // set bit k to 1
#define bit_c1(S) __builtin_popcountll(S) // count number of 1 in S

using namespace std; // only in algorithm contests
using namespace atcoder;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double f; // may cause WA...

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 2e5 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e16 + 8;
const f pi = acos(-1.0);
const f eps = 1e-6;

// hash BEGIN

struct hashable_value {
    static const ll maxv = 1e6 + 1;

    ll x,y,z;

    hashable_value(ll x = 0, ll y = 0, ll z = 0) : x(x), y(y), z(z) {}

    bool operator==(const hashable_value &r) const {
        return x == r.x && y == r.y && z == r.z;
    }

    struct hash {
        // size_t is 64-bits width on 64-bits system
        size_t operator()(const hashable_value &v) const {
            ll id = (v.x * hashable_value::maxv + v.y) * hashable_value::maxv + v.z;
            return static_cast<size_t>(id);
        }
    };
};

// std::unordered_map uses std::hash on default
unordered_map<hashable_value, string, hashable_value::hash> custom_hash_map;

// hash END

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

    cout << res_single.len << endl; // disable warning of unused variable
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
    ll from,to,id,real_id;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

// graph END

ll n,m,block_head[maxn],block_cnt = 0;
bool v[maxn];
vector<edge> unused_edge_in_blocks[maxn];
unordered_set<ll> added_edge_id;

void dfs(ll x) {
    v[x] = true;

    for(auto eid : g[x]) {
        edge &e = edges[eid];
        if(v[e.to]){
            if(!added_edge_id.count(e.real_id)) {
                added_edge_id.insert(e.real_id);
                unused_edge_in_blocks[block_cnt].pb(e); // retarget <to>
            }
        } else {
            added_edge_id.insert(e.real_id);
            dfs(e.to);
        }
    }
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;

    edges.resize(m * 2 + 10);
    rep(i,1,m) {
        static ll u,v;
        cin >> u >> v;
        edges[i * 2 - 1] = {u,v,i*2-1,i};
        edges[i * 2] = {v,u,i*2,i};
        g[u].pb(i * 2 - 1);
        g[v].pb(i * 2);
    }

    memset(v, false, sizeof(v));

    rep(i,1,n) {
        if(!v[i]) {
            block_head[++block_cnt] = i;
            dfs(i);
        }
    }

    // queue<ll> to_connect_blocks;
    // rep(i,2,block_cnt) {
    //     to_connect_blocks.push(i);
    // }

    // cout << block_cnt << endl;

    vector<tuple<ll,ll,ll>> ans;
    ll k = block_cnt - 1;

    cout << k << endl;

    if(k == 0) {
        return 0;
    }

    queue<ll> need_help_blocks;
    rep(i,2,block_cnt) {
        if(unused_edge_in_blocks[i].empty()) {
            need_help_blocks.push(i);
        } else {
            auto e = unused_edge_in_blocks[i].back();
            ans.pb({e.real_id, e.to, block_head[1]});
            unused_edge_in_blocks[i].pop_back();
        }
    }

    rep(i,1,block_cnt) {
        for(auto e : unused_edge_in_blocks[i]) {
            if(need_help_blocks.empty()) {
                goto print;
            }

            ll connect_block = need_help_blocks.front();
            need_help_blocks.pop();
            ans.pb({e.real_id, e.to, block_head[connect_block]});
        }
    }

    print:;
    for(auto x : ans) {
        cout << get<0>(x) << " " << get<1>(x) << " " << get<2>(x) << endl;
    }

    // rep(i,1,block_cnt) {
    //     for(auto e : unused_edge_in_blocks[i]) {
    //         if(to_connect_blocks.empty()) {
    //             cout << k << endl;
    //             for(auto x : ans) {
    //                 cout << get<0>(x) << " " << get<1>(x) << " " << get<2>(x) << endl;
    //             }
    //             return 0;
    //         }
    //         ll connect_block = to_connect_blocks.front();
    //         to_connect_blocks.pop();
    //         ans.pb({e.id, e.to, block_head[connect_block]});
    //     }
    // }
    
    return 0;
}