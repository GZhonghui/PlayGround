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

ll n,m,k,x[maxn],st[maxn];

struct node
{
    ll id,ti,st,sp;

    bool operator<(const node &r) const
    {
        if(ti == r.ti) return sp < r.sp;
        return ti < r.ti;
    }
}nodes[maxn << 1];

int main()
{
    memset(st,0,sizeof(st));
    memset(x,0,sizeof(x));
    cin >> n >> m >> x[1];
    rep(i, 1, m)
    {
        static ll a,b,s,t;
        cin >> a >> b >> s >> t;
        nodes[(i << 1) - 1] = (node){i,s,a,1};
        nodes[(i << 1) - 0] = (node){i,t,b,0};
    }

    sort(nodes + 1, nodes + 1 + (m << 1));

    rep(i, 1, m << 1)
    {
        const node &t = nodes[i];

        if(t.sp == 1)
        {
            if(!x[t.id])
                x[t.id] = max((ll)0, st[t.st] - t.ti);
        }
        else if(t.sp == 0)
        {
            st[t.st] = max(st[t.st], t.ti + x[t.id]);
        }
    }

    rep(i, 2, m)
    {
        cout << x[i] << " ";
    }
    cout << endl;

    return 0;
}