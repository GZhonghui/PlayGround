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

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll maxm = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge{
    ll to,w;
};

vector<edge> edges;
vector<ll> G[maxn];

ll n,m,ans[maxn];

void dfs(ll node)
{
    if(ans[node] == INT64_MIN) ans[node] = 0;
    for(ll i=0;i<G[node].size();i+=1)
    {
        const edge &e = edges[G[node][i]];
        if(ans[e.to] == INT64_MIN)
        {
            ans[e.to] = ans[node] + e.w;
            dfs(e.to);
        }
    }
}

int main()
{
    cin >> n >> m;
    for(ll i=1;i<=n;i+=1) ans[i] = INT64_MIN;

    for(ll i=1;i<=m;i+=1)
    {
        ll x,y,w;
        cin >> x >> y >> w;
        edges.push_back((edge){y,w});
        G[x].push_back(edges.size()-1);
        edges.push_back((edge){x,-w});
        G[y].push_back(edges.size()-1);
    }

    for(ll i=1;i<=n;i+=1)
    {
        dfs(i);
    }

    for(ll i=1;i<=n;i+=1)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}