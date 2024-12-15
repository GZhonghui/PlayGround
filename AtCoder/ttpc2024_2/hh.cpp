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

ll n,a[maxn],x[16],loop_len[16];
char s[maxn];

inline bool in_loop(ll idx, char target, vector<ll> &times)
{
    ll now_year = 0, now_pos = x[idx];
    unordered_set<ll> vis;
    while(!vis.count(now_pos)) {
        vis.insert(now_pos);
        if(target == s[now_pos]) {
            times.pb(now_year);
        }

        now_year += 1;
        now_pos = a[now_pos];
    }

    // cout << "times: ";
    // for(ll x : times) cout << x << ","; cout << endl;

    // cout << "looping-" << idx << ": ";
    bool found = false;
    ll _loop_start = now_pos;
    loop_len[idx] = 0;
    do {
        loop_len[idx] += 1;
        // cout << now_pos << ",";
        found |= s[now_pos] == target;
        now_pos = a[now_pos];
    } while(now_pos != _loop_start);
    //cout << "loop_len = " << loop_len[idx] << endl;

    return found;
}

inline void get_full_times(ll idx, char target, unordered_set<ll> &times)
{
    ll now_year = 0, now_pos = x[idx];
    ll _stop = min(n * n * n * n, (ll)2e6);
    while(now_year <= _stop) {
        if(s[now_pos] == target) times.insert(now_year);
        now_pos = a[now_pos];
        now_year += 1;
    }
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> (s+1);
    rep(i,1,n) cin >> a[i];
    rep(i,1,4) cin >> x[i];

    bool res[5];
    vector<ll> times[5];
    res[1] = in_loop(1,'T', times[1]);
    res[2] = in_loop(2,'T', times[2]);
    res[3] = in_loop(3,'P', times[3]);
    res[4] = in_loop(4,'C', times[4]);

    if(res[1] && res[2] && res[3] && res[4]) {
        unordered_set<ll> lens;
        rep(i,1,4) lens.insert(loop_len[i]);
        if(lens.size() == 4) {
            cout << "NeverEnds" << endl;
            return 0; 
        }
    }

    unordered_set<ll> _s[5];
    get_full_times(1,'T',_s[1]);
    get_full_times(2,'T',_s[2]);
    get_full_times(3,'P',_s[3]);
    get_full_times(4,'C',_s[4]);
    ll _res = 0;
    for(ll x : _s[1]) {
        if(_s[2].count(x) && _s[3].count(x) && _s[4].count(x)) _res = max(_res, x);
    }
    if(_res < n) cout << _res << endl;
    else cout << "NeverEnds" << endl;

    return 0;
}