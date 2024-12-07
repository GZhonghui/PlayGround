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
const ll maxn = 2e6 + 8;
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

ll n;

struct Sieve
{
    bool check[maxn]; // 被check标记的（check[i] == true）都是非质数（not_prime）
    vector<ll> prime; // 找到的质数

    void init()
    {
        memset(check,0,sizeof(check));
        prime.clear();
    }
    void calc(ll n) // 找到[,n]以内的质数
    {
        for(ll i=2;i<=n;i++)
        {
            if(!check[i]) {
                prime.push_back(i);
                for(ll j=i*i;j<=n;j+=i) {
                    check[j] = true;
                }
            }
        }
    }
}solver;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    solver.init();
    solver.calc(sqrt(n) + 1);

    ll ans = 0;
    bool running = true;
    for(ll i = 0; i < solver.prime.size(); ++ i) {
        ll x = solver.prime[i];
        if(running) {
            ll x8 = x * x * x * x * x * x * x * x;
            if(x8 > n) running = false;
            else { ans ++; }
        }
        
        if(x * x * x * x > n) break;
        for(ll j = i + 1; j < solver.prime.size(); ++ j) {
            ll y = solver.prime[j];

            if(x * x * y * y <= n) { ans ++; }
            else break;
        }
    }

    cout << ans << endl;

    return 0;
}