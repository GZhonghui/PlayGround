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

ll n,q,slash_sum[maxn],xth[3][maxn],sum[3][maxn];
char s[maxn];

inline ll slash_count(ll l, ll r)
{
    if(l <= r) return slash_sum[min(n,r)] - slash_sum[max((ll)1,l)-1]; return 0;
}

inline bool check(ll l, ll r, ll len)
{
    ll left_1 = sum[1][l-1], right_2 = sum[2][r+1];
    ll need_1 = left_1 + len, need_2 = right_2 + len;
    if(xth[1][need_1] == -1 || xth[2][need_2] == -1) return false;
    ll r_side_1 = max(l-1,xth[1][need_1]), l_side_2 = min(r+1,xth[2][need_2]);
    if(r_side_1 >= l_side_2) return false;
    return slash_count(r_side_1+1,l_side_2-1) >= 1;
}

inline ll solve(ll l, ll r)
{
    if(!check(l,r,0)) return 0;

    ll left = 0, right = n;
    while(right - left > 3) {
        ll mid = (left + right) >> 1;
        if(check(l,r,mid)) left = mid;
        else right = mid - 1; 
    }

    for(ll i = right; i >= left; i--) {
        if(check(l,r,i)) return (i << 1) | 1;
    }
    return 0;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> q >> (s+1);
    slash_sum[0] = 0;
    rep(i,1,n) {
        slash_sum[i] = slash_sum[i-1] + (s[i] == '/' ? 1 : 0);
    }

    memset(xth,-1,sizeof(xth));
    memset(sum,0,sizeof(sum));
    ll one = 0, two = 0;
    rep(i,1,n) {
        if(s[i] == '1') xth[1][++one] = i;
        sum[1][i] = sum[1][i-1] + (s[i] == '1' ? 1 : 0);
    }
    for(ll i=n;i>=1;i--) {
        if(s[i] == '2') xth[2][++two] = i;
        sum[2][i] = sum[2][i+1] + (s[i] == '2' ? 1 : 0);
    }
    xth[1][0] = 0, xth[2][0] = n + 1;

    while(q--) {
        static ll l,r; cin >> l >> r;
        cout << solve(l,r) << endl;
    }

    return 0;
}