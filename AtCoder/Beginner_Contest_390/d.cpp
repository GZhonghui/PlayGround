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

const ll maxn = 2e5 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 8;
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

ll n,a[maxn];
unordered_set<ll> results;
vector<ll> groups;

void dfs(ll i)
{
    if (i == n + 1) {
        ll _t = 0;
        for (auto s : groups) {
            _t ^= s;
        }
        results.insert(_t);
        return;
    }
    
    for (ll idx = 0; idx < groups.size(); idx++) {
        groups[idx] += a[i];
        dfs(i + 1);
        groups[idx] -= a[i];
    }
    
    groups.push_back(a[i]);
    dfs(i + 1);
    groups.pop_back();
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n) {
        cin >> a[i];
    }
        
    dfs(1);

    cout << results.size() << endl;

    return 0;
}
