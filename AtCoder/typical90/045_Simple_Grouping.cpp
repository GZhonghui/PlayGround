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

pl p[maxn];
ll n,k,mem[(ll)1<<maxn][maxn],max_dis[(ll)1<<maxn];

ll dp(ll _p, ll _k)
{
    if(mem[_p][_k] != -1) return mem[_p][_k];
    ll &res = mem[_p][_k] = inf;

    if(_p == 0 && _k == 0) return res = 0;
    if(_p == 0 || _k == 0) return res = inf;

    ll p_count = 0;
    vector<ll> p_pos;

    rep(i,1,n) {
        if(_p & ((ll)1 << (i-1))) {
            p_count += 1;
            p_pos.pb(i);
        }
    }

    if(p_count < _k) return res = inf;

    rep(i,1,((ll)1<<p_count)-1) {
        ll this_p = _p, this_g = 0;
        rep(j,1,p_count) {
            if(i & ((ll)1 << (j-1))) {
                this_p &= ~((ll)1 << (p_pos[j-1]-1));
                this_g |= (ll)1 << (p_pos[j-1]-1);
            }
        }
        res = min(res, max(max_dis[this_g], dp(this_p,_k-1)));
    }

    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    memset(mem,-1,sizeof(mem));

    cin >> n >> k;
    rep(i,1,n) cin >> p[i].x >> p[i].y;

    memset(max_dis,0,sizeof(max_dis));
    rep(i,1,((ll)1<<n)-1) {
        vector<ll> pid;
        rep(j,1,n) {
            if(i & ((ll)1<<(j-1))) {
                pid.pb(j);
            }
        }
        for(ll a : pid) for(ll b : pid) {
            max_dis[i] = max(max_dis[i], p[a].dis2(p[b]));
        }
    }

    cout << dp(((ll)1<<n)-1,k) << endl;

    return 0;
}