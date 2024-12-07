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
const ll maxn = 16;
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
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

ll h,w,d;
char m[maxn][maxn];

void pos(ll x, ll &_h, ll &_w) {
    _w = x % w; if(_w == 0) _w = w;
    _h = (x - _w) / w + 1;
}

ll dis(ll i, ll j) {
    ll w1,w2,h1,h2; pos(i,h1,w1); pos(j,h2,w2);
    return abs(w1-w2) + abs(h1-h2);
}

ll calc(ll i, ll j) {
    ll w1,w2,h1,h2; pos(i,h1,w1); pos(j,h2,w2);
    if(m[h1][w1] == '#' || m[h2][w2] == '#') return 0;
    ll ans = 0;
    rep(x,1,h*w) {
        ll w3,h3; pos(x,h3,w3);
        if(m[h3][w3] == '.' && min(dis(i,x), dis(j,x)) <= d) {
            ans += 1;
        }
    }
    return ans;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> h >> w >> d;
    rep(i,1,h) cin >> (m[i] + 1);

    ll ans = 0;
    rep(i,1,h*w) rep(j,1,h*w) {
        ans = max(ans, calc(i,j));
    }
    cout << ans << endl;

    return 0;
}