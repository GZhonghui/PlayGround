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
const ll maxm = 2e5 + 8;
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
vector<ll> g[maxm]; // id of target OR id of edge

ll n,m,x[maxm],a[maxm];
map<ll,ll> input;

struct node {
    ll x,a;

    bool operator<(const node &r) const {
        return x < r.x;
    }
}nodes[maxm];

struct line {
    ll l,r;
    bool operator<(const line &other) const {
        return r < other.r;
    }
};

priority_queue<line> lines;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ll sum = 0;
    cin >> n >> m;
    rep(i,1,m) cin >> x[i];
    rep(i,1,m) { cin >> a[i]; sum += a[i]; }
    rep(i,1,m) { input[x[i]] = a[i]; nodes[i] = (node){x[i],a[i]}; }

    sort(nodes+1,nodes+1+m);

    if(sum != n) {
        cout << -1 << endl;
        return 0;
    }

    ll ans = 0, last_end = n + 1;
    // if(nodes[m].x != n)
    //    lines.push((line){nodes[m].x + 1, n});
    for(ll i=m; i>=1; i--) {
        ll left_stone = nodes[i].a - 1;
        if(nodes[i].x + 1 < last_end) {
            lines.push((line){nodes[i].x + 1, last_end - 1});
        }
        last_end = nodes[i].x;

        while(left_stone != 0) {
            if(lines.empty()) {
                cout << -1 << endl;
                return 0;
            }

            line target = lines.top(); lines.pop();
            if(target.r - target.l + 1 > left_stone) {
                ll a = target.r - left_stone + 1, b = target.r;
                a = a - nodes[i].x, b = b - nodes[i].x;
                ans += (a + b) * (b - a + 1) / 2;
                lines.push((line){target.l, target.r-left_stone});
                left_stone = 0;
            } else {
                left_stone -= target.r - target.l + 1;
                ll a = target.l - nodes[i].x, b = target.r - nodes[i].x;
                ans += (a + b) * (b - a + 1) / 2;
            }
        }
    }

    if(!lines.empty()) {
        cout << -1 << endl;
        return 0;
    }

    cout << ans << endl; 

    return 0;
}