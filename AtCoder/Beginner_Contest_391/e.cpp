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

const ll maxn = 13 + 8;
const ll maxlen = 1594323 + 8;
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

ll n;
char s[maxlen];

inline char result(const char *s) {
    string str;
    
    ll len = strlen(s);

    if(len == 1) return s[0];
    for(ll i = 0; i < len; i += 3) {
        ll c0 = 0, c1 = 0;
        for(ll j = 0; j < 3; j++) {
            if(s[i+j] == '0') c0++;
            else c1++;
        }
        str += (c0 > c1 ? '0' : '1');
    }

    return result(str.c_str());
}

vector<ll> children[maxlen * 4];
char result_at_node[maxlen * 4];

ll node_id_idx = 0;
ll build_tree(ll l ,ll r) {
    ll node_id = ++node_id_idx;
    if(l == r) {
        result_at_node[node_id] = s[l];
        return node_id;
    }

    ll len = r - l + 1;
    ll s = len / 3;
    children[node_id].pb(build_tree(l, l + s - 1));
    children[node_id].pb(build_tree(l + s, l + s + s - 1));
    children[node_id].pb(build_tree(l + s + s, r));

    ll c0 = 0, c1 = 0;
    for(auto &child : children[node_id]) {
        if(result_at_node[child] == '0') c0++;
        else c1++;
    }

    result_at_node[node_id] = (c0 > c1 ? '0' : '1');

    return node_id;
}

char target;
ll memo[maxlen * 4];
ll dp(ll node_id) {
    if(memo[node_id] != -1) return memo[node_id];
    ll &res = memo[node_id];

    if(children[node_id].empty()) {
        return res = (result_at_node[node_id] == target) ? 0 : 1;
    }

    res = 0;

    vector<ll> costs;
    
    for(auto &child : children[node_id]) {
        if(result_at_node[child] != target) {
            costs.pb(dp(child));
        } else {
            costs.pb(0);
        }
    }

    sort(costs.begin(), costs.end());

    res = costs[0] + costs[1];

    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    memset(result_at_node, 0, sizeof(result_at_node));

    cin >> n >> (s+1);

    ll len = strlen(s+1);
    char res = result(s+1);

    target = res == '0' ? '1' : '0';

    ll root = build_tree(1, len);

    // TODO

    memset(memo, -1, sizeof(memo));
    ll ans = dp(root);

    cout << ans << endl;

    return 0;
}