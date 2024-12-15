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
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef uint64_t ull;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 2e5 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 8;
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
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

ll n;

ll dfs(ll node, ll fa) {
    ll res = 1;
    vector<ll> _cache;
    for(ll x : g[node]) {
        if(x == fa) continue;
        _cache.pb(dfs(x,node));
    }

    if(_cache.size() == 0) return 1;
    else if(_cache.size() == 1) return _cache[0];
    
    sort(_cache.begin(), _cache.end());
    ll _size = _cache.size();
    if(_cache[_size-1] == _cache[_size-2]) return _cache[_size-1] + 1;
    else return _cache[_size-1];
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n-1) {
        ll x,y; cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }
    cout << dfs(1,-1) << endl;

    return 0;
}