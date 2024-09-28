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
const ll maxn = 5e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,a = INT64_MIN, b = INT64_MIN;

int main()
{
    cin >> n;
    for(ll i=1;i<=n;i+=1)
    {
        ll x; cin >> x;
        a = max(a,x);
    }
    for(ll i=1;i<=n;i+=1)
    {
        ll x; cin >> x;
        b = max(b,x);
    }

    cout << a + b << endl;


    return 0;
}