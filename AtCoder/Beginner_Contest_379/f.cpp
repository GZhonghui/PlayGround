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

struct ask {
    ll l,r,id;
    bool operator<(const ask &oth) const {
        return r > oth.r;
    }
};

ll n,q,h[maxn],left_to[maxn];
vector< ask > asks;

struct LowBitTree
{
    int C[maxn],n;
    void init(int n=maxn-1) // 待验证：n为支持的数据规模，支持的下标范围是[1,n]
    {
        this->n=n;
        memset(C,0,sizeof(int)*maxn);
    }
    int lowbit(int x){ return x&(-x); }
    int Sum(int pos) // 待验证：计算Sum[1,pos]
    {
        int ans=0;
        for(int i=pos;i;i-=lowbit(i)) ans+=C[i];
        return ans;
    }
    void Add(int pos,int value) // 待验证：在pos的位置增加value
    {
        for(int i=pos;i<=n;i+=lowbit(i)) C[i]+=value;
    }
}solver;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> q;
    rep(i,1,n) cin >> h[i];
    rep(i,1,q) {
        static ll l,r; cin >> l >> r;
        asks.pb((ask){l,r,i});
    }

    sort(asks.begin(), asks.end());

    /* 这部分思路虽然是不对的，但是set的二份搜索方法也要学习一下
    set<ll> left;
    unordered_map<ll,ll> last_show;
    rep(i,1,n) {
        auto it = left.upper_bound(h[i]);
        if(it == left.end()) {
            left_to[i] = 1;
        } else {
            left_to[i] = last_show[*it] + 1;
        }
        left.insert(h[i]);
        last_show[h[i]] = i;
    }
    */

    // 单调栈！学习
    stack<ll> s;
    rep(i,1,n) {
        while(!s.empty() && h[s.top()] < h[i]) {
            s.pop();
        }
        if(s.empty()) left_to[i] = 1;
        else left_to[i] = s.top() + 1;
        s.push(i);
    }

    solver.init();
    unordered_map<ll,ll> ans;

    ll after = n;
    for(const ask &a : asks) {
        while(after > a.r) {
            solver.Add(static_cast<int>(left_to[after]), 1);
            after -= 1;
        }
        ans[a.id] = solver.Sum(static_cast<int>(a.l+1));
    }

    rep(i,1,q) cout << ans[i] << endl;

    return 0;
}