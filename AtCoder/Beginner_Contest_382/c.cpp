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

ll n,m,a[maxn],b[maxn],ans[maxn];

struct node {
    ll id,value;

    bool operator<(const node &r) const {
        return value > r.value;
    }
}nodes[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;
    rep(i,1,n) cin >> a[i];
    rep(i,1,m) cin >> b[i];
    rep(i,1,m) {
        nodes[i] = (node){i,b[i]};
    }
    sort(nodes+1,nodes+1+m);

    ll test_people = 1;
    rep(i,1,m) {
        const node &now = nodes[i];
        if(test_people > n) {
            ans[now.id] = -1;
        } else {
            if(now.value >= a[test_people]) {
                ans[now.id] = test_people;
            } else {
                test_people += 1;
                i -= 1;
            }
        }
    }

    rep(i,1,m) {
        cout << ans[i] << endl;
    }
    return 0;
}