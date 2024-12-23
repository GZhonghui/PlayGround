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

const ll maxn = 3e5 + 8;
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

ll n,link[maxn],limit[maxn];
priority_queue< ll, vector<ll>, greater<ll> > qs[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;

    memset(link,0,sizeof(link));
    rep(i,1,n-1) {
        ll x,y; cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
        link[x] += 1;
        link[y] += 1;
    }

    rep(i,1,n) limit[i] = inf;

    rep(i,1,n) {
        for(ll to : g[i]) {
            limit[to] = min(limit[to], link[i] - 1);
            qs[to].push(link[i] - 1);
        }
    }

    ll ans = 0;
    rep(i,1,n) {
        // ans = max(ans, 1 + link[i] * limit[i]);
        while(!qs[i].empty()) {
            ans = max(
                ans, 1 + (ll)qs[i].size() + (ll)qs[i].size() * (ll)qs[i].top()
            );
            qs[i].pop();
        }
    }

    cout << n - ans << endl;

    return 0;
}