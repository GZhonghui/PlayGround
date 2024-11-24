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
const ll maxn = 5e5 + 8;
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
char s[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> k >> (s+1); s[0] = '0';

    ll one_th = 0, zero_len = 0;
    rep(i,1,n) {
        if(s[i] == '1') {
            if(s[i-1] == '0') {
                one_th += 1;
            }
            cout << '1';
        } else if(s[i] == '0') {
            if(one_th == k-1) {
                zero_len += 1;
            } else {
                if(one_th == k) {
                    // while(zero_len--) cout << 0;
                    rep(i,1,zero_len) cout << '0'; zero_len = 0;
                }
                // cout << "[i = " << i << ", one_th = " << one_th << "]";
                cout << '0';
            }
        }
    }
    rep(i,1,zero_len) cout << '0'; zero_len = 0;
    cout << endl;

    return 0;
}