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

const ll maxn = 2e5 + 8;
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

ll n,q;
char s1[maxn],s2[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> q;
    while(q--) {
        cin >> n >> (s1 + 1) >> (s2 + 1);
        ll fixed = 0;
        rep(i,1,n) {
            if(s1[i] != s2[i]) {
                if(i <= n - 3 && s1[i] == 'T'  && s1[i+1] == 'I' && s1[i+2] == 'O' && s1[i+3] == 'T' && s2[i] == 'I') {
                    s1[i] = 'I';
                    s1[i+1] = 'S';
                    s1[i+2] = 'C';
                } else {
                    cout << "No" << endl;
                    goto no;
                }
            }
        }
        cout << "Yes" << endl;

        no:;
    }

    return 0;
}