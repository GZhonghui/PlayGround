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

ll n,id = 0,tree[maxn][26],shortest[maxn],fa[maxn];
char s[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    memset(tree,-1,sizeof(tree));
    memset(shortest,-1,sizeof(shortest));
    memset(fa,-1,sizeof(fa));

    cin >> n;
    rep(i,1,n) {
        cin >> (s+1);
        ll len = strlen(s+1);

        ll now_id = 0;
        rep(j,1,len) {
            char now_c = s[j];
            if(tree[now_id][now_c-'a'] == -1) {
                tree[now_id][now_c-'a'] = ++id;
                fa[tree[now_id][now_c-'a']] = now_id;
            }
            now_id = tree[now_id][now_c-'a'];
        }

        ll ans = len, up = 0;
        while(now_id != 0) {
            if(shortest[now_id] != -1) {
                ans = min(ans, up + shortest[now_id]);
                shortest[now_id] = min(shortest[now_id], up);
            }
            else shortest[now_id] = up;
            now_id = fa[now_id];
            up += 1;
        }

        cout << ans << endl;

    }

    return 0;
}