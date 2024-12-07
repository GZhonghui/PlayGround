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
const ll maxn = 1e3 + 8;
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
bool v[maxn][maxn];

void pos(ll x, ll &_h, ll &_w) {
    _w = x % w; if(_w == 0) _w = w;
    _h = (x - _w) / w + 1;
}

ll dfs(ll i, ll j, ll last_step)
{
    ll res = 0;
    if(!v[i][j]) {
        v[i][j] = true; res += 1;
    }

    if(last_step == 0) return res;

    rep(_t,0,3) {
        ll ii = i + dx[_t], jj = j + dy[_t];
        if(1 <= ii && ii <= h && 1 <= jj && jj <= w)
        if(m[ii][jj] == '.') {
            res += dfs(ii,jj,last_step-1);
        }
    }
    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> h >> w >> d;
    rep(i,1,h) cin >> (m[i] + 1);

    memset(v,0,sizeof(v));

    ll ans = 0;
    rep(i,1,h) rep(j,1,w) {
        if(m[i][j] == 'H') {
            ans += dfs(i,j,d);
        }
    }
    cout << ans << endl;

    /*
    rep(i,1,h) { 
        rep(j,1,w) {
            if(v[i][j]) cout << '1';
            else cout << '0';
        }
        cout << endl;
    }
    */

    return 0;
}