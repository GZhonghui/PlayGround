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

const ll maxs = 13;
struct status {
    ll a[maxs],b[maxs],c[maxs];

    string hash() {
        sort(a+1,a+1+a[0]);
        sort(b+1,b+1+b[0]);
        sort(c+1,c+1+c[0]);

        string res = "";
        rep(i,0,a[0]) res += to_string(a[i]) + ',';
        rep(i,0,b[0]) res += to_string(b[i]) + ',';
        rep(i,0,c[0]) res += to_string(c[i]) + ',';
        return res;
    }
}init;

ll n,m,l;

map<string,bool> mem;
bool win(status s, bool is_a) {
    string id = (is_a ? '+' : '-') + s.hash();
    if(mem.count(id)) return mem[id];
    bool &res = mem[id] = false;

    if(is_a) {
        if(!s.a[0]) return res = false;
        rep(i,1,s.a[0]) {
            rep(j,1,s.c[0]) {
                if(s.c[j] < s.a[i]) {
                    status next = s;
                    swap(next.a[i], next.c[j]);
                    if(!win(next, !is_a)) return res = true;
                }
            }
            status next = s;
            next.c[++next.c[0]] = next.a[i];
            swap(next.a[next.a[0]], next.a[i]);
            next.a[0] --;
            if(!win(next, !is_a)) return res = true;
        }

    } else { // is b
        if(!s.b[0]) return res = false;
        rep(i,1,s.b[0]) {
            rep(j,1,s.c[0]) {
                if(s.c[j] < s.b[i]) {
                    status next = s;
                    swap(next.b[i], next.c[j]);
                    if(!win(next, !is_a)) return res = true;
                }
            }
            status next = s;
            next.c[++next.c[0]] = next.b[i];
            swap(next.b[next.b[0]], next.b[i]);
            next.b[0] --;
            if(!win(next, !is_a)) return res = true;
        }

    }

    return res;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m >> l;
    init.a[0] = n; rep(i,1,n) cin >> init.a[i];
    init.b[0] = m; rep(i,1,m) cin >> init.b[i];
    init.c[0] = l; rep(i,1,l) cin >> init.c[i];

    cout << (win(init, true) ? "Takahashi" : "Aoki") << endl;

    return 0;
}