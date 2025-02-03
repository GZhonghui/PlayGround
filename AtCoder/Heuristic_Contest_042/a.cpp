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

const ll maxn = 20 + 8;
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
char m[maxn][maxn];
vector<pl> x_pos;

ll move_cnt = 0;
bool global_enable_print = true;
vector<string> *move_log = nullptr;
inline string move(char dir, ll idx, bool is_print = true) {
    string res = "";

    if(++move_cnt <= 4 * n * n) {
        res = dir + string(" ") + to_string(idx - 1);
        if(global_enable_print && is_print) {
            cout << res << endl;
        }
    }

    if(move_log && res != "") {
        move_log->pb(res);
    }
    return res;
}

inline void solve_a() {
    rep(i,1,n) {
        rep(j,1,n) {
            if(m[i][j] == 'x') {
                rep(k,1,i) {
                    move('U', j);
                }
            }
        }
    }
}

// row first
inline void solve_b() {
    char _m[maxn][maxn];
    memcpy(_m, m, sizeof(m));

    rep(i,1,n) {
        ll l = 0, r = n + 1;

        bool found_o = false, found_x = false;
        rep(j,1,n) {
            if(m[i][j] == 'x') {
                found_x = true;
                l = j;
            }
            if(m[i][j] == 'o') {
                found_o = true;
                break;
            }
        }
        rre(j,1,n) {
            if(m[i][j] == 'x') {
                found_x = true;
                r = j;
            }
            if(m[i][j] == 'o') {
                found_o = true;
                break;
            }
        }

        rep(j,1,l) if(m[i][j] == 'x') m[i][j] = '.';
        rep(j,r,n) if(m[i][j] == 'x') m[i][j] = '.';

        if(!found_x) {
            continue;
        }

        // found_x == true
        if(found_o) {
            if(l != 0) {
                rep(_t,1,l) move('L', i);
                rep(_t,1,l) move('R', i);
            }
            if(r != n + 1) {
                rep(_t,1,n-r+1) move('R', i);
                rep(_t,1,n-r+1) move('L', i);
            }
        } else {
            ll move_left = l, move_right = n - r + 1;

            if(move_left < move_right) {
                rep(_t,1,move_left) move('L', i);
            } else {
                rep(_t,1,move_right) move('R', i);
            }
        }
    }

    // copied
    rep(j,1,n) {
        ll l = 0, r = n + 1;

        bool found_o = false, found_x = false;
        rep(i,1,n) {
            if(m[i][j] == 'x') {
                found_x = true;
                l = i;
            }
            if(m[i][j] == 'o') {
                found_o = true;
                break;
            }
        }
        rre(i,1,n) {
            if(m[i][j] == 'x') {
                found_x = true;
                r = i;
            }
            if(m[i][j] == 'o') {
                found_o = true;
                break;
            }
        }

        rep(i,1,l) if(m[i][j] == 'x') m[i][j] = '.';
        rep(i,r,n) if(m[i][j] == 'x') m[i][j] = '.';

        if(!found_x) {
            continue;
        }

        // found_x == true
        if(found_o) {
            ll move_up = l == 0 ? 0 : l, move_down = r == n + 1 ? 0 : n - r + 1;
            if(move_up && move_down) {
                if(move_up < move_down) {
                    rep(_t,1,move_up) move('U', j);
                    rep(_t,1,move_up) move('D', j);
                    rep(_t,1,move_down) move('D', j);
                } else {
                    rep(_t,1,move_down) move('D', j);
                    rep(_t,1,move_down) move('U', j);
                    rep(_t,1,move_up) move('U', j);
                }
            } else if(move_up) {
                rep(_t,1,move_up) move('U', j);
            } else if(move_down) {
                rep(_t,1,move_down) move('D', j);
            }
        } else {
            ll move_up = l, move_down = n - r + 1;

            if(move_up < move_down) {
                rep(_t,1,move_up) move('U', j);
            } else {
                rep(_t,1,move_down) move('D', j);
            }
        }
    }

    memcpy(m, _m, sizeof(m));
}

// copied form solve_b
inline void solve_b_column_first() {
    char _m[maxn][maxn];
    memcpy(_m, m, sizeof(m));

    // copied
    rep(j,1,n) {
        ll l = 0, r = n + 1;

        bool found_o = false, found_x = false;
        rep(i,1,n) {
            if(m[i][j] == 'x') {
                found_x = true;
                l = i;
            }
            if(m[i][j] == 'o') {
                found_o = true;
                break;
            }
        }
        rre(i,1,n) {
            if(m[i][j] == 'x') {
                found_x = true;
                r = i;
            }
            if(m[i][j] == 'o') {
                found_o = true;
                break;
            }
        }

        rep(i,1,l) if(m[i][j] == 'x') m[i][j] = '.';
        rep(i,r,n) if(m[i][j] == 'x') m[i][j] = '.';

        if(!found_x) {
            continue;
        }

        // found_x == true
        if(found_o) {
            ll move_up = l == 0 ? 0 : l, move_down = r == n + 1 ? 0 : n - r + 1;
            if(move_up) {
                rep(_t,1,move_up) move('U', j);
                rep(_t,1,move_up) move('D', j);
            }
            if(move_down) {
                rep(_t,1,move_down) move('D', j);
                rep(_t,1,move_down) move('U', j);
            }
        } else {
            ll move_up = l, move_down = n - r + 1;

            if(move_up < move_down) {
                rep(_t,1,move_up) move('U', j);
            } else {
                rep(_t,1,move_down) move('D', j);
            }
        }
    }

    rep(i,1,n) {
        ll l = 0, r = n + 1;

        bool found_o = false, found_x = false;
        rep(j,1,n) {
            if(m[i][j] == 'x') {
                found_x = true;
                l = j;
            }
            if(m[i][j] == 'o') {
                found_o = true;
                break;
            }
        }
        rre(j,1,n) {
            if(m[i][j] == 'x') {
                found_x = true;
                r = j;
            }
            if(m[i][j] == 'o') {
                found_o = true;
                break;
            }
        }

        rep(j,1,l) if(m[i][j] == 'x') m[i][j] = '.';
        rep(j,r,n) if(m[i][j] == 'x') m[i][j] = '.';

        if(!found_x) {
            continue;
        }

        // found_x == true
        if(found_o) {
            ll move_left = l, move_right = n - r + 1;
            if(move_left && move_right) {
                if(move_left < move_right) {
                    rep(_t,1,move_left) move('L', i);
                    rep(_t,1,move_left) move('R', i);
                    rep(_t,1,move_right) move('R', i);
                } else {
                    rep(_t,1,move_right) move('R', i);
                    rep(_t,1,move_right) move('L', i);
                    rep(_t,1,move_left) move('L', i);
                }
            } else if(move_left) {
                rep(_t,1,move_left) move('L', i);
            } else if(move_right) {
                rep(_t,1,move_right) move('R', i);
            }
        } else {
            ll move_left = l, move_right = n - r + 1;

            if(move_left < move_right) {
                rep(_t,1,move_left) move('L', i);
            } else {
                rep(_t,1,move_right) move('R', i);
            }
        }
    }

    memcpy(m, _m, sizeof(m));
}

// copied form solve_b
inline void solve_c() {
    global_enable_print = false;

    vector<string> move_log_1, move_log_2;
    move_log = &move_log_1;
    solve_b();

    move_log = &move_log_2;
    solve_b_column_first();

    move_log = move_log_1.size() < move_log_2.size() ? &move_log_1 : &move_log_2;
    for(auto &s : *move_log) {
        cout << s << endl;
    }

    move_log = nullptr;

    global_enable_print = true;
}

inline void clear(bool row, ll idx, bool need_restore) {
    

}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i, 1, n) {
        cin >> (m[i] + 1);
    }

    rep(i,1,n) {
        rep(j,1,n) {
            if(m[i][j] == 'x') {
                x_pos.pb(pl{i,j});
            }
        }
    }

    // solve_a();
    // solve_b();
    // solve_b_column_first();
    solve_c();

    return 0;
}