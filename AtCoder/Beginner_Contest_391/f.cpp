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

const ll maxn = 2e5 + 8;
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

ll n,k,a[maxn],b[maxn],c[maxn];

inline ll calc(ll i, ll j, ll k) {
    return a[i] * b[j] + b[j] * c[k] + c[k] * a[i];
}

struct state {
    ll i,j,k,val;

    state(ll i, ll j, ll k) : i(i), j(j), k(k), val(calc(i,j,k)) {}

    void print() {
        cout << i << " " << j << " " << k << " " << val << endl;
    }

    bool operator < (const state &r) const {
        return val < r.val;
    }

    bool operator > (const state &r) const {
        return val > r.val;
    }
};

priority_queue<state> Q;
priority_queue<state, vector<state>, less<state>> Q_k;

inline void push_state(state s) {
    if(Q_k.size() < k) {
        Q_k.push(s);
    } else if(s.val > Q_k.top().val) {
        Q_k.pop();
        Q_k.push(s);
    }
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> k;
    rep(i,1,n) cin >> a[i];
    rep(i,1,n) cin >> b[i];
    rep(i,1,n) cin >> c[i];

    sort(a+1, a+n+1);
    sort(b+1, b+n+1);
    sort(c+1, c+n+1);

    Q_k.push(state(n,n,n));
    Q.push(state(n,n,n));
    rep(_t,1,k-1) {

        {
            state cur = Q.top();
            Q.pop();
            
            if(cur.i > 1) Q.push(state(cur.i-1, cur.j, cur.k));
            if(cur.j > 1) Q.push(state(cur.i, cur.j-1, cur.k));
            if(cur.k > 1) Q.push(state(cur.i, cur.j, cur.k-1));
        }

        state cur = Q_k.top();
        Q_k.pop();
        // cur.print();

        if(cur.i > 1) {
            push_state(state(cur.i-1, cur.j, cur.k));
        }
        if(cur.j > 1) {
            push_state(state(cur.i, cur.j-1, cur.k));
        }
        if(cur.k > 1) {
            push_state(state(cur.i, cur.j, cur.k-1));
        }
    }

    cout << Q_k.top().val << endl;
    cout << Q.top().val << endl;

    return 0;
}