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
typedef long double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 5e5 + 8;
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

ll n,a[maxn],target[maxn],mem[maxn];

ll dp(ll x) {
    if(mem[x] != -1) return mem[x];
    ll &res = mem[x];

    if(x <= 1) return res = 0;
    res = dp(x - 1);
    if(target[x] != -1) res = max(res, dp(target[x] - 1) + 1);

    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i, 1, n) cin >> a[i];

    memset(target, -1, sizeof(target));
    memset(mem, -1, sizeof(mem));

    ll l_idx = n - 1;
    for(ll i = n; i >= 1; i--) {
        ll now = a[i];
        while(l_idx >= 1 && a[l_idx] * 2 > now) l_idx --;
        if(l_idx >= 1) target[i] = l_idx;
        else target[i] = -1;
    }

    rep(i,1,n) cout << target[i] << " "; cout << endl;

    cout << dp(n) << endl;

    return 0;
}