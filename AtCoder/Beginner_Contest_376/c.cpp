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

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,a[maxn],b[maxn];

bool cmp(ll x, ll y)
{
    return y < x;
}

int main()
{
    cin >> n;
    rep(i, n) cin >> a[i];
    rep(i, n-1) cin >> b[i];

    sort(a+1,a+1+n,cmp);
    sort(b+1,b+1+n-1,cmp);

    ll pa, pb = 1;
    vector<ll> kill;
    rep(pa, n)
    {
        if(pb < n && b[pb] >= a[pa])
        {
            pb += 1;
        }
        else
        {
            kill.push_back(a[pa]);
        }
    }

    if(kill.size() == 1) cout << kill[0] << endl;
    else cout << -1 << endl; 

    return 0;
}