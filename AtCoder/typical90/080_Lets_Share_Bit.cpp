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
const ll maxn = 100 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,d,a[maxn];

// 容斥原理，不难，但是要注意细节

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif

    cin >> n >> d;
    rep(i,1,n) cin >> a[i];

    ll ans = 0;
    for(ll i = 1; i < ((ll)1<<n); i += 1) {
        ll or_res = 0, or_count = 0;
        rep(j,1,n) if((ll)1<<(j-1) & i) {
            or_res |= a[j];
            or_count += 1;
        }

        ll one_count = 0;
        rep(j,1,d) if((ll)1<<(j-1) & or_res) {
            one_count += 1;
        }

        // or_count的奇偶，决定了是加还是减，这部分画一个集合的关系图就明白了
        // 容斥原理，or_count也就是重叠部分的集合的个数（or_count个集合重叠的部分）
        // 很简单：1个集合重叠，也就是没有重叠，这部分是加
        // 2个集合重叠，就是多加的部分，要减掉
        // 3个集合重叠，就是多减的部分，要加回来
        ll local = (ll)1 << (d - one_count);
        ans += local * ((or_count & 1) ? 1 : -1);
    }

    cout << ((ll)1 << d) - ans << endl;

    return 0;
}