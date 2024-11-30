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

ll n,m,ans[maxn];
vector< vector<ll> > res;

inline void print()
{
    // rep(i,1,n) cout << ans[i] << " "; cout << endl;

    res.push_back(vector<ll>());
    rep(i,1,n) res.back().push_back(ans[i]);
}

void dfs(ll idx)
{
    if(idx == n + 1) {
        if(ans[n] <= m) print();
        return;
    }

    ll l = ans[idx-1] + 10, r = m - (n - idx) * 10;
    rep(i,l,r) {
        ans[idx] = i;
        dfs(idx + 1);
    }
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;

    ans[0] = 1 - 10;
    dfs(1);

    cout << res.size() << endl;
    for(const vector<ll> &x : res) {
        for(ll y : x) cout << y << " "; cout << endl;
    }

    return 0;
}