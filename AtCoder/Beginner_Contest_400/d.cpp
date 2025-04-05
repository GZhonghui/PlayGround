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
#endif // TARGET_64

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 1e3 + 8;
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

// ll n, m, k, a[maxn];
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

namespace Dijkstra {

using namespace std;
typedef int64_t ll;

const ll maxn = 100000 + 1;
const ll inf = 1e18;

struct Edge{
    ll to,dis;
};

struct Node{
    ll id,dis;
    bool operator< (const Node& r) const{
        return dis>r.dis;
    }
};

struct Dijkstra
{
public:
    // rebuild graph
    void init(ll n) // nodes range: [1,n]
    {
        this->n = n;
        edges.clear();
        for(ll i=1;i<=n;i++) G[i].clear();
    }

    void add_edge(ll start, ll end, ll distance)
    {
        Edge e={end,distance};
        edges.push_back(e);
        G[start].push_back(edges.size()-1);
    }

    void calc(ll start_id)
    {
        init();

        d[start_id]=0;
        Node start={start_id,0};
        priority_queue<Node> Q;
        Q.push(start);
        while(!Q.empty())
        {
            Node now=Q.top();Q.pop();
            ll x=now.id;
            if(done[x]) continue;
            done[x]=true;
            for(ll i=0;i<G[x].size();i++)
            {
                Edge& e=edges[G[x][i]];
                if(d[e.to]>now.dis+e.dis)
                {
                    d[e.to]=now.dis+e.dis;
                    Node Ins={e.to,d[e.to]};
                    Q.push(Ins);
                }
            }
        }
    }

    ll query(ll target)
    {
        return d[target];
    }

    void copy_result(ll* buffer)
    {
        memcpy(buffer,d,sizeof(ll)*(n+1));
    }

protected:
    // recalc distance
    void init()
    {
        for(ll i=1;i<=n;i++) done[i]=false,d[i]=inf;
    }

protected:
    vector<Edge> edges;
    vector<ll> G[maxn];
    ll n,m,d[maxn];
    bool done[maxn];
}solver;

} // namespace Dijkstra

ll h, w, a, b, c, d, id[maxn][maxn], id_cnt = 0, s_id = -1, t_id = -1;
char s[maxn][maxn];
unordered_map<ll, ll> dist[maxn];

inline void link(ll x, ll y, ll blocks) {
    // cout << x << " -> " << y << " " << blocks << endl;
    if(!dist[x].count(y)) {
        dist[x][y] = inf;
    }
    dist[x][y] = min(dist[x][y], (blocks + 1) >> 1);
}

void dfs(ll x, ll y, ll _id) {
    if(a == x && b == y) {
        s_id = _id;
    }
    if(c == x && d == y) {
        t_id = _id;
    }

    id[x][y] = _id;
    rep(i, 0, 3) {
        ll nx = x + dx[i], ny = y + dy[i];
        if(1 <= nx && nx <= h && 1 <= ny && ny <= w) {
            if(s[nx][ny] == '.' && id[nx][ny] == -1) {
                dfs(nx, ny, _id);
            } else {
                nx -= dx[i];
                ny -= dy[i];
                ll blocks = 0;
                while(true) {
                    nx += dx[i];
                    ny += dy[i];
                    if(nx < 1 || nx > h || ny < 1 || ny > w) {
                        break;
                    }
                    if(s[nx][ny] == '.') {
                        if(id[nx][ny] != -1 && id[nx][ny] != _id) {
                            link(_id, id[nx][ny], blocks);
                        }
                        break;
                    }
                    blocks++;
                    if(dx[i] == 0) {
                        ll _nx1 = nx + 1, _nx2 = nx - 1;
                        if(_nx1 >= 1 && _nx1 <= h && s[_nx1][ny] == '.') {
                            link(_id, id[_nx1][ny], blocks);
                            break;
                        }
                        if(_nx2 >= 1 && _nx2 <= h && s[_nx2][ny] == '.') {
                            link(_id, id[_nx2][ny], blocks);
                            break;
                        }
                    }
                    else if(dy[i] == 0) {
                        ll _ny1 = ny + 1, _ny2 = ny - 1;
                        if(_ny1 >= 1 && _ny1 <= w && s[nx][_ny1] == '.') {
                            link(_id, id[nx][_ny1], blocks);
                            break;
                        }
                        if(_ny2 >= 1 && _ny2 <= w && s[nx][_ny2] == '.') {
                            link(_id, id[nx][_ny2], blocks);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void main_algo_1() {
    cin >> h >> w;
    rep(i, 1, h) {
        cin >> (s[i] + 1);
    }
    cin >> a >> b >> c >> d;

    memset(id, -1, sizeof(id));
    rep(i, 1, h) {
        rep(j, 1, w) {
            if(s[i][j] == '.' && id[i][j] == -1) {
                dfs(i, j, ++id_cnt);
            }
        }
    }

    // cout << id_cnt << endl;
    // cout << s_id << " " << t_id << endl;

    Dijkstra::solver.init(id_cnt);
    rep(i, 1, id_cnt) {
        rep(j, i + 1, id_cnt) {
            ll a = dist[i].count(j) ? dist[i][j] : inf;
            ll b = dist[j].count(i) ? dist[j][i] : inf;
            ll t = min(a, b);
            Dijkstra::solver.add_edge(i, j, t);
            Dijkstra::solver.add_edge(j, i, t);
        }
    }

    Dijkstra::solver.calc(s_id);
    cout << Dijkstra::solver.query(t_id) << endl;
}

struct node {
    ll x, y, dis;
    bool operator< (const node &r) const {
        return dis > r.dis;
    }
};

void main_algo() {
    cin >> h >> w;
    rep(i, 1, h) {
        cin >> (s[i] + 1);
    }
    cin >> a >> b >> c >> d;

    ll dist[maxn][maxn];
    memset(dist, 0x3f, sizeof(dist));
    
    priority_queue<node> Q;
    Q.push({a, b, 0});
    while(!Q.empty()) {
        node now = Q.top(); Q.pop();
        if(now.x == c && now.y == d) {
            cout << now.dis << endl;
            return;
        }

        if(dist[now.x][now.y] <= now.dis) {
            continue;
        }
        dist[now.x][now.y] = now.dis;

        rep(i, 0, 3) {
            ll nx = now.x + dx[i], ny = now.y + dy[i];
            if(1 <= nx && nx <= h && 1 <= ny && ny <= w) {
                if(s[nx][ny] == '.') {
                    Q.push({nx, ny, now.dis});
                } else if(s[nx][ny] == '#') {
                    Q.push({nx, ny, now.dis + 1});

                    nx += dx[i], ny += dy[i];
                    if(1 <= nx && nx <= h && 1 <= ny && ny <= w) {
                        Q.push({nx, ny, now.dis + 1});
                    }
                }
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