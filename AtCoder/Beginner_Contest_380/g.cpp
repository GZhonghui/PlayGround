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
const ll mod = 998244353;
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

struct LowBitTree
{   
    // 树状数组求和的区间包括0的话，会出一点小问题，因为lowbit(0) = 0
    // 如果需要包括0的话，可以在Add和Sum的函数内部统一做一个偏移
    ll C[maxn],n;
    void init(ll n=maxn-1) // n为支持的数据规模，支持的下标范围是[1,n]
    {
        this->n=n;
        memset(C,0,sizeof(ll)*maxn);
    }
    ll lowbit(ll x){ return x&(-x); }
    ll Sum(ll pos) // 计算Sum[1,pos]
    {
        ll ans=0;
        for(ll i=pos;i;i-=lowbit(i)) ans+=C[i];
        return ans;
    }
    void Add(ll pos,ll value) // 在pos的位置增加value
    {
        for(ll i=pos;i<=n;i+=lowbit(i)) C[i]+=value;
    }
}tree;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
    if(!b) { d = a; x = 1; y = 0; }
    else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}

// 扩展欧几里得法，计算a的逆元，p是模数，a和p需要是互质的
ll inverse_element_exgcd(ll a, ll p){
    ll d,x,y;
    exgcd(a,p,d,x,y);
    return d == 1 ? (x+p)%p : -1;
}

ll n,k,a[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> k;
    rep(i,1,n) {
        cin >> a[i];
    }

    ll total = 0;
    tree.init();
    rep(i,1,n) {
        ll local = (i - 1) - tree.Sum(a[i]);
        tree.Add(a[i], 1);
        total += local;
    }

    ll fixed_inner = (k * (k - 1)) >> 1;

    ll up = 0;

    tree.init();
    ll l = 1, r = k, current_cnt = 0;
    rep(i,1,k) {
        current_cnt += (i - 1) - tree.Sum(a[i]);
        tree.Add(a[i], 1);
    }

    while(r <= n) {
        up += ((total - current_cnt) << 1) + fixed_inner;
        up %= mod;

        l ++, r ++;

        if(r <= n) {
            current_cnt += k - tree.Sum(a[r]);
            tree.Add(a[r], 1);
            tree.Add(a[l - 1], -1);
            current_cnt -= tree.Sum(a[l - 1]);
        }
    }

    ll down = (n - k + 1) << 1;
    // cout << up << " / " << down << endl;

    ll inv = inverse_element_exgcd(down, mod);
    cout << (inv * up) % mod << endl;

    return 0;
}