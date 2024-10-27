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
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,k;

unordered_map<ll,ll> c;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    ll q; cin >> q; while(q--) {
        static ll op, x;
        cin >> op;
        if(op == 1) {
            cin >> x;
            if(!c.count(x)) c[x] = 0; c[x] += 1;
        } else if(op == 2) {
            cin >> x;
            c[x] -= 1;
            if(c[x] == 0) c.erase(x);
        } else if(op == 3) {
            cout << (ll)c.size() << endl;
        }
    }

    return 0;
}