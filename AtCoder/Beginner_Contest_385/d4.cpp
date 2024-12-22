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
typedef double f;

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

struct house {
    ll id,x,y;
}houses[maxn];

bool cmp_x_first(const house &a, const house &b) {
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

bool cmp_y_first(const house &a, const house &b) {
    if(a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

struct road {
    ll pin,l,r;

    bool operator<(const road &other) const {
        if(pin == other.pin) return l < other.l;
        return pin < other.pin;
    }
}roads_ud[maxn], roads_lr[maxn];

ll n,m,sx,sy,roads_ud_size = 0, roads_lr_size = 0;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> m >> sx >> sy;
    rep(i,1,n) {
        cin >> houses[i].x >> houses[i].y;
        houses[i].id = i;
    }

    rep(i,1,m) {
        char dir;
        ll len;
        cin >> dir >> len;

        switch(dir) {
            case 'U':
                roads_ud[++roads_ud_size] = (road){sx, sy, sy + len};
                sy += len;
            break;
            case 'D':
                roads_ud[++roads_ud_size] = (road){sx, sy - len, sy};
                sy -= len;
            break;
            case 'L':
                roads_lr[++roads_lr_size] = (road){sy, sx - len, sx};
                sx -= len;
            break;
            case 'R':
                roads_lr[++roads_lr_size] = (road){sy, sx, sx + len};
                sx += len;
            break;
        }

    }

    sort(roads_lr+1, roads_lr+1+roads_lr_size);
    sort(roads_ud+1, roads_ud+1+roads_ud_size);

    unordered_set<ll> cnt;

    ll _idx = 1;
    sort(houses+1, houses+1+n, cmp_x_first); // up & down
    rep(i,1,roads_ud_size) {
        const road &now = roads_ud[i];

        while(_idx <= n && houses[_idx].x < now.pin) _idx += 1;
        while(_idx <= n && houses[_idx].x == now.pin && houses[_idx].y <= now.r) {
            if(houses[_idx].y >= now.l) cnt.insert(houses[_idx].id);
            _idx +=1;
        }
    }

    _idx = 1;
    sort(houses+1, houses+1+n, cmp_y_first);
    rep(i,1,roads_lr_size) {
        const road &now = roads_lr[i];

        while(_idx <= n && houses[_idx].y < now.pin) _idx += 1;
        while(_idx <= n && houses[_idx].y == now.pin && houses[_idx].x <= now.r) {
            if(houses[_idx].x >= now.l) cnt.insert(houses[_idx].id);
            _idx +=1;
        }
    }

    cout << sx << " " << sy << " " << cnt.size() << endl;


    return 0;
}