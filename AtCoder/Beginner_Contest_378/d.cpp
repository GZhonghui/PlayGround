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
const ll maxn = 20 + 8;
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

ll h,w,k;
char m[maxn][maxn];
set< pair<ll,ll> > s;

ll dfs(ll x, ll y, ll _k)
{
    if(x < 1 || x > h || y < 1 || y > w || m[x][y] == '#') {
        return 0;
    }

    if(_k == k) return 1;

    ll res = 0;
    rep(i,0,3) {
        ll _x = x + dx[i], _y = y + dy[i];
        if(!s.count(mk(_x,_y)))
        {
            s.insert(mk(_x,_y));
            res += dfs(_x,_y,_k+1);
            s.erase(mk(_x,_y));
        }
        
    }

    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> h >> w >> k;
    rep(i,1,h) cin >> (m[i] + 1);

    ll ans = 0;
    rep(i,1,h) rep(j,1,w) {
        if(m[i][j] == '.') {
            s.clear();
            s.insert(mk(i,j));

            ans += dfs(i,j,0);
        }
    }

    cout << ans << endl;

    return 0;
}