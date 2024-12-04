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

ll n,a[maxn];

inline ll solve(ll *a, ll n) {
    vector<ll> zip;
    rep(i,1,n>>1) {
        zip.push_back(a[i<<1] == a[(i<<1)-1] ? a[i<<1] : -1);
    }

    ll res = 0, to_del = 0;
    unordered_set<ll> cnt;

    for(ll i=0,_size=zip.size(); i<_size; i++) {
        ll to_add = zip[i];
        while(cnt.count(-1) || cnt.count(to_add)) {
            cnt.erase(zip[to_del++]);
        }
        cnt.insert(to_add);
        if(to_add != -1) res = max(res, i - to_del + 1);
    }

    return res << 1;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n) cin >> a[i];

    ll ans = 0;
    ans = max(ans, solve(a,n));
    ans = max(ans, solve(a+1,n-1));

    cout << ans << endl;
    return 0;
}