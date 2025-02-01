// C++ >= 17

#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <random>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <cmath>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include <atcoder/all>

#define mk make_pair
#define pb push_back
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)

using namespace std; // only in algorithm contests
using namespace atcoder;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double f; // may cause WA...

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 100 + 8;
const ll maxk = 1e5 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 8;
const f pi = acos(-1.0);
const f eps = 1e-6;

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

ll n,k,a[maxn],sum[maxn],memo[maxn][maxk],_ans[2][maxk],_sum_ans[maxk];

ll dp(ll r, ll cnt) {
    if(memo[r][cnt] != -1) return memo[r][cnt];
    ll &res = memo[r][cnt];

    if(r == 1) {
        return res = (cnt <= a[1] ? 1 : 0);
    }

    if(sum[r] < cnt) {
        res = 0;
    } else {
        res = 0;
        rep(i,0,min(cnt, a[r])) {
            res = (res + dp(r-1, cnt - i)) % mod;
        }
    }

    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> k;
    rep(i,1,n) cin >> a[i];

    sum[0] = 0;
    rep(i,1,n) sum[i] = sum[i-1] + a[i];

    ll *ans = (ll*)_ans, *target = (ll*)_ans + maxk;

    rep(i,0,k) ans[i] = (i <= a[1] ? 1 : 0);

    rep(i,2,n) {
        _sum_ans[0] = ans[0];
        rep(j,1,k) _sum_ans[j] = (_sum_ans[j-1] + ans[j]) % mod;

        rep(j,0,k) {
            if(sum[i] < j) {
                target[j] = 0;
            } else {
                // rep(_t, 0, min(j, a[i])) {
                //     target[j] = (target[j] + ans[j-_t]) % mod;
                // }

                ll len = min(j, a[i]);
                target[j] = (
                    _sum_ans[j] - (j-len-1 >= 0 ? _sum_ans[j-len-1] : 0) + mod
                ) % mod;
            }
        }
        swap(ans, target);
    }

    cout << ans[k] << endl;

    // memset(memo,-1,sizeof(memo));

    // cout << dp(n, k) << endl;

    return 0;
}