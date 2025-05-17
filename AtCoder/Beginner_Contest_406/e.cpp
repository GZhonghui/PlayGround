// C++ >= 17, all 1-indexed, all intervals are closed intervals (except atcoder library)

// #pragma GCC optimize ("-O3") // use it only when in need

// #define ZH_ACL // use atcoder library, requires C++ >= 17

// #define ZH_AHC // Heuristic Contest, otherwise it's a Algorithm contest

#define TARGET_64 // enable 64-bits system features, like __int128

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

typedef __int128_t ll;
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
const ll mod = 998244353;
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

ll t;

namespace combination {
using namespace std;
typedef ll int64_t;

const ll maxn = 1024; // 组合数的参数的范围

struct Quick_C
{
protected:
    ll Jc[maxn],mod; // Jc是阶乘的意思，可以预先计算
    void pre_cal()
    {
        Jc[0]=Jc[1]=1;
        for(ll i=2;i<maxn;i++)
            Jc[i]=Jc[i-1]*i%mod;
    }
    void exgcd(ll a,ll b,ll &x,ll &y)
    {
        if(!b) x=1,y=0;
        else
        {
            exgcd(b,a%b,y,x);
            y-=x*(a/b);
        }
    }
    ll niYuan(ll a,ll b) // 逆元
    {
        ll x,y;
        exgcd(a,b,x,y);
        return (x+b)%b;
    }

public:
    void init(ll mod) // 模数需要是质数
    {
        this->mod=mod;
        pre_cal();
    }
    ll cal_C(ll a,ll b) // a >= b C_{a}^{b} 从a个物品中选择b个的方案数
    {
        return Jc[a]*niYuan(Jc[b],mod)%mod*niYuan(Jc[a-b],mod)%mod;
    }
};

} // namespace combination

combination::Quick_C solver;
vector<ll> bin;
ll memo_cnt[64][64][2], memo_sum[64][64][2];

pair<ll, ll> dp(ll length, ll cnt, bool limit) {
    if(length < cnt) {
        return mk(0, 0);
    }
    if(!cnt) return mk(1, 0);

    if(memo_cnt[length][cnt][limit] != -1) {
        return mk(memo_cnt[length][cnt][limit], memo_sum[length][cnt][limit]);
    }
    ll &res_cnt = memo_cnt[length][cnt][limit] = 0;
    ll &res_sum = memo_sum[length][cnt][limit] = 0;

    if(!limit) {
        res_cnt = solver.cal_C(length, cnt) % mod;

        ll plans = solver.cal_C(length - 1, cnt - 1);
        rep(j, 1, length) {
            res_sum = (res_sum + plans * ((ll)1 << (j - 1) % mod)) % mod;
        }
    } else {
        if(bin[length - 1]) {
            auto t0 = dp(length - 1, cnt, false);
            auto t1 = dp(length - 1, cnt - 1, true);
            res_cnt = (t0.first + t1.first) % mod;
            res_sum = (
                (t0.second + t1.second) % mod + t1.first * ((ll)1 << (length - 1)) % mod
            ) % mod;
        } else {
            auto t = dp(length - 1, cnt, true);
            res_cnt = t.first % mod;
            res_sum = t.second % mod;
        }
    }
    
    return mk(res_cnt, res_sum);
}

ll ac(ll n, ll k) {
    bin.clear();
    memset(memo_cnt, -1, sizeof(memo_cnt));
    memset(memo_sum, -1, sizeof(memo_sum));

    while(n) {
        bin.pb(n & 1);
        n >>= 1;
    }
    return dp(bin.size(), k, true).second;
}

void main_algo() {
    solver.init(mod);
    i128_i(t);
    while(t--) {
        i128_i(n);
        i128_i(k);
        i128_o(ac(n, k));
        cout << endl;
    }
}