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
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 100 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,m = 1;
char s[maxn][maxn];
char a[maxn][maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    memset(a,0,sizeof(a));

    cin >> n;
    rep(i, 1, n) {
        cin >> (s[i] + 1);
        m = max(m, (ll)strlen(s[i] + 1));
    }
    rep(i, 1, n) {
        rep(j, 1, strlen(s[i] + 1)) {
            a[j][n+1-i] = s[i][j];
        }
    }

    rep(i, 1, m) {
        ll r = 1;
        rep(j, 1, n) {
            if(a[i][j]) r = j;
        }
        rep(j, 1, r) {
            if(a[i][j]) cout << a[i][j];
            else cout << '*';
        }
        cout << endl;
    }

    return 0;
}