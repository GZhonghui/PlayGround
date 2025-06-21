// C++ >= 17, all 1-indexed, all intervals are closed intervals (except atcoder library)

// #pragma GCC optimize ("-O3") // use it only when in need

// #define ZH_ACL // use atcoder library, requires C++ >= 17

#define ZH_AHC // Heuristic Contest, otherwise it's a Algorithm contest

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

const ll maxn = 2e2 + 8;
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

ll n, m, k, a[maxn][maxn], w[maxn][maxn], d[maxn][maxn];
vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

// global variables END

// AHC BEGIN

#ifdef ZH_AHC

struct Box {
    ll w, d, x, y;
};

class Solution {
protected:
    vector<char> ans; // final answer

public:
    virtual ll solve() = 0;
    void print() {
        rep(i, 0, (ll)ans.size() - 1) {
            cout << ans[i] << endl;
        }
        // cout << endl;
    }
    ll score() { // calculate the score of the answer
        // TODO: check if the answer is valid, otherwise return 0

        if(ans.size() > 2 * n * n * n) {
            return 0;
        }

        ll move_cnt = 0;

        ll x = 1, y = 1, finish = 0;
        stack<Box> holding;
        
        rep(i, 0, (ll)ans.size() - 1) {
            char c = ans[i];
            bool flash = false;

            pair<ll, ll> idx[maxn][maxn];
            rep(i, 1, n) {
                rep(j, 1, n) {
                    idx[i][j] = mk(i, j);
                }
            }
            idx[1][1] = mk(0, 0);

            if(c == 'U' || c == 'D' || c == 'L' || c == 'R') {
                move_cnt++;
            }

            if(c == 'U') {
                flash = true;
                x -= 1;
            } else if(c == 'D') {
                flash = true;
                x += 1;
            } else if(c == 'L') {
                flash = true;
                y -= 1;
            } else if(c == 'R') {
                flash = true;
                y += 1;
            } else if(c == '1') {
                // pick up
                auto p = idx[x][y];
                if(!p.first || !p.second) {
                    return 0;
                }
                holding.push((Box){w[p.first][p.second], d[p.first][p.second], p.first, p.second});
                idx[x][y] = mk(0, 0);
            } else if(c == '2') {
                if(holding.empty()) {
                    return 0;
                }
                auto p = idx[x][y];
                if(p.first || p.second) {
                    return 0;
                }
                auto now = holding.top();
                holding.pop();
                idx[x][y] = mk(now.x, now.y);
            }

            // check
            if(x <= 0 || x > n || y <= 0 || y > n) {
                return 0;
            }

            if(flash) {
                ll up_weight = 0;
                stack<Box> _t;

                while(!holding.empty()) {
                    Box now = holding.top();
                    holding.pop();
                    now.d -= up_weight;
                    up_weight += now.w;
                    _t.push(now);
                }

                while(!_t.empty()) {
                    Box now = _t.top();
                    _t.pop();
                    if(now.d <= 0) {
                        return 0;
                    }
                    holding.push(now);
                }

                if(x == 1 && y == 1) {
                    while(!holding.empty()) {
                        holding.pop();
                        finish += 1;
                    }
                }
            }
        }

        ll r = n * n - 1 - finish;
        return r ? n * n - r : n * n + 2 * n * n * n - move_cnt;
    }
};

class SolutionDefault : public Solution {
public:
    // 'override' keyword is a C++11 extension
    ll solve() /* override */ { // construct a default solution
        return score();
    }
};



class SolutionApple : public Solution {

struct Move {
    ll x, y;
    char op;
};

protected:
    bool h;

public:
    SolutionApple(bool h = true) : h(h) {}
    ll solve() {
        ll x = 1, y = 1;

        queue<Move> target;

        if(h) {
            bool right = true;
            rep(i, 1, n) {
                if(right) {
                    rep(j, 1, n) {
                        target.push((Move){i, j, j == 1 ? 'D' : 'R'});
                    }
                } else {
                    rre(j, 1, n) {
                        target.push((Move){i, j, j == n ? 'D' : 'L'});
                    }
                }
                right = !right;
            }
        } else {
            bool down = true;
            rep(j, 1, n) {
                if(down) {
                    rep(i, 1, n) {
                        target.push((Move){i, j, i == 1 ? 'L' : 'D'});
                    }
                } else {
                    rre(i, 1, n) {
                        target.push((Move){i, j, i == n ? 'L' : 'U'});
                    }
                }
                down = !down;
            }
        }
        
        target.pop();

        stack<Box> holding;
        auto check_task = [&](ll tx, ll ty) -> bool {
            auto _h(holding);
            auto _n = _h.top();
            _h.pop();

            ll dis = tx - 1 + ty - 1, up_weight = 0;
            while(!_h.empty()) {
                ll need = up_weight * (dis + 1) + _n.w * dis;
                if(_h.top().d <= need) {
                    return false;
                }
                up_weight += _h.top().w;
                _h.pop();
            }

            return true;
        };

        while(!target.empty()) {
            auto next = target.front();
            target.pop();
            holding.push((Box){w[next.x][next.y], d[next.x][next.y]});
            while(x < next.x) {
                ans.push_back('D');
                x++;
            }
            while(y < next.y) {
                ans.push_back('R');
                y++;
            }
            ans.push_back('1');

            while(!target.empty()) {
                auto next = target.front();
                holding.push((Box){w[next.x][next.y], d[next.x][next.y]});
                if(check_task(next.x, next.y)) {
                    target.pop();
                    ans.push_back(next.op);
                    ans.push_back('1');
                    x = next.x, y = next.y;
                } else {
                    holding.pop();
                    break;
                }
            }

            while(x > 1) {
                ans.push_back('U');
                x--;
            }
            while(y > 1) {
                ans.push_back('L');
                y--;
            }            
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

    cin >> n;
    rep(i, 1, n) {
        rep(j, 1, n) {
            cin >> w[i][j];
        }
    }
    rep(i, 1, n) {
        rep(j, 1, n) {
            cin >> d[i][j];
        }
    }

    vector< shared_ptr<Solution> > solutions;
    solutions.pb(make_shared<SolutionDefault>());
    solutions.pb(make_shared<SolutionApple>(true));
    solutions.pb(make_shared<SolutionApple>(false));

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

    // debug
    // cout << "score = " << best_score << endl;
}
#endif // ZH_AHC

void main_algo() {

}