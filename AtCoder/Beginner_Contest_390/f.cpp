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

const ll maxn = 3e5 + 8;
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

ll n,a[maxn],l[maxn],r[maxn];

inline void find_bound() {
    stack<ll> s;
    rep(i,1,n) {
        while(!s.empty() && a[s.top()] < a[i]){
            s.pop();
        }
        l[i] = s.empty() ? 0 : s.top();
        s.push(i);
    }

    while(!s.empty()) {
        s.pop();
    }

    rre(i,1,n) {
        while(!s.empty() && a[s.top()] <= a[i]) {
            s.pop();
        }
        r[i] = s.empty() ? n + 1 : s.top();
        s.push(i);
    }
}

inline void find_bound_1() {
    stack<ll> s;
    rep(i,1,n) {
        while(!s.empty() && a[s.top()] > a[i]){
            s.pop();
        }
        l[i] = s.empty() ? 0 : s.top();
        s.push(i);
    }

    while(!s.empty()) {
        s.pop();
    }

    rre(i,1,n) {
        while(!s.empty() && a[s.top()] >= a[i]) {
            s.pop();
        }
        r[i] = s.empty() ? n + 1 : s.top();
        s.push(i);
    }
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n) {
        cin >> a[i];
    }

    ll sum_1 = 0;
    find_bound();
    rep(i,1,n) {
        sum_1 += a[i] * (i - l[i]) * (r[i] - i);
    }

    rep(i,1,n) {
        a[i] = -a[i];
    }

    ll sum_2 = 0;
    find_bound();
    rep(i,1,n) {
        sum_2 += -a[i] * (i - l[i]) * (r[i] - i);
    }

    rep(i,1,n) {
        a[i] = -a[i];
    }

    sum_2 = 0;
    find_bound_1();
    rep(i,1,n) {
        sum_2 += a[i] * (i - l[i]) * (r[i] - i);
    }

    ll sum_3 = n * (n + 1);

    vector<ll> _p[maxn];
    rep(i,1,n) {
        _p[a[i]].pb(i);
    }

    ll sum_4 = 0;
    rep(i,1,n) {
        ll _begin = 0;
        for(auto j : _p[i]) {
            sum_4 += (j - _begin) * (n - j + 1);
            _begin = j;
        }
    }
    
    cout << sum_1 << ", " << sum_2 << ", " << sum_3 << ", " << sum_4 << endl;
    cout << sum_1 - sum_2 + sum_3 - sum_4 << endl;
    
    return 0;
}