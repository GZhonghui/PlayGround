#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <cmath>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#define mk make_pair
#define pb push_back
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef uint64_t ull;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

template<class T> struct point {
    T x,y;

    T dis2(const point &r) {
        T dx = x - r.x, dy = y - r.y;
        return dx * dx + dy * dy;
    }
};

typedef point<ll> pl;
typedef point<f> pf;

ll n,m;

namespace Dijkstra {

using namespace std;
typedef int64_t ll;

const ll maxn = ::maxn;
const ll inf = 1e9;

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

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> m;
    Dijkstra::solver.init(n + m + 100); // 这里既然想都没想，随便加了个100，好蠢的错误

    rep(i,1,m) {
        ll k,x,new_node = n + i; cin >> k;
        rep(j,1,k) {
            cin >> x;
            Dijkstra::solver.add_edge(new_node, x, 0);
            Dijkstra::solver.add_edge(x, new_node, 1);
        }
    }

    Dijkstra::solver.calc(1);

    rep(i,1,n) {
        ll dis = Dijkstra::solver.query(i);
        cout << ((dis < Dijkstra::inf) ? dis : -1) << endl;
    }

    return 0;
}