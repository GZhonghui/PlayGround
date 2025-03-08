// C++ >= 17, all 1-indexed, all intervals are closed intervals (except atcoder library)

// #pragma GCC optimize ("-O3") // use it only when in need

// #define ZH_ACL // use atcoder library

#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <random>
#include <bitset> // for bitset, bitset<length>(int_number)
#include <cmath>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#ifdef ZH_ACL
#include <atcoder/all>
using namespace atcoder;
#endif

#define mk make_pair
#define pb push_back
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)
#define bit_q1(S, k) (S & (1LL << (k - 1))) // query bit k is 1 or not
#define bit_s0(S, k) (S & (~(1LL << (k - 1)))) // set bit k to 0
#define bit_s1(S, k) (S | (1LL << (k - 1))) // set bit k to 1
#define bit_c1(S) __builtin_popcountll(S) // count number of 1 in S

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef uint64_t ull;
typedef long double f; // may cause WA on old version compiler...

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 5e5 + 8;
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

#ifdef ZH_ACL
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

    cout << res_single.len << " " << res_range.len << endl; // disable warning of unused variable
}
#endif

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

// ========== INSERT CODE BELOW ==========

ll n, m, dis[maxn];
bool vis[maxn];
vector< pair<ll, ll> > res;

void dfs(ll x, ll fa = 0, ll d = 0) {
    dis[x] = d;
    vis[x] = true;
    for(ll eid : g[x]) {
        edge &e = edges[eid];
        if(e.to == fa) continue;
        if(vis[e.to]) {
            if(e.dis < d - dis[e.to]) {
                res.pb({e.to, x});
            }
        } else {
            dfs(e.to, x, d + e.dis);
        }
    }
    vis[x] = false;
}

namespace disjoint_set {
using namespace std;

const int maxn = 5e5 + 8;

class DisjointSet {
protected:
    int fa[maxn];

public:
    // 初始化
    void init()
    {
        for (int i = 0; i < maxn; i++)
            fa[i] = i;
    }

    // 查找根节点
    int root(int x)
    {
        // 路径压缩 默认启用
        // 在少部分的题目中 可能不能使用路径压缩 毕竟路径压缩会破坏树的结构
        return fa[x] == x ? x : fa[x] = root(fa[x]);
    }

    // 判断两个节点是否已经连接
    bool judge(int x, int y)
    {
        return root(x) == root(y);
    }

    // 连接两个节点
    void link(int x, int y)
    {
        int rx = root(x), ry = root(y);
        fa[rx] = ry;
    }
};

// 带权并查集
class DisjointSetWithType {
protected:
    // relation: relation with father
    int fa[maxn], relation[maxn], type_cnt;

public:
    void init(int type_cnt) {
        this->type_cnt = type_cnt;
        for(int i = 0; i < maxn; i++) {
            fa[i] = i;
            relation[i] = 0;
        }
    }

    // root & relation with root
    pair<int, int> root(int x) {
        if(x == fa[x]) {
            return make_pair(x, 0);
        }
        auto res = root(fa[x]);
        // compress path
        fa[x] = res.first;
        relation[x] = (relation[x] + res.second) % type_cnt;
        return make_pair(res.first, relation[x]);
    }

    // x -> y, +delta
    bool link(int x, int y, int delta) {
        auto rx = root(x), ry = root(y);
        if(rx.first == ry.first) {
            // same root, may have conflict
            return delta % type_cnt == (type_cnt - rx.second + ry.second) % type_cnt;
        } else {
            // different root, no conflict
            fa[ry.first] = x;
            relation[ry.first] = (type_cnt + delta - ry.second) % type_cnt;
        }
        return true;
    }
};

// 本函数代码是经典例题「POJ 1182 食物链」（http://poj.org/problem?id=1182）的代码
void toolkit() {
    DisjointSetWithType ds;
    ds.init(3);

    int n, k, t, x, y, res = 0;
    cin >> n >> k;
    while(k--) {
        cin >> t >> x >> y;
        if (x > n || y > n || x < 1 || y < 1) {
            res += 1;
        } else if(t == 1) {
            res += ds.link(x, y, 0) ? 0 : 1;
        } else if(t == 2) {
            res += ds.link(x, y, 1) ? 0 : 1;
        }
    }
    cout << res << endl;
}

} // namespace disjoint_set

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;
    rep(i, 1, m) {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.pb({v, w});
        g[u].pb(edges.size() - 1);
        edges.pb({u, w});
        g[v].pb(edges.size() - 1);
    }

    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    dfs(1);

    disjoint_set::DisjointSet ds;
    ds.init();

    for(auto &p : res) {
        if(ds.judge(p.first, p.second)) {
            cout << "No" << endl;
            return 0;
        }
        ds.link(p.first, p.second);
    }

    cout << (res.size() == n - 1 ? "Yes" : "No") << endl;

    return 0;
}
