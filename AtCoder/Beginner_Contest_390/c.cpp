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

const ll maxn = 1e3 + 8;
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

ll h,w;
char m[maxn][maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> h >> w;
    rep(i,1,h) {
        cin >> (m[i] + 1);
    }
    
    ll h_min = maxn, h_max = -1, w_min = maxn, w_max = -1;

    rep(i,1,h) {
        rep(j,1,w) {
            if(m[i][j] == '#') {
                h_min = min(i, h_min);
                h_max = max(i, h_max);

                w_min = min(j, w_min);
                w_max = max(j, w_max);

            }
        }
    }

    rep(i,h_min,h_max) {
        rep(j,w_min,w_max) {
            if(m[i][j] == '.') {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
    


    return 0;
}