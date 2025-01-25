// C++ >= 17

#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <random>
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
typedef long double f; // may cause WA...

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 5e3 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e12 + 8;
const f pi = acos(-1.0);
const f eps = 1e-6;


// geometry BEGIN

template<class T> struct point {
    T x,y;

    T dis2(const point &r) {
        T dx = x - r.x, dy = y - r.y;
        return dx * dx + dy * dy;
    }
};

typedef point<ll> pl;
typedef point<f> pf;

// geometry END

// graph BEGIN

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

// graph END

struct vtam {
    ll dp[maxn];

    inline void init() {
        rep(i, 0, maxn - 1) dp[i] = 0;
    }

    inline void add(ll a, ll c) {
        for(ll i = maxn - 1; i >= 0; i--) {
            if(i >= c) {
                dp[i] = max(dp[i - c] + a, dp[i]);

            } else break;
        }
    }

    inline ll min_c(ll a) {
        rep(i, 0, maxn - 1) {
            if(dp[i] >= a) {
                return i;
            }
        }
        return -1;
    }
};

ll n,x;

vtam v[4];

inline bool check(ll k) {
    ll need = 0;
    rep(i,1,3) {
        ll _t = v[i].min_c(k);
        if(_t == -1) return false;
        need += _t;
    }
    return need <= x;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    rep(i,1,3) v[i].init();

    cin >> n >> x;
    rep(i,1,n) {
        ll _v,a,c;
        cin >> _v >> a >> c;
        v[_v].add(a,c);
    }

    ll l = 0, r = 10e10;
    while(r - l > 3) {
        ll mid = (l + r) >> 1;
        if(check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    for(ll i = r; i >= l; i--) {
        if(check(i)) {
            cout << i << endl;
            break;
        }
    }
    return 0;
}