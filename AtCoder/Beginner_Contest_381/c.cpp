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

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

template<class T> struct point {
    T x,y;

    T dis2(const point &r) {
        T dx = x - r.x, dy = y - r.y;
        return dx * dx + dy * dy;
    }
};

typedef point<ll> pl;
typedef point<f> pf;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

ll n,a[maxn],b[maxn];
char s[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> (s+1);

    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));

    rep(i,1,n) {
        if(s[i] == '1') {
            a[i] = a[i-1] + 1;
        } else a[i] = 0;
    }
    for(ll i=n; i>=1; i--) {
        if(s[i] == '2') {
            b[i] = b[i+1] + 1;
        } else b[i] = 0;
    }

    ll ans = 0;
    rep(i,1,n) {
        if(s[i] == '/') {
            ans = max(ans, min(a[i-1],b[i+1]));
        }
    }

    cout << (1 + (ans << 1)) << endl;

    return 0;
}