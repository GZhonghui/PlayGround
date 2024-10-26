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

ll n,m,k,l[maxn],r[maxn],min_value[maxn];

struct node {
    ll l,r;

    bool operator<(const node &rhx) const
    {
        return l < rhx.l;
    }
}nodes[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> m;
    rep(i, 1, n) {
        cin >> l[i] >> r[i];
        nodes[i] = (node){l[i],r[i]};
    }

    sort(nodes+1, nodes+1+n);

    min_value[n] = nodes[n].r;
    for(ll i = n-1; i >= 1; i -= 1)
    {
        min_value[i] = min(min_value[i+1], nodes[i].r);
    }

    queue<node> qn;
    rep(i, 1, n)
    {
        qn.push(nodes[i]);
    }

    ll ans = 0;
    rep(i, 1, m)
    {
        while(!qn.empty() && qn.front().l < i) qn.pop();

        ll last = qn.size();
        ll r_limit = (last >= 1 ? min_value[n+1-last] - 1: m);

        ans += r_limit - i + 1;
    }

    cout << ans << endl;

    return 0;
}