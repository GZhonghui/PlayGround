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
typedef long double f;

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

ll n;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ll dig_i, dis;
    cin >> dig_i >> dis;

    f speed = dis / 60.0;
    ll speed_i = speed * 10 + 0.5;

    if(speed_i <= 2) {
        cout << "C 0" << endl;
        return 0;
    }

    ll speed_level = 0;

    if (speed_i <= 15) {
        speed_level = 1;
    } else if (speed_i <= 33) {
        speed_level = 2;
    } else if (speed_i <= 54) {
        speed_level = 3;
    } else if (speed_i <= 79) {
        speed_level = 4;
    } else if (speed_i <= 107) {
        speed_level = 5;
    } else if (speed_i <= 138) {
        speed_level = 6;
    } else if (speed_i <= 171) {
        speed_level = 7;
    } else if (speed_i <= 207) {
        speed_level = 8;
    } else if (speed_i <= 244) {
        speed_level = 9;
    } else if (speed_i <= 284) {
        speed_level = 10;
    } else if (speed_i <= 326) {
        speed_level = 11;
    } else {
        speed_level = 12;
    }

    f dig = dig_i * 0.1;

    if (11.25 < dig && dig < 33.75) {
        cout << "NNE";
    } else if (33.75 < dig && dig < 56.25) {
        cout << "NE";
    } else if (56.25 < dig && dig < 78.75) {
        cout << "ENE";
    } else if (78.75 < dig && dig < 101.25) {
        cout << "E";
    } else if (101.25 < dig && dig < 123.75) {
        cout << "ESE";
    } else if (123.75 < dig && dig < 146.25) {
        cout << "SE";
    } else if (146.25 < dig && dig < 168.75) {
        cout << "SSE";
    } else if (168.75 < dig && dig < 191.25) {
        cout << "S";
    } else if (191.25 < dig && dig < 213.75) {
        cout << "SSW";
    } else if (213.75 < dig && dig < 236.25) {
        cout << "SW";
    } else if (236.25 < dig && dig < 258.75) {
        cout << "WSW";
    } else if (258.75 < dig && dig < 281.25) {
        cout << "W";
    } else if (281.25 < dig && dig < 303.75) {
        cout << "WNW";
    } else if (303.75 < dig && dig < 326.25) {
        cout << "NW";
    } else if (326.25 < dig && dig < 348.75) {
        cout << "NNW";
    } else {
        cout << "N";
    }

    cout << " " << speed_level << endl;

    return 0;
}