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
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef uint64_t ull;
typedef long double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 2e5 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e18 + 8;
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

struct seg {
    ll l, r;

    void Union(const seg &other) {
        l = max(l, other.l);
        r = min(r, other.r);
        if(r < l) r = l - 1;
    }
}k = (seg){0,inf};

ll n,x,y;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> x >> y;
    rep(i,1,n) {
        ll a,b;
        cin >> a >> b;
        if(x <= a) {
            if(y > b) {
                k.Union((seg){
                    0,
                    floor(1.0 * (a - x) / (y - b))
                });
            }
        } else {
            if (y < b) {
                k.Union((seg){
                    ceil(1.0 * (x - a) / (b - y)),
                    inf
                });
            } else {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << (k.l <= k.r ? "Yes" : "No") << endl;
    return 0;
}