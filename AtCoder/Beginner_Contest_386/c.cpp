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

const ll maxn = 5e5 + 8;
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

ll k;
char s[maxn], t[maxn];

inline bool check0() {
    ll len_s = strlen(s+1), len_t = strlen(t+1);

    ll ps = 1, pt = 1, k = 1;
    while(ps <= len_s && pt <= len_t) {
        if(s[ps] != t[pt]) {
            if(k) k -= 1;
            else return false;
        }

        ps += 1, pt += 1;
    }
    if(ps == len_s + 1 && pt == len_t + 1) return true;
    ll last = max(len_s + 1 - ps, len_t + 1 - pt);
    return last <= k;
}

inline bool check1() {
    ll len_s = strlen(s+1), len_t = strlen(t+1);

    ll ps = 1, pt = 1, k = 1;
    while(ps <= len_s && pt <= len_t) {
        if(s[ps] != t[pt]) {
            if(k) k -= 1, ps -= 1;
            else return false;
        }

        ps += 1, pt += 1;
    }
    if(ps == len_s + 1 && pt == len_t + 1) return true;
    ll last = max(len_s + 1 - ps, len_t + 1 - pt);
    return last <= k;
}


inline bool check2() {
    ll len_s = strlen(s+1), len_t = strlen(t+1);

    ll ps = 1, pt = 1, k = 1;
    while(ps <= len_s && pt <= len_t) {
        if(s[ps] != t[pt]) {
            if(k) k -= 1, pt -= 1;
            else return false;
        }

        ps += 1, pt += 1;
    }
    if(ps == len_s + 1 && pt == len_t + 1) return true;
    ll last = max(len_s + 1 - ps, len_t + 1 - pt);
    return last <= k;
}


int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> k >> (s+1) >> (t+1);

    bool ans = check0() || check1() || check2();
    cout << (ans ? "Yes" : "No") << endl;

    return 0;
}