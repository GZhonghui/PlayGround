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

ll n,m,p[maxn];

struct node {
    ll id, buy_cnt;

    ll buy_price() const {
        return p[id] * (buy_cnt + 1) * (buy_cnt + 1) - p[id] * buy_cnt * buy_cnt;
    }

    bool operator < (const node &r) const {
        return buy_price() > r.buy_price();
    }
};

bool can_buy(ll cnt) {
    ll last = m;

    priority_queue<node> q;

    rep(i,1,n) {
        q.push((node){i, 0});
    }

    rep(i,1,cnt) {
        node cur = q.top();
        q.pop();

        if(cur.buy_price() > last) return false;

        last -= cur.buy_price();
        q.push((node){cur.id, cur.buy_cnt + 1});
    }

    return true;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;
    rep(i,1,n) cin >> p[i];

    ll l = 0, r = 1e18;

    while(r - l > 3) {
        ll mid = (l + r) >> 1;
        if(can_buy(mid)) l = mid;
        else r = mid - 1;
    }

    while(r >= l) {
        if(can_buy(r)) {
            cout << r << endl;
            return 0;
        }
        r--;
    }

    return 0;
}