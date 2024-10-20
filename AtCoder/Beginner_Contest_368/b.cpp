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

priority_queue<ll> q;

int main()
{
    ll n;
    cin >> n;
    rep(i, n) {
        static ll x;
        cin >> x;
        q.push(x);
    }

    ll ans = 0;
    while(true)
    {
        ll x1 = q.top(); q.pop();
        ll x2 = q.top(); q.pop();
        if(x2 <= 0) break;

        q.push(x1-1);
        q.push(x2-1);
        ans += 1;
    }
    cout << ans << endl;

    return 0;
}