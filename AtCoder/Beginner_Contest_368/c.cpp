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
#define rep(i, n) for (ll i = 1; i <= (n); i++)

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

ll n, step = 1;

inline void next_step(ll &x, ll &res) { 
    if(step == 3) x -= 3;
    else x -= 1;

    step += 1; if(step == 4) step = 1; 
    res += 1;
}

inline ll kill(ll x)
{
    ll res = 0;
    while(step != 1)
    {
        next_step(x, res);

        if(x <= 0) return res;
    }

    ll c = x / 5;
    res += c * 3;
    x -= c * 5;

    while(x > 0) next_step(x, res);
    
    return res;
}

int main()
{
    cin >> n;

    ll ans = 0;
    rep(i, n)
    {
        static ll x;
        cin >> x;
        ans += kill(x);
    }
    cout << ans << endl;

    return 0;
}