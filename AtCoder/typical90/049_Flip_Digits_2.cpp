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

struct edge {
    ll from,to,dis;

    bool operator<(const edge &r) const {
        return dis < r.dis;
    }
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

namespace disjoint_set {

const int maxn=::maxn;

int fa[maxn];

int root(int x)
{
    //路径压缩
    return fa[x]==x?x:fa[x]=root(fa[x]);
}

inline bool Judge(int x,int y)
{
    //判断两个节点是否已经连接
    return root(x)==root(y);
}

inline void Link(int x,int y)
{
    int rx=root(x),ry=root(y);
    fa[rx]=ry;
}

inline void init()
{
    for(int i=0;i<maxn;i++) fa[i]=i;
}

} // namespace disjoint_set

ll n,m;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    disjoint_set::init();

    cin >> n >> m;
    rep(i,1,m) {
        static ll from,to,dis; cin >> dis >> from >> to;
        edges.pb((edge){from-1,to,dis});
    }
    sort(edges.begin(),edges.end());

    ll ans = 0, c = 0;
    for(const edge &e : edges) {
        if(!disjoint_set::Judge(e.from, e.to)) {
            disjoint_set::Link(e.from, e.to);
            ans += e.dis, c += 1;
        }
    }

    cout << ((c == n) ? ans : -1) << endl;

    return 0;
}