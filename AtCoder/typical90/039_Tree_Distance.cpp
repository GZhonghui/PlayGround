#include <algorithm>
#include <iostream>
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const ll dx[4] = {0,0,1,-1};
const ll dy[4] = {1,-1,0,0};

const ll mod = 1e9+7;
const ll maxn = 100000 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,ans = 0,tree_size[maxn];
vector<ll> G[maxn];

ll dfs(ll node, ll fa)
{
    tree_size[node] = 1;
    for(ll i=0;i<G[node].size();i+=1)
    {
        ll target = G[node][i];
        if(target == fa) continue;

        tree_size[node] += dfs(target, node);
    }

    return tree_size[node];
}

void dfs2(ll node, ll fa)
{
    for(ll i=0;i<G[node].size();i+=1)
    {
        ll target = G[node][i];
        if(target == fa) continue;

        // target & node
        ans += tree_size[target] * (n - tree_size[target]);
        dfs2(target, node);
    }
}

int main()
{
    cin >> n;

    ll x,y;
    for(ll i=1;i<n;i+=1)
    {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    dfs(1,-1); dfs2(1,-1);

    cout << ans << endl;

    return 0;
}