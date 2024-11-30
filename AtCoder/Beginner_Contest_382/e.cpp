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
const ll maxn = 2e5 + 8;
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

ll n,x,p[maxn];
f p_ins[maxn];

unordered_map<ll,f> mem;
f dp(ll now)
{
    if(now >= x) return 0;
    if(mem.count(now)) return mem[now];

    f res = 1;
    rep(i,1,n) {
        res += dp(now + i) * p_ins[i];
    }

    return mem[now] = res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> x;
    rep(i,1,n) cin >> p[i];

    p_ins[0] = 1;
    rep(i,1,n) p_ins[i] = 0;
    rep(i,1,n) {
        f p_add = (f)p[i] * 1e-2;
        for(ll j=n; j>=1; j--) {
            p_ins[j] = p_ins[j] * (1 - p_add) + p_ins[j - 1] * p_add;
        }
        p_ins[0] *= 1 - p_add;
    }

    cout << dp(0) << endl;

    return 0;
}