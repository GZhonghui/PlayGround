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

const ll mod = 998244353;
const ll maxn = 300 + 8;
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

ll n,m,s[maxn],_data[maxn][maxn];

inline void swap_line(ll l1, ll l2) {
    rep(i,0,maxn-1) swap(_data[l1][i], _data[l2][i]);
}

inline void add_line_to(ll src_line, ll tgt_line) {
    rep(i,0,maxn-1) _data[tgt_line][i] = (_data[tgt_line][i] + _data[src_line][i]) % 2;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> m;
    rep(i,1,n) {
        static ll t,a; cin >> t;
        rep(j,1,m) _data[i][j] = 0;
        rep(j,1,t) {
            cin >> a;
            _data[i][a] = 1;
        }
    }
    rep(i,1,m) cin >> s[i];

    ll complate_line = 0;
    rep(i,1,m) {
        ll found_line = -1;
        rep(j,complate_line+1,n) {
            if(_data[j][i]) if(found_line == -1) {
                found_line = j;
            } else {
                add_line_to(found_line, j);
            }
        }
        if(found_line != -1) {
            complate_line += 1;
            swap_line(found_line, complate_line);
        }
    }

    ll now[maxn], ans = 1;
    memset(now,0,sizeof(now));
    rep(i,1,n) {
        ll first_one = 0;
        rep(j,1,m) if(_data[i][j]) {
            first_one = j; break;
        }
        if(first_one) {
            if(now[first_one] != s[first_one]) {
                rep(j,1,m) if(_data[i][j]) now[j] = 1 - now[j];
            }
        } else ans = (ans << 1) % mod;
    }

    bool found_error = false;
    rep(i,1,m) found_error |= (s[i] != now[i]);
    cout << (found_error ? (ll)0 : ans) << endl;

    return 0;
}