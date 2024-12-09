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

ll n,a[maxn],sum[21][maxn],xth[21][maxn];

inline ll next(ll number, ll starts_at) {
    ll left_cnt = sum[number][starts_at - 1];
    ll next_id = xth[number][left_cnt + 2];
    return next_id;
}

unordered_map<ll,ll> mem;
ll dp(ll x)
{
    if(mem.count(x)) return mem[x];
    ll &res = mem[x] = inf;

    if(!x) res = 0;
    else rep(i,1,20) {
        ll _pin_i = (((ll)1) << (i-1));
        if( _pin_i & x ) {
            ll pre_x = x & ~_pin_i;
            ll pre_x_len = dp(pre_x);
            if(pre_x_len < inf) {
                ll next_id = next(i, pre_x_len + 1);
                if(next_id != -1) res = min(res, next_id);
            }
        }
    }

    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n) cin >> a[i];

    memset(sum,0,sizeof(sum));
    memset(xth,-1,sizeof(xth));

    rep(j,1,20) {
        ll cnt = 0;
        rep(i,1,n) {
            sum[j][i] = sum[j][i-1] + ((a[i] == j) ? 1 : 0);
            if(a[i] == j) xth[j][++cnt] = i;
        }
    }

    ll ans = 0;
    ll _end = (((ll)1)<<20)-1;
    rep(i,0,_end) {
        if(dp(i) < inf) {
            ll _ans = 0;
            rep(j,1,20) _ans += ((((ll)1) << (j-1)) & i) ? 1 : 0;
            ans = max(ans, _ans);
        }
    }
    cout << (ans << 1) << endl;

    return 0;
}