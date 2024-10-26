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
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 128;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,k;

char m[maxn][maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    rep(i, 1, 8)
    {
        cin >> (m[i] + 1);
    }

    ll ans = 0;
    rep(i, 1, 8)
    {
        rep(j, 1, 8)
        {
            bool found = false;
            rep(x, 1, 8) if(m[i][x] == '#') found = true;
            rep(x, 1, 8) if(m[x][j] == '#') found = true;
            if(!found) ans += 1;
        }
    }
    cout << ans << endl;

    return 0;
}