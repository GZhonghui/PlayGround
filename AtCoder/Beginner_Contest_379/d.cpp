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

ll n,k;
map<ll,ll> ct;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ll q,day = 0; cin >> q; while(q--) {
        static ll op,t,h; cin >> op;
        if(op == 1) {
            if(!ct.count(day)) ct[day] = 0;
            ct[day] += 1;
        } else if(op == 2) {
            cin >> t;
            day += t;
        } else if (op == 3) {
            cin >> h;
            ll last_day = day - h, ans = 0;
            vector<ll> to_del;
            for(auto i = ct.begin(); i != ct.end(); i++) {
                if(i->first <= last_day) {
                    ans += i->second;
                    to_del.push_back(i->first);
                } else break;
            }
            for(ll i : to_del) ct.erase(i);
            cout << ans << endl;
        }
    }

    return 0;
}