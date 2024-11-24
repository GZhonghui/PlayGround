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

ll q;
char s[maxn];

char ask(ll idx) {
    ll len = strlen(s+1);
    
    ll need_len = len, need_op = 0;
    while(idx > need_len) {
        need_len <<= 1;
        need_op += 1;
    }

    ll r = 0;
    while(idx > len) {
        ll mid = need_len >> 1;
        if(idx > mid) idx = idx - mid, r = 1 - r;
        need_len >>= 1;
    }
    return r ? (
        'a' <= s[idx] && s[idx] <= 'z' ? 
        s[idx] + 'A' - 'a' : s[idx] + 'a' - 'A'
    ) : s[idx];
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> (s+1) >> q;
    while(q--) {
        ll x; cin >> x; cout << ask(x) << " ";
    } cout << endl;

    return 0;
}