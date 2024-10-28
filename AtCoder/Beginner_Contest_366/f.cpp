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
const ll maxk = 16;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

struct node {
    ll a,b;

    bool operator<(const node &r) const {
        return (a-1)*r.b < (r.a-1)*b;
    }
}nodes[maxn];

ll n,k,a[maxn],b[maxn],mem[maxn][maxk];

ll dp(ll x, ll y)
{
    if(mem[x][y] != -1) return mem[x][y];
    ll &res = mem[x][y] = 1;

    if(y <= 0) return res;
    
    res = nodes[x].a * dp(x-1,y-1) + nodes[x].b;
    if(x <= y) return res;

    return res = max(res, dp(x-1,y));
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> k;
    rep(i,1,n) {
        cin >> a[i] >> b[i];
        nodes[i] = (node){a[i],b[i]};
    }
    // DP的想法没有问题 但是要提前排好序
    // DP是前X当中选择Y个的最优值，但是DP是无法考虑顺序的
    // 本题中的顺序，有一个固定的最优顺序，在DP之前按照规则排好序
    sort(nodes+1,nodes+1+n);

    memset(mem,-1,sizeof(mem));
    cout << dp(n,k) << endl;

    return 0;
}