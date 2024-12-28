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

ll n,k,a[maxn],ans = 0, sum = 0;

unordered_set<ll> flag;

void dfs(ll start, ll now, ll k, bool def) {
    if(k == 0) {
        if(def) ans = max(ans, now);
        else ans = max(ans, sum);
        return ;
    }

    if(n - start + 1 < k) return;

    rep(i,start,n - k + 1) {
        if(!flag.count(i)) {
            flag.insert(i);

            if(def)
                dfs(i + 1, now ^ a[i], k - 1, def);
            else {
                sum ^= a[i];
                dfs(i + 1, 0, k -1, def);
                sum ^= a[i];
            }

            flag.erase(i);
        }
    }
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> k;
    rep(i,1,n) {
        cin >> a[i];
        sum ^= a[i];
    }

    dfs(1, 0, min(k, n-k), k <= n-k);

    cout << ans << endl;

    return 0;
}