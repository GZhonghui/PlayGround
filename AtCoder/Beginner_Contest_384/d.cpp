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

const ll maxn = 4e5 + 8;
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

ll n,s,a[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> s;
    rep(i,1,n) cin >> a[i];
    rep(i,1,n) a[i + n] = a[i];

    ll sum = 0;
    rep(i,1,n) sum += a[i];

    s = s % sum;
    
    /*if(s == 0) 
    {
        cout << "Yes" << endl;
        return 0;
    }*/

    queue<ll> Q;
    ll now_s = 0;
    rep(i,1,n<<1) {
        now_s += a[i];
        Q.push(a[i]);

        while(now_s > s) {
            now_s -= Q.front();
            Q.pop();
        }
        if(now_s == s) {
            cout << "Yes" << endl;
            return 0;
        }

    } 
    cout << "No" << endl;

    return 0;
}