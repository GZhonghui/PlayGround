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

string n;

inline bool check(ll x) {
    ll sum = 0, _x = x;
    while(x) {
        sum += x % 10;
        x /= 10;
    }

    return _x % sum == 0;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    if(n.length() < 7) {
        ll _n = stoi(n);

        bool last = false;
        rep(i, _n, _n << 1) {
            bool now = check(i);
            if(now && last) {
                cout << i - 1 << endl;
                return 0;
            }
            last = now;
        }

        cout << -1 << endl;
        return 0;
    }

    string head = "00";
    memcpy((void *)head.c_str(), (void *)n.c_str(), 2);
    ll _head = stoi(head);

    auto zeros = [](int cnt) {
        while(cnt--) cout << 0;
    };

    if(10 <= _head && _head <= 16) {
        cout << 17;
    } else if(17 <= _head && _head <= 25) {
        cout << 26;
    } else if(26 <= _head && _head <= 34) {
        cout << 35;
    } else if(35 <= _head && _head <= 61) {
        cout << 62;
    } else if(62 <= _head && _head <= 99) {
        cout << 107;
    }
    zeros(n.length() - 2);
    cout << endl;

    return 0;
}