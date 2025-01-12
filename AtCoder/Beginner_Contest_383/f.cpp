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

const ll mod = 1e9+7;
const ll maxn = 500 + 8;
const ll maxx = 50000 +8;
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

struct item {
    ll p,u,c;

    bool operator<(const item &other) const {
        return c < other.c;
    }
};

ll n,x,k,dp[maxx],cache[maxx];
vector<item> items;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> x >> k;
    rep(i,1,n) {
        static ll p,u,c;
        cin >> p >> u >> c;
        items.pb((item){p,u,c});
    }
    sort(items.begin(), items.end());
    
    ll current_color = -1;
    rep(i,1,x) cache[i] = dp[i] = -1; cache[0] = dp[0] = 0;
    for(item &i : items) {
        if(i.c != current_color) {
            rep(j,0,x) {
                cache[j] = dp[j] = max(dp[j], cache[j]);
            }
            current_color = i.c;
        }
        rre(j,0,x){
            if(j >= i.p) {
                if(dp[j - i.p] >= 0) {
                    dp[j] = max(dp[j], dp[j - i.p] + i.u);
                }
                if(cache[j - i.p] >= 0) {
                    dp[j] = max(dp[j], cache[j - i.p] + i.u + k);
                }
            }
        }
    }
    ll ans = 0;
    rep(i,0,x) ans = max(ans, max(dp[i], cache[i]));
    cout << ans << endl;

    return 0;
}