// C++ >= 17, all 1-indexed (except atcoder library)

#pragma GCC optimize ("-O3") // use it only when in need

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

const ll maxn = 3e3 + 8;
const ll maxl = 2e5 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e16 + 8;
const f pi = acos(-1.0);
const f eps = 1e-6;

// hash BEGIN

struct hashable_value {
    static const ll maxv = 1e6 + 1;

    ll x,y;

    hashable_value(ll x = 0, ll y = 0) : x(x), y(y) {}

    bool operator==(const hashable_value &r) const {
        return x == r.x && y == r.y;
    }

    struct hash {
        // size_t is 64-bits width on 64-bits system
        size_t operator()(const hashable_value &v) const {
            ll id = v.x * hashable_value::maxv + v.y;
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
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

// graph END

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
    if(!b) { d = a; x = 1; y = 0; }
    else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}

// 扩展欧几里得法，计算a的逆元，p是模数，a和p需要是互质的
// 如果p本身就是质数，那么a就没有限制了，任意非零数a都与素数p互质
ll inverse_element_exgcd(ll a, ll p){
    ll d,x,y;
    exgcd(a,p,d,x,y);
    return d == 1 ? (x+p)%p : -1;
}

struct node {
    ll x,y,id;

    bool operator<(const node &r) const {
        return x <= r.x && y <= r.y;
    }
};

ll h,w,n,memo[maxn],a[maxl];
vector<node> ps;
unordered_map<hashable_value, ll, hashable_value::hash> path_cnt_memo;

inline ll path_cnt(ll dx, ll dy) {
    dx = abs(dx);
    dy = abs(dy);
    static bool is_init = false;
    if(!is_init) {
        is_init = true;
        a[0] = 1;
        rep(i,1,maxl-1) {
            a[i] = a[i-1] * i % mod;
        }
    }

    hashable_value hv(dx, dy);
    if(path_cnt_memo.count(hv)) return path_cnt_memo[hv];

    ll &res = path_cnt_memo[hv];

    res = a[dx + dy] * inverse_element_exgcd(a[dx], mod) % mod * inverse_element_exgcd(a[dy], mod) % mod;
    return res;
}

namespace _main {

ll dp(ll x) {
    if(memo[x] != -1) return memo[x];

    ll &res = memo[x];
    if(x == 0) return res = 1;

    res = 0;
    for(ll son : g[x]) {
        res = (res + path_cnt(ps[x].x - ps[son].x, ps[x].y - ps[son].y) * dp(son) % mod) % mod;
    }

    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> h >> w >> n;
    ps.pb(node{1,1,0});
    rep(i,1,n) {
        static ll x,y;
        cin >> x >> y;
        ps.pb(node{x, y, i});
    }
    ps.pb(node{h,w,n + 1});

    auto _ps(ps);

    sort(_ps.begin(), _ps.end());

    rep(i,0,n+1) {
        rep(j,i+1,n+1) {
            if(_ps[i] < _ps[j]) {
                g[ps[j].id].pb(ps[i].id);
                break;
            }
        }
    }

    memset(memo, -1, sizeof(memo));

    ll total = path_cnt(h - 1, w - 1);
    ll block = dp(n + 1);

    cout << (total - block + mod) % mod << endl;

    return 0;
}

} // namespace _main

// 第一次经过的墙壁的ID是X，从（1，1）到墙壁X的路径数量
// 也就是：从（1，1）到达墙壁X，而不经过其他墙壁的路径数量
ll dp(ll x) {
    if(memo[x] != -1) return memo[x];

    ll &res = memo[x];
    
    res = 0;
    rep(i, 1, n) {
        if(i == x) continue;
        if(ps[i] < ps[x]) {
            res = (res + path_cnt(ps[x].x - ps[i].x, ps[x].y - ps[i].y) * dp(i) % mod) % mod;
        }
    }

    res = (path_cnt(ps[x].x - 1, ps[x].y - 1) - res + mod) % mod;

    return res;
}

int main()
{
    cin >> h >> w >> n;
    ps.pb(node{1,1,0});
    rep(i,1,n) {
        static ll x,y;
        cin >> x >> y;
        ps.pb(node{x, y, i});
    }
    ps.pb(node{h,w,n + 1});

    memset(memo, -1, sizeof(memo));
    cout << dp(n + 1) << endl;

    return 0;
}