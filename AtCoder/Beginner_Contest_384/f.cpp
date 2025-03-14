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

ll n,a[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n) cin >> a[i];

    ll m = 1, d[32];

    rep(k,0,25) {
        d[k] = 0;
        unordered_map<ll,ll> cnt;
        unordered_map<ll,ll> sum;
        rep(i,1,n) {
            ll self = a[i] % m;
            ll target = (m - self) % m;

            if(!cnt.count(self)) cnt[self] = 0;
            if(!sum.count(self)) sum[self] = 0;
            cnt[self] += 1;
            sum[self] += a[i];
            
            d[k] += (
                cnt.count(target) ? cnt[target] : 0
            ) * a[i] + (
                sum.count(target) ? sum[target] : 0
            );

        }

        // cout << k << " " << d[k] << endl;
        
        m <<= 1;
    }

    m = 1;
    ll ans = 0;
    rep(k,0,24) {
        ans += (d[k] - d[k+1]) / m;
        m <<= 1;
    }
    cout << ans << endl;

    return 0;
}