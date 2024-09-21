#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
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
const ll maxn = 50;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

const ll MAXN = 50; // 较小的节点数，例如500
ll dist[MAXN][MAXN];

ll n,p,k;

void floydWarshall() {
    for (ll k = 1; k <= n; ++k) {
        for (ll i = 1; i <= n; ++i) {
            for (ll j = 1; j <= n; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int32_t main() {
    cin >> n >> p >> k;

    for(ll i=1;i<=n;i+=1)
    {
        for(ll j=1;j<=n;j+=1)
        {
            cin >> dist[i][j];
        }
    }

    floydWarshall();

    

    return 0;
}
