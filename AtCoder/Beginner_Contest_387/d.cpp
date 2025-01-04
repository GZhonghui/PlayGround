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

ll h,w;
char m[maxn][maxn];
bool v[maxn][maxn][2];

struct node {
    ll x,y,steps,next_up_down;
};

queue<node> Q;
ll solve(ll x, ll y, ll init_v) {
    ll res = inf;

    memset(v,0,sizeof(v));
    while(!Q.empty()) Q.pop();
    Q.push((node){x,y,0,init_v});
    while(!Q.empty()) {
        node now = Q.front(); Q.pop();
        if(v[now.x][now.y][now.next_up_down]) continue;
        
        if(m[now.x][now.y] == 'G') {
            res = min(res, now.steps);
            break;
        }

        v[now.x][now.y][now.next_up_down] = true;
        if(now.next_up_down) {
            ll xx = now.x + 1, yy = now.y;
            if(1 <= xx && xx <= h && 1 <= yy && yy <= w && m[xx][yy] != '#' && !v[xx][yy][1-now.next_up_down]) {
                Q.push((node){xx,yy,now.steps+1,1-now.next_up_down});
            }

            xx = now.x - 1;
            if(1 <= xx && xx <= h && 1 <= yy && yy <= w && m[xx][yy] != '#' && !v[xx][yy][1-now.next_up_down]) {
                Q.push((node){xx,yy,now.steps+1,1-now.next_up_down});
            }

        } else {
            ll xx = now.x, yy = now.y + 1;
            if(1 <= xx && xx <= h && 1 <= yy && yy <= w && m[xx][yy] != '#' && !v[xx][yy][1-now.next_up_down]) {
                Q.push((node){xx,yy,now.steps+1,1-now.next_up_down});
            }

            yy = now.y - 1;
            if(1 <= xx && xx <= h && 1 <= yy && yy <= w && m[xx][yy] != '#' && !v[xx][yy][1-now.next_up_down]) {
                Q.push((node){xx,yy,now.steps+1,1-now.next_up_down});
            }
        }
    }
    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> h >> w;
    rep(i,1,h) cin >> (m[i] + 1);

    ll x,y;
    rep(i,1,h) rep(j,1,w) {
        if(m[i][j] == 'S') {
            x = i, y = j;
        }
    }

    ll res = min(solve(x,y,1), solve(x,y,0));

    if(res >= inf) cout << -1 << endl;
    else cout << res << endl;


    return 0;
}