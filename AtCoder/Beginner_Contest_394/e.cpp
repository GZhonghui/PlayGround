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

const ll maxn = 100 + 8;
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
    ll to;
    char c;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge
vector<ll> g_rev[maxn];

// graph END

// ========== INSERT CODE BELOW ==========

struct node {
    ll l,r,len;
};

ll n,ans[maxn][maxn];
char m[maxn][maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n) {
        cin >> (m[i] + 1);
    }

    rep(i,1,n) {
        rep(j,1,n) {
            if(m[i][j] != '-') {
                edges.pb({j, m[i][j]});
                g[i].pb(edges.size() - 1); // left

                edges.pb({i, m[i][j]});
                g_rev[j].pb(edges.size() - 1);
            }

            ans[i][j] = inf;
        }
    }

    queue<node> q;
    rep(i,1,n) {
        rep(j,1,n) {
            if(m[i][j] != '-') {
                q.push({i,j,1});
            }
        }
        q.push({i,i,0});
    }

    while(!q.empty()) {
        node cur = q.front();
        q.pop();

        if(cur.len < ans[cur.l][cur.r]) {
            ans[cur.l][cur.r] = cur.len;

            unordered_map<char, vector<ll> > available_c;
            for(ll edge_id : g_rev[cur.l]) {
                const edge &e = edges[edge_id];
                if(!available_c.count(e.c)) {
                    available_c[e.c] = vector<ll>();
                }
                available_c[e.c].pb(e.to);
            }

            for(ll edge_id : g[cur.r]) {
                const edge &e = edges[edge_id];
                if(available_c.count(e.c)) {
                    for(ll to : available_c[e.c]) {
                        q.push({to, e.to, cur.len + 2});
                    }
                }
            }
        }
    }

    rep(i,1,n) {
        rep(j,1,n) {
            cout << (ans[i][j] == inf ? -1 : ans[i][j]) << " ";
        }
        cout << endl;
    }

    return 0;
}