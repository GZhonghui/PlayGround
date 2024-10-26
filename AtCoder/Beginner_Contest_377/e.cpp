// 置换
// 本题初见没有做出来
// 类似的ABC367E也是写了很久没有写出来
// 置换真的是弱项
// 在这里记录一点思路

// Q1：为什么是2^k次？
// A：简单来说，数学归纳法
// 其实在推导的过程中，自己的公式中也出现了很多次2^k这个数字，但是没有想到是用在这里
// TODO：详细解释

// Q2：有没有可能是先一段环外的路径，再进入环，这样的话就不好计算了
// A：不可能，每个节点入度为1，出度为1，可能想象，就是若干个环，没有环外的部分

// Q3：本题和ABC367E有什么区别？
// A：本题的P会改变，所以不能累加（或者说不方便累加，从这里理解为什么是2^k）
// ABC367E的P不会改变，是P作用在其他的数组上，所以可以累加

// 另外，把图画出来，顺着路径走一走，可以帮助理解为什么是2^k

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
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll maxl = 2e2 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

uint64_t qpow(uint64_t base, uint64_t times, uint64_t mod)
{
    if(times == 0) return 1;
    if(times == 1) return base;

    uint64_t ans = qpow(base, times>>1, mod) % mod;
    
    ans = ans * ans % mod;
    if(times % 2) ans = ans * base % mod;

    return ans;
}

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,k,p[maxn],ans[maxn];

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> k;
    rep(i, 1, n) cin >> p[i];

    memset(ans,-1,sizeof(ans));

    rep(i, 1, n) {
        if(ans[i] != -1) continue;

        vector<ll> loop;
        unordered_set<ll> flag;

        ll now = i;
        while(!flag.count(now))
        {
            flag.insert(now);
            loop.push_back(now);

            now = p[now];
        }

        ll loop_size = loop.size();

        ll rk = qpow(2, k, loop_size);

        rep(j, 0, loop_size - 1)
        {
            ans[loop[j]] = loop[(j + rk) % loop_size];
        }
    }

    rep(i, 1, n) cout << ans[i] << " "; cout << endl;

    return 0;
}