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

const ll maxn = 1e3 + 8;
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

ll h,w,x,y;
char m[maxn][maxn],t[(ll)1e4 + 10];
set< pair<ll,ll> > cnt;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> h >> w >> x >> y;
    rep(i,1,h) {
        cin >> (m[i] + 1);
    }
    cin >> (t+1);
    ll tl = strlen(t+1);

    unordered_map<char,ll> dir;
    dir['U'] = 0;
    dir['D'] = 2;
    dir['L'] = 3;
    dir['R'] = 1;
    rep(i,1,tl) {
        ll j = dir[t[i]];
        ll xx = x + dx[j];
        ll yy = y + dy[j];
        if(1 <= xx && xx <= h && 1 <= yy && yy <= w && m[xx][yy] != '#') {
            x = xx;
            y = yy;
        }
        if(m[x][y] == '@') {
            cnt.insert(mk(x,y));
        }
    }
    cout << x << " " << y << " " << cnt.size() << endl;
    
    return 0;
}