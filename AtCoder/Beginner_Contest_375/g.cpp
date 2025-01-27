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
    ll id,from,to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

// graph END

namespace Dijkstra {

using namespace std;
typedef int64_t ll;

const ll maxn = ::maxn;
const ll inf = 1e16;

struct Edge{
    ll to,dis,id;
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

    void add_edge(ll start, ll end, ll distance, ll id)
    {
        Edge e={end,distance,id};
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

    void calc_cut_edges(vector<::edge> &shortest_edges) {
        queue<ll> Q;
        unordered_set<ll> S;
        Q.push(n);
        S.insert(n);
        while(!Q.empty()) {
            ll u = Q.front(); Q.pop();
            for(ll i = 0; i < G[u].size(); i++) {
                Edge &e = edges[G[u][i]];
                if(d[e.to] + e.dis == d[u]) {
                    if(!S.count(e.to)) {
                        Q.push(e.to);
                        S.insert(e.to);
                    } 
                    shortest_edges.pb((::edge){e.id, u, e.to, e.dis});
                }
            }
        }
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
}dij_solver;

} // namespace Dijkstra

class Cut {
    struct Edge {
        int u, v, id; // u -> v, id
    };
    
    int n, m;
    vector< vector<int> > g;
    vector<Edge> edges;

    vector<int> dfn, low, father;
    vector<bool> vis, is_cut_point, is_cut_edge;
    int idx, cnt_cut_points, cnt_cut_edges;

public:
    void init(int n, int m) { // [1, n]
        this->n = n;
        this->m = m;
        edges.clear();
        g.resize(n + 1);
        for(int i = 0; i <= n; i++) {
            g[i].clear();
        }
    }

    void add_edge(int u, int v, int id) { // edge id: [1, m]
        edges.push_back((Edge){u, v, id});
        g[u].push_back(edges.size() - 1);
        edges.push_back((Edge){v, u, id});
        g[v].push_back(edges.size() - 1);
    }

protected:
    // from: https://oi-wiki.org/graph/cut/
    void tarjan_p(int u, int fa) {  // u 当前点的编号，fa 自己爸爸的编号
        vis[u] = true;              // 标记
        low[u] = dfn[u] = ++idx;    // 打上时间戳
        int child = 0;              // 每一个点儿子数量
        for (int k : g[u]) {        // 访问这个点的所有邻居 （C++11）
            int v = edges[k].v;
            if (!vis[v]) {
                child++;                       // 多了一个儿子
                tarjan_p(v, u);                // 继续
                low[u] = min(low[u], low[v]);  // 更新能到的最小节点编号
                if (fa != u && low[v] >= dfn[u] && !is_cut_point[u]) {  // 主要代码
                    // 如果不是自己，且不通过父亲返回的最小点符合割点的要求，并且没有被标记过
                    // 要求即为：删了父亲连不上去了，即为最多连到父亲
                    is_cut_point[u] = true;
                    cnt_cut_points++;  // 记录答案
                }
            } else if (v != fa) {
                // 如果这个点不是自己的父亲，更新能到的最小节点编号
                low[u] = min(low[u], dfn[v]);
            }
        }
        // 主要代码，自己的话需要 2 个儿子才可以
        if (fa == u && child >= 2 && !is_cut_point[u]) {
            is_cut_point[u] = true;
            cnt_cut_points++;  // 记录答案
        }
    }

    // from: https://oi-wiki.org/graph/cut/
    void tarjan_e(int u, int fa, vector<int> &shortest_edges) {
        bool flag = false;
        father[u] = fa;
        low[u] = dfn[u] = ++idx;
        for (int k : g[u]) {
            int v = edges[k].v;
            if (!dfn[v]) {
                tarjan_e(v, u, shortest_edges);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    is_cut_edge[v] = true;
                    cnt_cut_edges++;
                    shortest_edges.push_back(edges[k].id);
                }
            } else {
                if (v != fa || flag)
                    low[u] = min(low[u], dfn[v]);
                else
                    flag = true;
            }
        }
    }

public:
    void calc_cut_points(vector<int> &cut_points) {
        dfn = vector<int>(n + 1, 0);
        low = vector<int>(n + 1, 0);
        vis = vector<bool>(n + 1, false);
        is_cut_point = vector<bool>(n + 1, false);
        cnt_cut_points = 0;

        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                idx = 0;
                tarjan_p(i, i);
            }
        }

        cut_points.clear();
        for(int i = 1; i <= n; i++) {
            if(is_cut_point[i]) {
                cut_points.push_back(i);
            }
        }
    }

    void calc_cut_edges(vector<int> &shortest_edges) {
        dfn = vector<int>(n + 1, 0);
        low = vector<int>(n + 1, 0);
        father = vector<int>(n + 1, 0);
        // is_cut_edge[x] == true -> (x, father[x]) is a cut edge
        is_cut_edge = vector<bool>(n + 1, false);
        cnt_cut_edges = 0;

        shortest_edges.clear();
        for(int i = 1; i <= n; i++) {
            if(!dfn[i]) {
                idx = 0;
                tarjan_e(i, i, shortest_edges);
            }
        }
    }
}cut_solver;

ll n,m;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;

    Dijkstra::dij_solver.init(n);
    rep(i,1,m) {
        static ll u,v,w;
        cin >> u >> v >> w;
        Dijkstra::dij_solver.add_edge(u,v,w,i);
        Dijkstra::dij_solver.add_edge(v,u,w,i);

        edges.pb({i,u,v,w});
    }

    Dijkstra::dij_solver.calc(1);

    vector<edge> shortest_edges;
    // for(edge e : edges) {
    //     ll u = e.from, v = e.to, w = e.dis;
    //     ll d1 = Dijkstra::dij_solver.query(u);
    //     ll d2 = Dijkstra::dij_solver.query(v);
    //     if(min(d1,d2) + w == max(d1,d2)) {
    //         shortest_edges.pb(e);
    //     }
    // }
    Dijkstra::dij_solver.calc_cut_edges(shortest_edges);

    cut_solver.init(n, shortest_edges.size());

    ll e_idx = 0;
    for(edge e : shortest_edges) {
        cut_solver.add_edge(e.from, e.to, ++e_idx);
    }

    bool ans[maxn];
    memset(ans, 0, sizeof(ans));

    vector<int> cut_edges_id;
    cut_solver.calc_cut_edges(cut_edges_id);

    for(int id : cut_edges_id) {
        ans[shortest_edges[id - 1].id] = true;
    }

    // test
    // for(edge e : shortest_edges) {
    //     ans[e.id] = true;
    // }

    rep(i,1,m) {
        cout << (ans[i] ? "Yes" : "No") << endl;
    }

    return 0;
}