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
const ll maxn = 5e5 + 8;
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

ll n,q,cnt[maxn],fa[maxn][2],color[maxn];

inline void init() {
    rep(i,1,n) {
        cnt[i] = 1;
        fa[i][0] = fa[i][1] = i;
        color[i] = i;
    }
}

ll root(ll x, ll dir) {
    return fa[x][dir] == x ? x : fa[x][dir] = root(fa[x][dir],dir);
}

inline pair<ll,ll> get_block(ll idx, ll &c) {
    ll l = root(idx, 0), r = root(idx, 1);
    c = color[l];
    return mk(l,r);
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> q;
    init();

    while(q--) {
        static ll op, x, c; cin >> op;
        if(op == 1) {
            cin >> x >> c;
            ll _color = 0;
            auto range = get_block(x, _color);
            cnt[_color] -= range.second - range.first + 1;
            cnt[c] += range.second - range.first + 1;
            color[range.first] = c;
            if(range.first > 1) {
                get_block(range.first-1, _color);
                if(_color == c) {
                    fa[range.first][0] = range.first - 1;
                    fa[range.first - 1][1] = range.first;
                }
            }
            if(range.second < n) {
                get_block(range.second+1, _color);
                if(_color == c) {
                    fa[range.second][1] = range.second + 1;
                    fa[range.second + 1][0] = range.second;
                }
            }
        } else if(op == 2) {
            cin >> c; cout << cnt[c] << endl;
        }
    }

    return 0;
}