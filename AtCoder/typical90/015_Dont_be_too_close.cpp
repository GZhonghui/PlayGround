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
const ll maxn = 1e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,ans[maxn];

int main()
{
    cin >> n;

    ans[n] = n;
    for(ll k=n-1;k>=1;k-=1)
    {
        // dis == k, at least 2
        ans[k] = (ans[k+1] + min(k, n-k)) % mod;
    }

    for(ll i=1;i<=n;i+=1) cout << ans[i] << endl;
    return 0;
}