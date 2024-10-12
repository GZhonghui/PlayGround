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

struct point
{
    f x,y;
    f dis(point r) {
        f dx = x-r.x, dy = y-r.y;
        return sqrt(dx*dx+dy*dy);
    }
}ps[maxn];

ll n;

int main()
{
    cin >> n;
    for(ll i=1;i<=n;i+=1) {
        f x,y;
        cin >> ps[i].x >> ps[i].y;
    }
    ps[0].x = 0, ps[0].y = 0;

    f ans = ps[0].dis(ps[n]);

    for(ll i=0;i<n;i+=1) {
        ans += ps[i].dis(ps[i+1]);
    }

    cout << fixed << setprecision(10) << ans << endl;
    return 0;
}