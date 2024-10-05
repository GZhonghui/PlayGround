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
const ll maxn = 24;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,a[maxn];

int main()
{
    cin >> n;
    for(ll i=1;i<=n;i+=1) cin >> a[i];

    ll ans = INT64_MAX;
    for(ll i=0; i<((ll)1 << n); i+=1)
    {
        ll x = 0, y = 0;
        for(ll j=1;j<=n;j+=1)
        {
            if(i & ((ll)1 << (j-1))) x += a[j];
            else y += a[j];
        }

        ans = min(ans, max(x,y));

    }

    cout << ans << endl;
    return 0;
}