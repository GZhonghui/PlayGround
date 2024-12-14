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
typedef double f;

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

ll n,k,a[maxn],b[maxn],sa[maxn],sb[maxn],ans[maxn];
unordered_map<ll,ll> zip,unzip;

struct query {
    ll x,y,id;
    bool operator<(const query &r) const {
        if(x == r.x) return y < r.y;
        return x < r.x;
    }
}qs[maxn];

struct LowBitTree
{   
    // 树状数组求和的区间包括0的话，会出一点小问题，因为lowbit(0) = 0
    // 如果需要包括0的话，可以在Add和Sum的函数内部统一做一个偏移
    int C[maxn],n;
    void init(int n=maxn-1) // n为支持的数据规模，支持的下标范围是[1,n]
    {
        this->n=n;
        memset(C,0,sizeof(int)*maxn);
    }
    int lowbit(int x){ return x&(-x); }
    int Sum(int pos) // 计算Sum[1,pos]
    {
        int ans=0;
        for(int i=pos;i;i-=lowbit(i)) ans+=C[i];
        return ans;
    }
    void Add(int pos,int value) // 在pos的位置增加value
    {
        for(int i=pos;i<=n;i+=lowbit(i)) C[i]+=value;
    }
}s1,s2;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n; set<ll> _t;
    sa[0] = sb[0] = 0;
    rep(i,1,n) { cin >> a[i]; _t.insert(a[i]); sa[i] = a[i] + sa[i-1]; }
    rep(i,1,n) { cin >> b[i]; _t.insert(b[i]); sb[i] = b[i] + sb[i-1]; }

    ll idx = 0;
    for(ll _x : _t) {
        zip[_x] = ++idx;
        unzip[idx] = _x;
    }

    cin >> k;
    rep(i,1,k) {
        ll x,y; cin >> x >> y;
        qs[i] = (query){x,y,i};
    }

    sort(qs+1,qs+1+k);

    s1.init();

    ll _temp[maxn], last_x = 0;
    rep(i,1,k) {
        if(last_x != qs[i].x) {
            rep(j,last_x+1,qs[i].x) {
                s1.Add(zip[a[j]],1);
                s2.Add(zip[a[j]],a[j]);
            }
            ll _sum_min = 0;
            rep(j,1,n) {
                _temp[j] = sa[qs[i].x] * j + sb[j] * qs[i].x;
                _sum_min += (qs[i].x - s1.Sum(zip[b[j]])) * b[j] + s2.Sum(zip[b[j]]);
                _temp[j] -= 2 * _sum_min;
            }

            last_x = qs[i].x;
        }

        ans[qs[i].id] = _temp[qs[i].y];
    }

    rep(i,1,k) cout << ans[i] << endl;

    return 0;
}