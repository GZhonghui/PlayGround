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

const ll maxn = 500000 + 8;
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

ll k;
char s[maxn], t[maxn];
map< pair<ll, ll>, ll > mem;
ll mem_raw[maxn * 45];

ll dis(ll i, ll j) {
    if(i == 0 && j == 0) return 0;
    if(i == 0) return j;
    if(j == 0) return i;
    if(abs(i - j) > k) return abs(i - j);
    // if(mem.count(mk(i,j))) return mem[mk(i,j)];
    ll id = i * 42 + j;
    if(mem_raw[id] != -1) return mem_raw[id];

    ll res = min(
        dis(i-1, j) + 1,
        min(
            dis(i, j-1) + 1,
            dis(i-1, j-1) + (s[i] == t[j] ? 0 : 1)
        )
    );
    return mem_raw[id] = res;
    // return mem[mk(i,j)] = res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    memset(mem_raw, -1, sizeof(mem_raw));
    cin >> k >> (s+1) >> (t+1);
    cout << ((dis(strlen(s+1), strlen(t+1)) <= k) ? "Yes" : "No") << endl;

    return 0;
}