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
const ll maxn = 200000 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> g1[maxn],g2[maxn]; // id of target OR id of edge

ll n,m,q,c[maxn],e[maxn],res[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;
    ll sm = (ll)sqrt(m); // 平方分割

    memset(c,0,sizeof(c));
    rep(i,1,m) {
        static ll a,b;
        cin >> a >> b;
        c[a] += 1;
        c[b] += 1;
        g1[a].pb(b);
        g1[b].pb(a);
    }

    rep(i,1,n) {
        for(ll to : g1[i]) {
            if(c[to] > sm) g2[i].pb(to);
        }
    }

    memset(e,0,sizeof(e));
    rep(i,1,n) res[i] = 1;

    cin >> q; vector<ll> ask(q+1); ask[0] = 1;
    rep(i,1,q) {
        static ll x,y;
        cin >> x >> y;
        ask[i] = y;

        if(c[x] > sm) {
            cout << res[x] << endl;
        } else {
            ll last_ask = e[x];
            for(ll to : g1[x]) last_ask = max(last_ask, e[to]);
            cout << ask[last_ask] << endl;
        }
        e[x] = i;
        for(ll to : g2[x]) res[to] = y; res[x] = y;
    }

    return 0;
}