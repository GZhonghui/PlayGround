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
bool rain[maxn];

ll hm_to_m(ll h, ll m) {
    return h * 60 + m;
}

pair<ll, ll> m_to_hm(ll m) {
    return mk(m / 60, m % 60);
}

void print_m_in_hm(ll m) {
    cout << setw(2) << setfill('0') << m / 60 << setw(2) << setfill('0') << m % 60;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    memset(rain, 0, sizeof(rain));

    cin >> n;
    rep(i, 1, n) {
        char _t;
        ll l, r;

        cin >> l >> _t >> r;
        l = hm_to_m(l / 100, l % 100);
        r = hm_to_m(r / 100, r % 100);
        rep(j, l, r) {
            rain[j] = true;
        }
    }

    vector< pair<ll, ll> > _t;

    ll begin = -1;
    rep(i, 0, 24 * 60 + 1) {
        if(rain[i]) {
            if(begin == -1) {
                begin = i;
            }
        } else {
            if(begin != -1) {
                _t.pb(mk(begin, i - 1));
                begin = -1;
            }
        }
    }

    // ll now = 5;
    // while(now <= 2400) {
    //     ll l = now - 5 + 1;
    //     bool is_rain = false;
    //     rep(j, l, now - 1) {
    //         if (rain[j]) {
    //             is_rain = true;
    //             break;
    //         }
    //     }
    //     if (is_rain) {
    //         _t.pb(mk(l, now));
    //     } else if(rain[now]) {
    //         if(!_t.empty() && _t.back().second == l - 1) {
    //             _t.pb(mk(l, now));
    //         } else if(now < 2400) {
    //             _t.pb(mk(now + 1, now + 5));
    //             now += 5;
    //         }
    //     }

    //     now += 5;
    // }

    auto move = [](ll x, ll s) -> ll {
        while(x % 5) {
            x += s;
        }
        return x;
    };

    auto should_connect = [&](pair<ll, ll> a, pair<ll, ll> b) -> bool {
        return move(a.second, 1) >= move(b.first, -1);
    };

    vector< pair<ll, ll> > ans;
    for(auto &p : _t) {
        if(!ans.empty() && should_connect(ans.back(), p)) {
            ans.back().second = p.second;
        } else {
            ans.pb(p);
        }
    }

    // for(auto &p : _t) {
    //     if(ans.empty()) {
    //         ans.pb(p);
    //     } else {
    //         if (ans.back().second == p.first - 1) {
    //             ans.back().second = p.second;
    //         } else {
    //             ans.pb(p);
    //         }
    //     }
    // }

    for(auto &p : ans) {
        print_m_in_hm(move(p.first, -1));
        cout << "-";
        print_m_in_hm(move(p.second, 1));
        cout << endl;
    }

    return 0;
}