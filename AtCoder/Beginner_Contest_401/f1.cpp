// C++ >= 17, all 1-indexed, all intervals are closed intervals (except atcoder library)

// #pragma GCC optimize ("-O3") // use it only when in need

#define ZH_ACL // use atcoder library, requires C++ >= 17

// #define ZH_AHC // Heuristic Contest, otherwise it's a Algorithm contest

// #define TARGET_64 // enable 64-bits system features, like __int128

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
#include <memory>
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
#ifdef TARGET_64
typedef __int128_t i128;
#endif // TARGET_64

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

// graph END

// global variables BEGIN

ll n, m, k, a[maxn];
vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

// global variables END

// AHC BEGIN

#ifdef ZH_AHC

class Solution {
protected:
    vector<ll> ans; // final answer

public:
    virtual ll solve() = 0;
    void print() {
        rep(i, 0, (ll)ans.size() - 1) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    ll score() { // calculate the score of the answer
        // TODO: check if the answer is valid, otherwise return 0
        
        ll sum = 0;
        rep(i, 0, (ll)ans.size() - 1) {
            sum += ans[i];
        }
        return sum;
    }
};

class SolutionDefault : public Solution {
public:
    // 'override' keyword is a C++11 extension
    ll solve() /* override */ { // construct a default solution
        rep(i, 1, 5) {
            ans.pb(i);
        }
        return score();
    }
};

#endif // ZH_AHC

// AHC END

#ifdef ZH_AHC
void main_ahc();
#endif // ZH_AHC

void main_algo();

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

#ifdef ZH_AHC
    main_ahc();
#else
    main_algo();
#endif

    return 0;
}

// ========== INSERT CODE BELOW ==========

#ifdef ZH_AHC
void main_ahc() {
    // TODO: read input

    vector< shared_ptr<Solution> > solutions;
    solutions.pb(make_shared<SolutionDefault>());

    ll best_score = 0;
    shared_ptr<Solution> best_solution;
    rep(i, 0, (ll)solutions.size() - 1) {
        ll score = solutions[i]->solve();
        if (score > best_score) {
            best_score = score;
            best_solution = solutions[i];
        }
    }

    best_solution->print();
}
#endif // ZH_AHC

ll n1, n2, u, v, l1, r1, l2, r2, max_dist = 0, dist1[maxn], dist2[maxn];
vector<ll> g1[maxn], g2[maxn];

void dfs(ll x, ll fa, ll dist, ll &res, vector<ll> (&g)[maxn]) {
    if(dist > max_dist) {
        max_dist = dist;
        res = x;
    }
    for(ll to : g[x]) {
        if(to != fa) {
            dfs(to, x, dist + 1, res, g);
        }
    }
}

void dfs_for_dis(ll x, ll fa, ll dist, ll (&dist_res)[maxn], vector<ll> (&g)[maxn]) {
    dist_res[x] = max(dist_res[x], dist);
    for(ll to : g[x]) {
        if(to != fa) {
            dfs_for_dis(to, x, dist + 1, dist_res, g);
        }
    }
}

void main_algo() {
    cin >> n1;
    rep(i, 1, n1 - 1) {
        cin >> u >> v;
        g1[u].pb(v);
        g1[v].pb(u);
    }

    cin >> n2;
    rep(i, 1, n2 - 1) {
        cin >> u >> v;
        g2[u].pb(v);
        g2[v].pb(u);
    }

    max_dist = 0;
    dfs(1, 0, 0, l1, g1);
    max_dist = 0;
    dfs(l1, 0, 0, r1, g1);

    max_dist = 0;
    dfs(1, 0, 0, l2, g2);
    max_dist = 0;
    dfs(l2, 0, 0, r2, g2);

    memset(dist1, 0, sizeof(dist1));
    memset(dist2, 0, sizeof(dist2));
    dfs_for_dis(l1, 0, 0, dist1, g1);
    dfs_for_dis(r1, 0, 0, dist1, g1);
    dfs_for_dis(l2, 0, 0, dist2, g2);
    dfs_for_dis(r2, 0, 0, dist2, g2);

    ll original_max = max(dist1[l1], dist2[l2]);

    ll ans = 0;

    vector<ll> lens(n2 + 1), lens_sum(n2 + 1, 0);
    rep(i, 1, n2) {
        lens[i] = dist2[i];
    }
    sort(lens.begin() + 1, lens.end());
    rep(i, 1, n2) {
        lens_sum[i] = lens_sum[i - 1] + lens[i];
    }

    rep(i, 1, n1) {
        ll left = dist1[i] + 1;
        ll right = original_max - left;
        auto p = upper_bound(lens.begin() + 1, lens.end(), right);
        ll left_cnt = p - lens.begin() - 1;
        ll right_cnt = n2 - left_cnt;
        ans += original_max * left_cnt;
        ans += right_cnt * left + lens_sum[n2] - lens_sum[left_cnt];
    }

    cout << ans << endl;

}