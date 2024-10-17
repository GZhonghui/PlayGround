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

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,m,a[maxn],ans[maxn];
vector<int> G[maxn];

ll sch(ll x)
{
    if(ans[x] != -1) return ans[x];
    ll &res = ans[x] = 0;

    if(x == n)
    {
        return res = 1;
    }

    for(ll i=0;i<G[x].size();i+=1)
    {
        if(a[G[x][i]] == a[x]) continue;
        ll t = sch(G[x][i]);
        res = max(res, (t + (t && a[x] != a[G[x][i]] ? 1 : 0)));
    }

    for(ll i=0;i<G[x].size();i+=1)
    {
        if(a[G[x][i]] != a[x]) continue;
        ll t = sch(G[x][i]);
        res = max(res, (t + (t && a[x] != a[G[x][i]] ? 1 : 0)));
    }

    return res;
}

int main()
{
    memset(ans,-1,sizeof(ans));

    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,m) {
        static ll u,v;
        cin >> u >> v;
        if(a[u] <= a[v]) G[u].push_back(v);
        if(a[v] <= a[u]) G[v].push_back(u);
    }

    ll res = sch(1);
    cout << res << endl;

    return 0;
}