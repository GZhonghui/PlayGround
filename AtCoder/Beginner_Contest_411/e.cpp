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

ll n, m, k, a[maxn][7];
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

namespace inverse_element
{

typedef int64_t ll;

const ll mod = 1009; // 素数

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

// 来源：OI-Wiki，p是模数
ll qpow(ll a, ll b, ll p) {
    ll ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1) {
        if (b & 1) ans = (a * ans) % p;
        a = (a * a) % p;
    }
    return ans;
}

// 快速幂法，p是模数，且p需要是质数
ll inverse_element_qpow(ll a, ll p)
{
    // 【逆元】 = a^{p-2}
    return qpow(a,p-2,p);
}

// 线性求逆元，求[1,n]以内所有数字的逆元（i的逆元是inv[i]，p是模数）
void inverse_element_linear(ll n, ll p, ll* inv)
{
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (ll)(p - p / i) * inv[p % i] % p;
    }
}

// 来源：OI-Wiki
// 计算n个任意数字（不一定要连续）的逆元
// a是输入（需要求逆元的n个数字，下标范围是[1,n]），inv是结果，p是模数
// 速度比上面【单独求逆元】要快
void inverse_elements(ll n, ll* a, ll* inv, ll p)
{
    ll s[n+1],sv[n+1];

    s[0] = 1;
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] * a[i] % p;
    sv[n] = qpow(s[n], p - 2, p);
    // 当然这里也可以用 exgcd 来求逆元,视个人喜好而定.
    for (int i = n; i >= 1; --i) sv[i - 1] = sv[i] * a[i] % p;
    for (int i = 1; i <= n; ++i) inv[i] = sv[i] * s[i - 1] % p;
}

} // namespace inverse_element

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

vector<ll> nums;
unordered_map<ll, vector<ll> > update;

void main_algo() {
    cin >> n;
    rep(i, 1, n) {
        unordered_set<ll> local;
        rep(j, 1, 6) {
            cin >> a[i][j];
            nums.pb(a[i][j]);
            // local.pb(a[i][j]);
            local.insert(a[i][j]);
        }
        // sort(local.begin(), local.end());

        for(ll num : local) {
            if(!update.count(num)) update[num] = vector<ll>();
            update[num].push_back(i);
        }
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    ll n6 = 1, n6rev = 1;
    rep(i, 1, n) {
        n6 = (n6 * 6) % mod;
    }
    n6rev = inverse_element::inverse_element_exgcd(n6, mod);

    ll zeros = n, cnt[maxn], ans = 1, inited = false, prev = 0, E = 0;
    memset(cnt, 0, sizeof(cnt));

    for(ll i : nums) {
        if(!inited) {
            for(ll j : update[i]) {
                ll updated_cnt = 0;
                rep(k, 1, 6) {
                    if(a[j][k] <= i) updated_cnt++;
                }
                if(cnt[j] == 0 && updated_cnt != 0) {
                    zeros--;
                }
                cnt[j] = updated_cnt;
            }

            if(zeros == 0) {
                rep(j, 1, n) {
                    ans = (ans * cnt[j]) % mod;
                }
                ans = (ans * n6rev) % mod;
                inited = true;
            }
        } else {
            for(ll j : update[i]) {
                ll updated_cnt = 0;
                rep(k, 1, 6) {
                    if(a[j][k] <= i) updated_cnt++;
                }
                ans = (ans * updated_cnt) % mod;
                ans = (ans * inverse_element::inverse_element_exgcd(cnt[j], mod)) % mod;
                cnt[j] = updated_cnt;
            }
        }

        if(inited) {
            ll delta = (ans - prev + mod) % mod;
            ll local = (i * delta) % mod;
            E = (E + local) % mod;
            prev = ans;
        }
    }

    cout << E << endl;
}