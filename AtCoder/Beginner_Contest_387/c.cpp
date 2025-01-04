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

ll n,k,num[200],len;
std::string s;

ll dfs(ll index, bool full, ll limit) {
    if(index > len) return 1;

    ll res = 0;
    if(full) {
        ll real_limit = min(limit-1, num[index]);
        if(real_limit == num[index]) {
            res += dfs(index+1, true, limit);
            res += dfs(index+1, false, limit) * real_limit;
        } else {
            res += dfs(index+1, false, limit) * (real_limit + 1);
        }
    } else {
        res = limit * dfs(index+1, false, limit);
    }
    return res;
}

ll sum(ll l) {
    if(l == len) return 0;
    // ll res = sum(l+1);
    ll res = 0;
    for(ll i=l+1;i<len;i++) {
        for(ll j=1;j<=9;j++) {
            ll local = 1;
            for(ll k=i+1;k<=len;k++) local *= j;
            res += local;
        } 
    }
// 221852052834757
// 221852052834757
    
    for(ll i=1;i<num[l];i++) {
        ll local = 1;
        for(ll j=l+1;j<=len;j++) local *= i;
        res += local;
    }
    res += dfs(l+1,true,num[l]);
    return res;
}

ll cnt(ll x) {
    s = std::to_string(x);
    for(ll i=0; i<s.length(); i++) {
        num[i+1] = s[i] - '0';
    }
    len = s.length();

    return sum(1);
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    
    ll l,r; cin >> l >> r;
    cout << cnt(r) - cnt(l-1) << endl;

    return 0;
}