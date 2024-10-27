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
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,d,x[maxn],y[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> d;
    rep(i,1,n) cin >> x[i] >> y[i];

    sort(x+1,x+1+n);

    ll h_d = 0,h_idx = -2e6-10;
    rep(i,1,n) h_d += abs(x[i] - h_idx);

    queue<ll> q; rep(i,1,n) q.push(x[i]);
    rep(i,h_idx,-h_idx) {
        // h_d

        ll h_rcount = q.size();
        ll h_lcount = n - h_rcount;
        h_d += h_lcount;
        h_d -= h_rcount;
        while(!q.empty() && q.front() <= i+1) q.pop();
    }


    return 0;
}