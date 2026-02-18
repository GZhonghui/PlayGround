// C++ >= 17, all 1-indexed, all intervals are closed intervals (except atcoder library)

// #pragma GCC optimize ("-O3") // use it only when in need

// #define ZH_ACL // use atcoder library, requires C++ >= 17

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
inline void i128_i(i128 &v) {
    string s;
    cin >> s;
    bool neg = (s[0] == '-');
    v = 0;
    for (int i = neg ? 1 : 0; i < (int)s.size(); i++) {
        v = v * 10 + (s[i] - '0');
    }
    if (neg) v = -v;
}
inline void i128_o(i128 v) {
    if (v == 0) {
        cout << 0;
        return;
    }
    bool neg = (v < 0);
    if (neg) v = -v;
    string s;
    while (v > 0) {
        s.push_back(char((v % 10) + '0'));
        v /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end()); 
    cout << s;
}
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

namespace partial_sum {
using namespace std;
using ll = int64_t;

// TODO
class partial_sum {

};

class partial_sum_2d { // all api 1-indexed!
protected:
    ll n, m;
    vector< vector<ll> > data, sum;
    vector< vector<bool> > vis;

    ll dfs(ll x, ll y) {
        if(vis[x][y]) return sum[x][y];

        vis[x][y] = true;
        ll &res = sum[x][y];

        res = 0;
        if(!x && !y) {
            res = data[0][0];
        } else if(!x) {
            res = data[x][y] + dfs(x, y - 1);
        } else if(!y) {
            res = data[x][y] + dfs(x - 1, y);
        } else {
            res = data[x][y] + dfs(x - 1, y) + dfs(x, y - 1) - dfs(x - 1, y - 1);
        }

        return res;
    }

public:
    void init(ll n, ll m) {
        this->n = n, this->m = m;
        data = vector< vector<ll> >(n + 2, vector<ll>(m + 2, 0));
    }

    // 1-indexed
    // [x1, x2] -> [1, n] [y1, y2] -> [1, m]
    void range_add(pair<ll, ll> x, pair<ll, ll> y, ll value) {
        data[x.second + 1][y.second + 1] += value;
        data[x.first][y.second + 1] -= value;
        data[x.second + 1][y.first] -= value;
        data[x.first][y.first] += value;
    }

    void build() {
        sum = vector< vector<ll> >(n + 2, vector<ll>(m + 2, 0));
        vis = vector< vector< bool> >(n + 2, vector<bool>(m + 2, false));
        dfs(n, m);

        data = sum;
        vis = vector< vector< bool> >(n + 2, vector<bool>(m + 2, false));
        dfs(n, m);
    }

    // 1-indexed
    ll range_sum(pair<ll, ll> x, pair<ll, ll> y) {
        return (
            sum[x.second][y.second]
            - sum[x.first - 1][y.second]
            - sum[x.second][y.first - 1]
            + sum[x.first - 1][y.first - 1]
        );
    }
};

// https://atcoder.jp/contests/typical90/tasks/typical90_cc
// 基础二维前缀和
void toolkit1() {
    const ll maxl = 5000;
    partial_sum_2d solver;
    solver.init(maxl, maxl);

    ll n, k, a, b;
    cin >> n >> k;
    for(ll i = 0; i < n; i++) {
        cin >> a >> b;
        solver.range_add({a, a}, {b, b}, 1);
    }
    solver.build();

    k = k + 1;
    ll res = 0;
    for(ll x = k; x <= maxl; x++) for(ll y = k; y <= maxl; y++) {
        res = max(res, solver.range_sum({x - k + 1, x}, {y - k + 1, y}));
    }
    cout << res << endl;
}

// https://atcoder.jp/contests/typical90/tasks/typical90_ab
// 2维前缀和
// 二次元いもす法
// https://x.com/e869120/status/1388262816101007363/photo/1
// 这题挺经典的
// 或许2维线段树也可以
// （之前）卡了挺久的，为什么我的写法不可以？数据范围搞错了
// 下面的代码是可以AC的
void toolkit2() {
    const ll maxl = 1000;
    partial_sum_2d solver;
    solver.init(maxl, maxl);

    ll n, lx, ly, rx, ry;
    cin >> n;
    for(ll i = 0; i < n; i++) {
        cin >> lx >> ly >> rx >> ry;
        solver.range_add({lx + 1, rx}, {ly + 1, ry}, 1);
    }
    solver.build();

    vector<ll> ans(n + 1, 0);
    for(ll i = 1; i <= maxl; i++) for(ll j = 1; j <= maxl; j++) {
        ll area = solver.range_sum({i, i}, {j, j});
        ans[area] += 1;
    }
    for(ll i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
}

} // namespace partial_sum

const ll W = 2000;
partial_sum::partial_sum_2d cnt, ids;

void main_algo() {
    cin >> n;

    cnt.init(W + 1, W + 1);
    ids.init(W + 1, W + 1);
    rep(i, 1, n) {
        ll U, D, L, R;
        cin >> U >> D >> L >> R;
        cnt.range_add({U, D}, {L, R}, 1);
        ids.range_add({U, D}, {L, R}, i);
    }

    cnt.build();
    ids.build();

    ll empty_cnt = 0;
    vector<ll> ans(n + 1, 0);
    rep(i, 1, W) rep(j, 1, W) {
        ll c = cnt.range_sum({i, i}, {j, j});
        if(c == 0) {
            empty_cnt++;
        } else if(c == 1) {
            ans[ids.range_sum({i, i}, {j, j})] += 1;
        }
    }

    rep(i, 1, n) {
        cout << (ans[i] + empty_cnt) << endl;
    }
}