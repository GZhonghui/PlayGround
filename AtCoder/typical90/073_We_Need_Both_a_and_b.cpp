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
const ll maxn = 100000 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,mem[maxn][3];
char c[maxn];

ll dfs(ll pos, ll ab, ll fa = -1)
{
    // 应该不需要记忆化，因为计算顺序是固定的
    // 不不不，还是需要，因为会重复计算
    if(mem[pos][ab] != -1) return mem[pos][ab];

    ll &ans = mem[pos][ab] = 0;
    if(ab == 0) {
        if(c[pos] == 'a') {
            ans = 1;
            for(ll to : G[pos]) {
                if(to == fa) continue;
                ans = (ans * (dfs(to,0,pos) + dfs(to,2,pos))) % mod;
            }
        } else ans = 0;
    } else if(ab == 1) {
        if(c[pos] == 'b') {
            ans = 1;
            for(ll to : G[pos]) {
                if(to == fa) continue;
                ans = (ans * (dfs(to,1,pos) + dfs(to,2,pos))) % mod;
            }
        } else ans = 0;
    } else if(ab == 2) {
        ll l = 1, r = 1;
        for(ll to : G[pos]) {
            if(to == fa) continue;
            l = (l * (dfs(to,0,pos) + dfs(to,1,pos) + 2*dfs(to,2,pos))) % mod;
            r = (r * (dfs(to,c[pos] == 'a' ? 0 : 1,pos) + dfs(to,2,pos))) % mod;
        }
        ans = ((l + mod) - r) % mod;
    }

    return ans % mod;
}

// 自己没想出来的点：

// 首先很重要的一点：dp[pos][0]表示的是
// pos为根的子树中，pos的连接分量全a，其他的连接分量全部满足包含ab
// 有多少种分割方式

// fa 是 x 的父节点，根据 x 计算 fa 的时候
// 以 x 为根的子树如果有 k 种分割方案
// 如果：x 和 fa 必需连接 或者 必需断开，则 x 的贡献就是 k
// 如果：x 和 fa 可以连接也可以断开，则 x 的贡献就是 2k

// 特别是计算dp[fa][2]（2表示ab都有）的时候
// 减法前面是：x的部分全是a（必须连接fa） + x的部分全是b（必须连接fa）
// + x的部分是ab（不连接fa，这样是合法的） + x的部分是ab（连接fa）
// 但是这样会多算，因为我们计算的是dp[fa][2]
// 上述算法有一些情况会导致fa的部分全a（假设fa是a）
// 所以减去：x部分是全a（和fa连接，也只能连接，没有别的选择） + x部分是ab（和ab断开）
// 以上这两种情况会导致fa的部分全a

// 总之，勉强搞明白了第一道树状DP，继续加油！

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    memset(mem,-1,sizeof(mem));

    cin >> n;
    rep(i,1,n) cin >> c[i];

    rep(i,1,n-1) {
        static ll a,b;
        cin >> a >> b;
        G[a].pb(b);
        G[b].pb(a);
    }

    cout << dfs(1,2) << endl;

    return 0;
}