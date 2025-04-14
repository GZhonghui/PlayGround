// C++ >= 17, all 1-indexed, all intervals are closed intervals (except atcoder library)

// #pragma GCC optimize ("-O3") // use it only when in need

// #define ZH_ACL // use atcoder library, requires C++ >= 17

// #define ZH_AHC // Heuristic Contest, otherwise it's a Algorithm contest

#define TARGET_64 // enable 64-bits system features, like __int128

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

namespace max_flow_dinic {
using namespace std;

const int maxn=1024; // 节点数
const int inf=0xffffff;

struct Edge
{
    int from,to,cap,flow;
    Edge(int from,int to,int cap,int flow):
        from(from),to(to),cap(cap),flow(flow){}
};

class Dinic
{
protected:
    vector<Edge> edges;
    vector<int> G[maxn];
    int s,t,d[maxn],cur[maxn];
    bool vis[maxn];
public:
    //起点、终点和节点数目
    // 节点ID：[1,n]
    void init(int s,int t,int n)
    {
        this->s=s,this->t=t;
        for(int i=1;i<=n;i++) G[i].clear();
        edges.clear();
    }
    // 每条边都有容量
    void AddEdge(int from,int to,int cap)
    {
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));

        G[from].push_back(edges.size()-2);
        G[to].push_back(edges.size()-1);
    }
protected:
    bool bfs()
    {
        memset(vis,0,sizeof(vis));

        queue<int> Q;
        vis[s]=true;
        Q.push(s);
        d[s]=0;

        while(!Q.empty())
        {
            int now=Q.front();
            Q.pop();

            for(int i=0;i<G[now].size();i++)
            {
                Edge& e=edges[G[now][i]];
                if(!vis[e.to]&&e.cap>e.flow)
                {
                    vis[e.to]=true;
                    d[e.to]=d[now]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int dfs(int x,int a)
    {
        if(x==t||a==0) return a;

        int flow=0,f;
        for(int& i=cur[x];i<G[x].size();i++)
        {
            Edge& e=edges[G[x][i]];
            if(d[x]+1==d[e.to]&&(f=dfs(e.to,min(a,e.cap-e.flow)))>0)
            {
                a-=f;
                flow+=f;
                e.flow+=f;
                edges[G[x][i]^1].flow-=f;

                if(!a) break;
            }
        }
        return flow;
    }
public:
    int maxFlow()
    {
        int ans=0;
        while(bfs())
        {
            memset(cur,0,sizeof(cur));
            ans+=dfs(s,inf);
        }
        return ans;
    }
};
int dinic_example()
{
    Dinic *solver=new Dinic;

    // init
    // add_edge
    // calc_max_flow

    delete solver;

    return 0;
}

} // namespace max_flow_dinic

i128 mul = 1e9;
vector< pair<ll, ll> > s, t;

inline bool check(i128 limit) {
    // cout << "enter check with ";
    // i128_o(limit);
    // cout << endl;

    max_flow_dinic::Dinic solver;

    int s = (n << 1) + 1, t = (n << 1) + 2;
    solver.init(s, t, t);
    rep(i, 1, n) {
        solver.AddEdge(s, i, 1);
        solver.AddEdge(n + i, t, 1);
    }
    rep(i, 1, n) {
        rep(j, 1, n) {
            ll dx = ::s[i].first - ::t[j].first, dy = ::s[i].second - ::t[j].second;
            f dis = sqrtl((i128)dx * dx + (i128)dy * dy);
            i128 disi = dis * mul;
            if(disi <= limit) {
                solver.AddEdge(i, n + j, 1);
            }
        }
    }

    // i128_o(limit);
    // cout << "start flow..." << endl;
    int flow = solver.maxFlow();
    // cout << "end flow." << endl;
    return flow >= n;
}

void main_algo() {
    cin >> n;
    s.resize(n + 1), t.resize(n + 1);

    rep(i, 1, n) {
        static ll x, y;
        cin >> x >> y;
        s[i] = mk(x, y);
    }
    rep(i, 1, n) {
        static ll x, y;
        cin >> x >> y;
        t[i] = mk(x, y);
    }

    f max_dis = 0;
    rep(i, 1, n) {
        rep(j, 1, n) {
            ll dx = s[i].first - t[j].first, dy = s[i].second - t[j].second;
            max_dis = max(max_dis, (f)sqrtl((i128)dx * dx + (i128)dy * dy));
        }
    }

    // cout << std::fixed << "max distance = " << max_dis << endl;

    i128 l = 0, r = static_cast<i128>(max_dis * mul) + 16;
    // cout << "search range: ";
    // i128_o(l);
    // cout << ", ";
    // i128_o(r);
    // cout << endl;

    while(r - l > 3) {
        i128 mid = (l + r) >> 1;
        // cout << "length = ";
        // i128_o(r - l);
        // cout << endl;
        if(check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    for(i128 i = l; i <= r; i += 1) {
        if(check(i)) {
            cout << std::fixed << static_cast<f>(i) / mul << endl;
            break;
        }
    }
}

// 教训：绝对误差 和 相对误差
// 另外：相对误差不一定是百分数的形式 普通小数也是一样的