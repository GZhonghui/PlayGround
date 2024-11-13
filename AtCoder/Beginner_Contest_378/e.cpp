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

ll n,m,a[maxn],s[maxn];

struct LowBitTree
{
    int C[maxn],n;
    void init(int n=maxn-1) // n为支持的数据规模，支持的下标范围是[1,n]
    {
        this->n=n;
        memset(C,0,sizeof(int)*maxn);
    }
    int lowbit(int x){ return x&(-x); }
    int Sum(int pos) // 计算Sum[1,pos]
    {
        pos += 1;
        int ans=0;
        for(int i=pos;i;i-=lowbit(i)) ans+=C[i];
        return ans;
    }
    void Add(int pos,int value) // 在pos的位置增加value
    {
        pos += 1;
        for(int i=pos;i<=n;i+=lowbit(i)) C[i]+=value;
    }
}solver;

// 本题提供的一个很重要的 多个区间的求和思路
// 区间求和是 前缀和的右端点 - 左端点
// 多个区间求和就是 右端点的求和 - 左端点的求和

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> m;
    rep(i,1,n) cin >> a[i];

    s[0] = 0;
    rep(i,1,n) s[i] = (s[i-1] + a[i]) % m;

    solver.init();
    solver.Add(0, 1);

    ll ans = 0, sum_l = 0;
    rep(r,1,n) {
        ll local = 0;
        local += s[r] * r - sum_l;
        local += m * (r - solver.Sum(s[r]));

        solver.Add(s[r], 1);
        sum_l += s[r];

        ans += local;
    }
    cout << ans << endl;

    return 0;
}