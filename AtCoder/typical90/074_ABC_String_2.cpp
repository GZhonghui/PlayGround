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
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n;
char s[maxn];

// 思维题 很巧妙
// 简单记录一下思路：{a,b,c} = {0,1,2}
// 然后比如：选择一个位置 b -> a，前面的全部 a -> b（这一步很像退位）
// b -> a 只需要一步，所以权重是1，同理 c 的权重是2
// 详细还是要看官方的解说，其中还给出了一些想这种题的技巧

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> (s+1);

    ll ans = 0, now = 1;
    rep(i,1,n) {
        ans += (s[i] - 'a') * now;
        now <<= 1;
    }
    cout << ans << endl;

    return 0;
}