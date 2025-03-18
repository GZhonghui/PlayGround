// C++ >= 17, all 1-indexed, all intervals are closed intervals (except atcoder library)

// #pragma GCC optimize ("-O3") // use it only when in need

// #define ZH_ACL // use atcoder library, requires C++ >= 17

// #define ZH_AHC // Heuristic Contest, otherwise it's a Algorithm contest

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
typedef __int128_t i128;
typedef long double f; // may cause WA on old version compiler...

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

#define HASHABLE_STRING_SEGMENT_TREE
#ifdef HASHABLE_STRING_SEGMENT_TREE
#include <atcoder/segtree>
#include <atcoder/lazysegtree>
#endif // HASHABLE_STRING_SEGMENT_TREE

namespace hashable_string {

using namespace std;
using ull = uint64_t;

const ull suggest_mods_cnt = 5;
const ull sh_base = 26; // only works in [A, Z] for now
const ull sh_mods[6] = {
    static_cast<ull>(1e9 + 7),
    static_cast<ull>(1e9 + 9),
    static_cast<ull>(1e9 + 13),
    static_cast<ull>(1e9 + 17),
    static_cast<ull>(1e9 + 21),
    212370440130137957ULL
};

ull qpow(ull base, ull times, ull mod = UINT64_MAX)
{
    if(times == 0) return 1;
    if(times == 1) return base;

    ull ans = qpow(base, times >> 1, mod) % mod;
    ans = ans * ans % mod;
    if(times & 1) ans = ans * base % mod;

    return ans;
}

// uses 2 mods
class hashable_string {
    string s;
    ull hash0, hash1;
    vector<ull> prefix0, prefix1;

    inline ull convert_char(char c) const { // [0, 26) or [0, sh_base)
        return static_cast<ull>(c - 'A');
    }

    inline void hash_str(const string &s, ull mod, ull &res, vector<ull> &prefix) const {
        int len = s.size();
        prefix.resize(len + 1);
        prefix[0] = 0;

        res = 0;
        for (int i = 1; i <= len; i++) {
            res = (res * sh_base + convert_char(s[i - 1])) % mod;
            prefix[i] = res;
        }
    }

    // sub string: [l, r]
    inline ull hash_substr(int l, int r, ull mod, const vector<ull> &prefix) const {
        ull res = prefix[r];
        ull sub = qpow(sh_base, r - l + 1, mod) * prefix[l - 1] % mod;
        return (res + mod - sub) % mod;
    }

public:
    inline void set(const string &v) {
        s = v;
        hash_str(s, sh_mods[0], hash0, prefix0);
        hash_str(s, sh_mods[1], hash1, prefix1);
    }

    inline int length() const {
        return s.length();
    }

    // O(1)
    inline pair<ull, ull> hash_str() const {
        return make_pair(hash0, hash1);
    }

    // O(log{r-l}) 主要计算量在于pow的计算 可以通过预计算降低到O(1)
    inline pair<ull, ull> hash_substr(int l, int r) const { // 1 <= l <= r <= len
        return make_pair<ull, ull>(
            hash_substr(l, r, sh_mods[0], prefix0),
            hash_substr(l, r, sh_mods[1], prefix1)
        );
    }

    // remember to compare length
    bool operator==(const hashable_string &other) const {
        return length() == other.length() && hash_str() == other.hash_str();
    }

    hashable_string() {
        set("");
    }
};

#ifdef HASHABLE_STRING_SEGMENT_TREE
// uses n mods
class hashable_string_segment_tree {
protected:
    string s;

    static ull char_to_num(char c) {
        return c - 'a';
    }

protected:
    struct S {
        ull h[suggest_mods_cnt], pw[suggest_mods_cnt];

        static S default_value(char c) {
            S res;
            for(int i = 0; i < suggest_mods_cnt; i++) {
                res.h[i] = char_to_num(c);
                res.pw[i] = sh_base;
            }
            return res;
        }

        static S empty_value() {
            S res;
            for(int i = 0; i < suggest_mods_cnt; i++) {
                res.h[i] = 0;
                res.pw[i] = 1;
            }
            return res;
        }
    };

    static S op(S l, S r) {
        S res;
        for(int i = 0; i < suggest_mods_cnt; i++) {
            res.h[i] = (l.h[i] * r.pw[i] % sh_mods[i] + r.h[i]) % sh_mods[i];
            res.pw[i] = l.pw[i] * r.pw[i] % sh_mods[i];
        }
        return res;
    }

    static S e() {
        return S::empty_value();
    }

    std::unique_ptr<atcoder::segtree<S, op, e>> seg;

public:
    void set(const string &s) {
        this->s = s;

        // build segment tree
        vector<S> v(s.length());
        for(int i = 0; i < s.length(); i++) {
            v[i] = S::default_value(s[i]);
        }
        seg = std::make_unique<atcoder::segtree<S, op, e>>(v);
    }

    // pos: [1, length]
    void modify(ull pos, char c) {
        seg->set(pos - 1, S::default_value(c));
    }

    // l, r: [1, length] -> str[l, r]
    vector<ull> hash(ull l, ull r) {
        vector<ull> res(suggest_mods_cnt);
        auto prod = seg->prod(l - 1, r);
        for(int i = 0; i < suggest_mods_cnt; i++) {
            res[i] = prod.h[i];
        }
        return res;
    }
};
#endif // HASHABLE_STRING_SEGMENT_TREE

int hashable_string_toolkit() {
    hashable_string a, b;
    a.set("ABCDABC");
    b.set("AB");

    for(int i = b.length(); i <= a.length(); i++) {
        if(b.hash_str() == a.hash_substr(i - b.length() + 1, i)) {
            cout << i << " ";
        }
    }
    cout << endl;

#ifdef HASHABLE_STRING_SEGMENT_TREE
    hashable_string_segment_tree seg1, seg2;
    seg1.set("ABCABCABCABCABCABCABCABCABCABC");
    seg2.set("ACCABCABCABCABCABCABCABCABCABB");
    seg2.modify(2, 'B');
    auto ha = seg1.hash(1, 30), hb = seg2.hash(1, 30);
    for(int i = 0; i < suggest_mods_cnt; i++) {
        cout << ha[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < suggest_mods_cnt; i++) {
        cout << hb[i] << " ";
    }
    cout << endl;
#endif // HASHABLE_STRING_SEGMENT_TREE

    return 0;
}

} // namespace hashable_string

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

void main_algo() {
    ll n, q;
    string s;
    cin >> n >> q >> s;

    hashable_string::hashable_string_segment_tree s1, s2;
    s1.set(s);
    reverse(s.begin(), s.end());
    s2.set(s);

    rep(i, 1, q) {
        ll t, l, r, x;
        char c;
        cin >> t;
        if(t == 1) {
            cin >> x >> c;
            s1.modify(x, c);
            s2.modify(n - x + 1, c);
        } else if(t == 2) {
            cin >> l >> r;
            auto h1 = s1.hash(l, r);
            auto h2 = s2.hash(n - r + 1, n - l + 1);
            if(h1 == h2) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
}

// ========== INSERT CODE ABOVE ==========

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