// C++ >= 17

#pragma GCC optimize(2)

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

bool edge_available[maxn];

namespace Dijkstra {

using namespace std;
typedef int64_t ll;

const ll maxn = 310 + 1;
const ll inf = 1e18;

struct Edge{
    ll id,to,dis;
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
        Edge e={id,end,distance};
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
                if(!edge_available[e.id]) continue;
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


ll n,m,q;


int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> m >> q;
    Dijkstra::solver.init(n);
    rep(i,1,m) {
        ll u,v,w;
        cin >> u >> v >> w;
        Dijkstra::solver.add_edge(u,v,w,i);
        Dijkstra::solver.add_edge(v,u,w,i);
        edge_available[i] = true;
    }

    vector< tuple<ll,ll,ll> > queries;
    vector< pair<ll,ll> > ans_in_this_query;

    auto ans_queries = [&]() {
        if (queries.empty()) return;
        
        sort(queries.begin(), queries.end(), [&](tuple<ll,ll,ll> a, tuple<ll,ll,ll> b) {
            return get<0>(a) < get<0>(b);
        });

        ll current_start = -1;

        for (auto &query : queries) {
            ll x = get<0>(query), y = get<1>(query), id = get<2>(query);
            if (current_start != x) {
                Dijkstra::solver.calc(x);
                current_start = x;
            }
            ll ans = Dijkstra::solver.query(y);
            ans_in_this_query.pb(mk(id, ans));
        }

        sort(ans_in_this_query.begin(), ans_in_this_query.end(), [&](pair<ll,ll> a, pair<ll,ll> b) {
            return a.first < b.first;
        });

        for (auto &ans : ans_in_this_query) {
            cout << (ans.second == Dijkstra::inf ? -1 : ans.second) << endl;
        }

        queries.clear();
        ans_in_this_query.clear();
    };

    rep(i,1,q) {
        ll type, x, y;
        cin >> type;
        if (type == 1) {
            ans_queries();
            cin >> x;
            edge_available[x] = false;
        } else if (type == 2) {
            cin >> x >> y;
            queries.pb(make_tuple(min(x,y), max(x,y), i));
        }
    }

    ans_queries();

    return 0;
}