// 按照题解的思路写的

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
const ll maxn = 2e6 + 8;
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

ll n,ans[maxn];
char s[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> (s+1);

    ll value = 0;
    rep(i,1,n) {
        value += (s[i] - '0') * i;
    }

    rep(i,1,n) {
        ans[i] = value;
        value -= (s[n+1-i] - '0') * (n+1-i);
    }

    ll idx = 1;
    while(true) {
        if(idx > n && ans[idx] == 0){
            ans[0] = idx - 1;
            break;
        }

        ans[idx + 1] += ans[idx] / 10;
        ans[idx] %= 10;
        idx += 1;
    }

    for(ll i = ans[0]; i > 0; i--) {
        cout << ans[i];
    } cout << endl;

    return 0;
}