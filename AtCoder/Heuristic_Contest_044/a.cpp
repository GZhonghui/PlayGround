// C++ >= 17, all 1-indexed, all intervals are closed intervals (except atcoder library)

#pragma GCC optimize ("-O3") // use it only when in need

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
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

// graph END

// ========== INSERT CODE BELOW ==========

ll n, l, t[maxn];

class Solution {
protected:
    vector< pair<ll, ll> > ans;
public:
    virtual ll solve() = 0;
    void print() {
        for (auto [x, y] : ans) {
            cout << x << " " << y << endl;
        }
    }
    ll calc_res(vector<ll> *_cnt = nullptr) {
        if((ll)ans.size() != n) return 0;

        ll res = 1e6, cur = 0;
        vector<ll> cnt(n, 0);
        rep(i, 1, l) {
            cnt[cur]++;
            if(cnt[cur] & 1) cur = ans[cur].first;
            else cur = ans[cur].second;
        }
        rep(i, 0, n - 1) {
            res -= abs(t[i] - cnt[i]);
        }
        if(_cnt) {
            _cnt->resize(n);
            rep(i, 0, n - 1) {
                (*_cnt)[i] = cnt[i];
            }
        }
        return max(res, (ll)0);
    }
};

class Solution1 : public Solution {
public:
    ll solve() override {
        rep(i, 0, n - 1) {
            ans.pb(mk(0, 0));
        }
        return calc_res();
    }
};

class Solution2 : public Solution {
public:
    bool shuffle;
    Solution2(bool shuffle = false) : shuffle(shuffle) {}

    struct node {
        ll id, remains;
    };

    vector<node> nodes;
    unordered_set<ll> vis;

    void dfs(ll id) {
        if(vis.count(id)) return;
        vis.insert(id);

        sort(nodes.begin(), nodes.end(), [&](const node &a, const node &b) {
            if(a.id == id) return false;
            if(b.id == id) return true;
            return a.remains > b.remains;
        });

        ans[id].first = nodes[0].id;
        ans[id].second = nodes[1].id;

        ll half = t[id] >> 1;
        nodes[0].remains -= t[id] - half;
        nodes[1].remains -= half;

        dfs(nodes[0].id);
        dfs(nodes[1].id);
    }

    ll solve() override {
        ans = vector< pair<ll, ll> >(n, mk(0, 0));
        rep(i, 0, n - 1) {
            nodes.pb({i, t[i]});
        }

        vector<ll> p(n, 0);
        rep(i, 0, n - 1) {
            p[i] = i;
        }
        if(shuffle) {
            std::shuffle(p.begin(), p.end(), mt19937(random_device()()));
        }

        rep(i, 0, n - 1) {
            dfs(p[i]);
        }

        return calc_res();
    }
};

class Solution3 : public Solution2 {
public:
    Solution3(bool shuffle = false) : Solution2(shuffle) {}

    ll solve() override {
        Solution2::solve();

        vector< pair<ll, ll> > s2_offset(n, mk(0, 0));
        vector<ll> s2_cnt;
        calc_res(&s2_cnt);
        rep(i, 0, n - 1) {
            s2_offset[i] = mk(i, s2_cnt[i] - t[i]);
        }
        sort(s2_offset.begin(), s2_offset.end(), [&](const pair<ll, ll> &a, const pair<ll, ll> &b) {
            return a.second < b.second;
        });

        rep(i, 1, 15) {
            ll l = i - 1, r = n - i;
            ll need = min(-s2_offset[l].second, s2_offset[r].second);
            rep(j, 0, n - 1) {
                ll half = s2_cnt[j] >> 1;
                auto try_move = [&](ll *p) -> bool {
                    if(*p == s2_offset[r].first && half <= need) {
                        need -= half;
                        *p = s2_offset[l].first;
                        return true;
                    }
                    return false;
                };
                if(!try_move(&ans[j].first)) {
                    try_move(&ans[j].second);
                }
            }
        }
        
        return calc_res();
    }
};

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> l;
    rep(i, 0, n - 1) cin >> t[i];

    vector< shared_ptr<Solution> > solutions;
    solutions.pb(make_shared<Solution1>());
    solutions.pb(make_shared<Solution2>());
    rep(i, 1, 300) {
        solutions.pb(make_shared<Solution2>(true));
    }
    solutions.pb(make_shared<Solution3>());
    rep(i, 1, 300) {
        solutions.pb(make_shared<Solution3>(true));
    }

    ll res = 0;
    shared_ptr<Solution> best_solution;
    for (auto s : solutions) {
        ll cur = s->solve();
        if (cur > res) {
            res = cur;
            best_solution = s;
        }
    }
    best_solution->print();

    return 0;
}