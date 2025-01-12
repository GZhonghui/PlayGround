#pragma GCC optimize(2)

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

#include <atcoder/all>

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

const ll maxn = 1e5 + 8;
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

struct LowBitTree
{   
    // 树状数组求和的区间包括0的话，会出一点小问题，因为lowbit(0) = 0
    // 如果需要包括0的话，可以在Add和Sum的函数内部统一做一个偏移
    ll C[maxn << 1],n;
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
};

LowBitTree a_cnt,a_sum,b_cnt,b_sum;
atcoder::fenwick_tree<ll> a_cnt_ac(maxn << 1), a_sum_ac(maxn << 1), b_cnt_ac(maxn << 1), b_sum_ac(maxn << 1);

struct ask {
    ll x,y,id,block_id;

    bool operator<(const ask &other) const {
        if(block_id == other.block_id) return block_id & 1 ? y > other.y : y < other.y;
        return block_id < other.block_id;
    }
};

vector<ask> asks;

ll n,a[maxn],b[maxn],k,ans[maxn],block_size,a_total = 0, b_total = 0;
unordered_map<ll, ll> zip, unzip;

inline ll calc_value_to_target(
    ll value, ll target_length, ll target_toal,
    LowBitTree &cnt_tree, LowBitTree &sum_tree
) {
    ll res = 0;
    ll _idx = zip[value];
    ll cnt = cnt_tree.Sum(_idx);
    ll sum = sum_tree.Sum(_idx);
    res += value * cnt - sum;
    res += target_toal - sum - (target_length - cnt) * value;
    return res;
}

inline ll calc_value_to_target(
    ll value, ll target_length, ll target_toal,
    atcoder::fenwick_tree<ll> &cnt_tree, atcoder::fenwick_tree<ll> &sum_tree
) {
    ll res = 0;
    ll _idx = zip[value];
    ll cnt = cnt_tree.sum(0, _idx + 1);
    ll sum = sum_tree.sum(0, _idx + 1);
    res += value * cnt - sum;
    res += target_toal - sum - (target_length - cnt) * value;
    return res;
}

inline void add_to_target(
    ll value, ll k,
    ll &target_total, LowBitTree &target_cnt, LowBitTree &target_sum
) {
    ll _idx = zip[value];
    target_cnt.Add(_idx, k);
    target_sum.Add(_idx, k * value);
    target_total += k * value;
}

inline void add_to_target(
    ll value, ll k,
    ll &target_total, atcoder::fenwick_tree<ll> &target_cnt, atcoder::fenwick_tree<ll> &target_sum
) {
    ll _idx = zip[value];
    target_cnt.add(_idx, k);
    target_sum.add(_idx, k * value);
    target_total += k * value;
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    a_cnt.init(n << 1);
    a_sum.init(n << 1);
    b_cnt.init(n << 1);
    b_sum.init(n << 1);

    rep(i,1,n) cin >> a[i];
    rep(i,1,n) cin >> b[i];
    // block_size = sqrt(n);
    block_size = 1000;

    vector<ll> v;
    rep(i,1,n) v.pb(a[i]), v.pb(b[i]);
    sort(v.begin(), v.end());
    ll _idx = 0;
    for(ll x : v) {
        if(!zip.count(x)) {
            zip[x] = ++_idx;
            // unzip[_idx] = x;
        }
    }

    cin >> k;
    rep(i,1,k) {
        ll x,y,block_id;
        cin >> x >> y;
        block_id = x / block_size;
        asks.pb((ask){x,y,i,block_id});
    }
    sort(asks.begin(), asks.end());

    ll l = 0, r = 0, current_ans = 0;

    auto p = [&]() {
        // cout << l << ", " << r << ": " << current_ans << endl;
    };

    for(ask &now_q : asks) {
        while(l < now_q.x) {
            l += 1;
            current_ans += calc_value_to_target(a[l], r, b_total, b_cnt_ac, b_sum_ac);
            add_to_target(a[l], 1, a_total, a_cnt_ac, a_sum_ac);
            // p();
        }
        while(l > now_q.x) {
            current_ans -= calc_value_to_target(a[l], r, b_total, b_cnt_ac, b_sum_ac);
            add_to_target(a[l], -1, a_total, a_cnt_ac, a_sum_ac);
            l -= 1;
            // p();
        }

        while(r < now_q.y) {
            r += 1;
            current_ans += calc_value_to_target(b[r], l, a_total, a_cnt_ac, a_sum_ac);
            add_to_target(b[r], 1, b_total, b_cnt_ac, b_sum_ac);
            // p();
        }
        while (r > now_q.y) {
            current_ans -= calc_value_to_target(b[r], l, a_total, a_cnt_ac, a_sum_ac);
            add_to_target(b[r], -1, b_total, b_cnt_ac, b_sum_ac);
            r -= 1;
            // p();
        }
        
        ans[now_q.id] = current_ans;
    }

    rep(i,1,k) {
        cout << ans[i] << endl;
    }

    return 0;
}