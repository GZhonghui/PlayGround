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
#define rep(i, n) for (ll i = 1; i <= (n); i++)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,k,ans = 0,v[maxn];
vector<ll> G[maxn];
unordered_set<ll> vs;

ll dfs(ll x, ll fa)
{
    ll res = 0;
    if(vs.count(x)) res = 1;

    for(ll i=0;i<G[x].size();i+=1)
    {
        ll to = G[x][i];
        if(to == fa) continue;
        res += dfs(to, x);
    }

    if(res == 0) ans += 1;
    return res;
}

int main()
{
    cin >> n >> k;
    rep(i, n-1) {
        static ll u,v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    rep(i, k) {
        cin >> v[i]; vs.insert(v[i]);
    }

    dfs(v[1], -1);

    cout << n - ans << endl;

    return 0;
}