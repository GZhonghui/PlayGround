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

#include <atcoder/dsu>
using namespace atcoder;

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

ll n,a[maxn];
bool is_root[maxn];

dsu u(maxn);
vector< vector<ll> > cs;

ll ans = 0;
ll dfs(ll x) {
    ll cnt = 1;
    for(ll to : g[x]) {
        if(is_root[to]) continue;
        cnt += dfs(to);
    }
    if(!is_root[x]) ans += cnt;
    return cnt;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n) {
        cin >> a[i];
        g[a[i]].pb(i);
    }

    memset(is_root, false, sizeof(is_root));

    rep(i,1,n) {
        if(u.same(i,a[i])) {
            cs.pb(vector<ll>());
            ll _t = i;
            do {
                is_root[_t] = true;
                cs.back().pb(_t);
                _t = a[_t];
            } while(_t != i);
        } else {
            u.merge(i, a[i]);
        }
    }

    for(vector<ll> &c : cs) {
        ll sum = 0;
        for(ll x : c) {
            sum += dfs(x);
        }
        ans += sum * c.size();
    }
    cout << ans << endl;

    return 0;
}