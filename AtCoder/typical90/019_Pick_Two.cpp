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

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 210;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,a[maxn << 1];
map<pair<ll,ll>,ll> ans;
// unordered_map 的 key 不能使用 pair

ll dp(ll l, ll r)
{
    if(ans.count(make_pair(l,r))) return ans[make_pair(l,r)];

    ll res = 0;
    if(r - l + 1 >= 2) {
        res = abs(a[r] - a[l]) + dp(l+1,r-1);

        for(ll offset = 2; offset < (r-l+1); offset += 2) {
            res = min(res, dp(l,l+offset-1) + dp(l+offset,r));
        }
    }

    return ans[make_pair(l,r)] = res;
}

int main()
{
    cin >> n;
    for(ll i=1;i<=(n<<1);i+=1) cin >> a[i];
    cout << dp(1,n<<1) << endl;

    return 0;
}