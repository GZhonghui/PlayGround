// C++ >= 17, all 1-indexed (except atcoder library)

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

namespace matrix {
    using namespace std;

    typedef int64_t ll;

    ll mod = -1;

    // 1-indexed
    class matrix {
        int n, m;
        vector< vector<ll> > data;

    public:
        inline void set_zero() {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    data[i][j] = 0;
                }
            }
        }

        inline void set_identity() {
            if (n != m) {
                throw invalid_argument("Matrix is not square");
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    data[i][j] = (i == j);
                }
            }
        }

        matrix(int n, int m) : n(n), m(m), data(n, vector<ll>(m)) {
            if (n == m) {
                set_identity();
            } else {
                set_zero();
            }
        }
        matrix(const matrix& other) : n(other.n), m(other.m), data(other.data) {}

        inline void set(int i, int j, ll val) {
            data[i - 1][j - 1] = val;
        }

        inline ll get(int i, int j) const {
            return data[i - 1][j - 1];
        }

        inline void print() const {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << data[i][j] << " ";
                }
                cout << endl;
            }
        }

        matrix operator*(const matrix& other) const {
            if (m != other.n) {
                throw invalid_argument("Matrix dimensions do not match");
            }

            matrix res(n, other.m);
            res.set_zero();
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < other.m; j++) {
                    for (int k = 0; k < m; k++) { // m == other.n
                        res.data[i][j] += data[i][k] * other.data[k][j];
                        if (mod != -1) {
                            res.data[i][j] %= mod;
                        }
                    }
                }
            }
            return res;
        }

        matrix operator^(ll k) const {
            matrix res(n, n);
            matrix base(*this);
            res.set_identity();

            while (k > 0) {
                if (k & 1) {
                    res = res * base;
                }
                base = base * base;
                k >>= 1;
            }
            return res;
        }
    };
}

ll n,k;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    matrix::mod = ::mod;

    cin >> n >> k;

    matrix::matrix mat(n,n);

    rep(i,1,n) {
        rep(j,1,n) {
            static ll _t;
            cin >> _t;
            mat.set(i,j,_t);
        }
    }

    //mat.print();

    matrix::matrix res = mat^k;
    // res.print();

    ll ans = 0;
    rep(i,1,n) {
        rep(j,1,n) {
            ans += res.get(i,j);
            ans %= mod;
        }
    }
    cout << ans << endl;

    return 0;
}