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

ll n,m,k;

set< pair<ll,ll> > s;

inline bool in(ll x)
{
    return 1 <= x && x <= n;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;
    rep(ii, 1, m)
    {
        static ll i,j;
        cin >> i >> j;
        s.insert(mk(i,j));

        if(in(i+2) && in(j+1)) s.insert(mk(i+2,j+1));
        if(in(i+1) && in(j+2)) s.insert(mk(i+1,j+2));
        if(in(i-1) && in(j+2)) s.insert(mk(i-1,j+2));
        if(in(i-2) && in(j+1)) s.insert(mk(i-2,j+1));
        if(in(i-2) && in(j-1)) s.insert(mk(i-2,j-1));
        if(in(i-1) && in(j-2)) s.insert(mk(i-1,j-2));
        if(in(i+1) && in(j-2)) s.insert(mk(i+1,j-2));
        if(in(i+2) && in(j-1)) s.insert(mk(i+2,j-1));
    }

    cout << n * n - s.size() << endl ;

    return 0;
}