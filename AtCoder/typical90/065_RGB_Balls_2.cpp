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

const ll mod = 998244353;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
// vector<ll> G[maxn]; // id of target OR id of edge

ll R,G,B,K,X,Y,Z;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> R >> G >> B >> X >> Y >> Z;
    ll rr = min(R, min(K, min(X, Z)));

    ll ans = 0;
    rep(r, 0, rr) {
        ll gb = K - r;
        if(gb > Y) continue;
        ll gr = min(G, X - r);
        ll br = min(B, Z - r);
        ll br2_l = gb - gr;
        ll br2_r = gb;
        ll A = max((ll)0,br2_l), B = min(br,br2_r);
        ans = (ans + max((ll)0, B-A+1)) % mod;
    }
    cout << ans << endl;

    return 0;
}