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

struct node
{
    ll a,b;

    bool operator<(const node &r) const
    {
        return a < r.a;
    }
};

ll n,k,a[maxn],b[maxn];

ll ac()
{
    vector<node> ns;
    rep(i, n) ns.push_back((node){a[i],b[i]});
    sort(ns.begin(),ns.end());

    ll ans = inf, maxv = 0, sumv = 0;
    priority_queue<ll> bs;

    rep(i, n)
    {
        // add ith
        maxv = ns[i-1].a;
        if(bs.size() < k)
        {
            bs.push(ns[i-1].b);
            sumv += ns[i-1].b;
        } else
        {
            if(ns[i-1].b < bs.top())
            {
                sumv += ns[i-1].b - bs.top();
                bs.pop();
                bs.push(ns[i-1].b);
            }
        }

        if(i >= k)
        {
            // update ans
            ans = min(ans, maxv * sumv);
        }
    }

    return ans;
}

int main()
{
    ll T;
    cin >> T;
    while(T--)
    {
        cin >> n >> k;
        rep(i, n) cin >> a[i];
        rep(i, n) cin >> b[i];
        cout << ac() << endl;
    }

    return 0;
}