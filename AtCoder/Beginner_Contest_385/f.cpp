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
const ll inf = 1e9 + 8;
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

ll n;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    if(
        sizeof(double) == 4 ||
        sizeof(double) == sizeof(long double) ||
        sizeof(long double) == 16
    ) {
        while(true) cout << "ATCODER! what are you doing????" << endl;
    }
    

    f ans = -1e12;

    cin >> n;
    f _x, _h;
    rep(i,1,n) {
        f x,h; cin >> x >> h;
        if(i > 1) {
            f sb = (h - _h) / (x - _x);
            f sb1 = (_h - h) / (_x - x);
            ans = max(ans, 
                // -(_h - h) * _x / (_x - x) + _h
                // (h * _x - _h * x) / (_x - x)
                // _h - (_h - h) / (_x - x) * _x
                // _h - _x * sb
                _h - sb1 * _x
            );
        }
        _x = x, _h = h;
    }

    if(ans < 0) cout << -1 << endl;
    else cout << setprecision(20) << ans << endl;

    return 0;
}