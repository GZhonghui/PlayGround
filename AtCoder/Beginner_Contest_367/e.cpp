// 置换 经典习题 值得复习
// 搭配ABC377E一起看

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

ll n,k,x[maxn],a[maxn],ans[maxn];

struct node
{
    ll x[maxn];

    void mul(ll *x)
    {
        rep(i, 1, n)
        {
            this->x[i] = x[this->x[i]];
        }
    }
}xs;

node qpow(node x, ll c)
{
    if(c == 0){
        node res;
        rep(i,1,n) res.x[i] = i;
        return res;
    }
    else if(c == 1) return x;

    ll hc = c >> 1;
    node hx1 = qpow(x, hc);
    node hx2 = hx1;
    hx1.mul(hx2.x);

    if(c & 1) hx1.mul(x.x);

    return hx1;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> k;
    rep(i, 1, n) cin >> x[i];
    rep(i, 1, n) cin >> a[i];

    memcpy(xs.x, x, sizeof(x));
    node xf = qpow(xs, k);
    rep(i, 1, n)
    {
        ans[i] = a[xf.x[i]];
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}