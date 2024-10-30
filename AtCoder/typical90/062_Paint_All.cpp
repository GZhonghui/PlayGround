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

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,a[maxn],b[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n) cin >> a[i] >> b[i];

    queue<ll> q;
    rep(i,1,n) if(i == a[i] || i == b[i]) q.push(i);
    rep(i,1,n) {
        G[a[i]].pb(i); G[b[i]].pb(i);
    }

    vector<ll> ans;
    unordered_set<ll> c;
    while(!q.empty()) {
        ll t = q.front(); q.pop();
        if(c.count(t)) continue;
        c.insert(t);
        ans.pb(t);
        for(ll next : G[t]) q.push(next);
    }

    if(ans.size() == n) for(ll i = ans.size() - 1; i >= 0; i -= 1) {
        cout << ans[i] << endl;
    } else cout << "-1" << endl;

    return 0;
}