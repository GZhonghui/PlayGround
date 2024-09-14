#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <cmath>
#include <unordered_map>
#include <unordered_set>

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const ll dx[4] = {0,0,1,-1};
const ll dy[4] = {1,-1,0,0};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,q,x[maxn],p[maxn],sum[maxn];

std::pair<ll, ll> find_range(ll x[], ll n, ll l, ll r) {
    // 注意调整指针来适应从1开始的下标
    ll* start = std::lower_bound(x + 1, x + n + 1, l);
    ll* end = std::upper_bound(x + 1, x + n + 1, r);

    // 由于 upper_bound 返回的是第一个大于目标的元素位置，需要向前移动一位
    if (end != (x + 1)) {
        --end;
    }

    // 检查找到的区间是否有效（即确保 start <= end）
    if (start > end || *start < l || *end > r) {
        return make_pair(-1, -1);  // 返回无效区间
    }

    // 返回区间的下标，数组下标已经从1开始
    return make_pair(static_cast<ll>(start - x), static_cast<ll>(end - x));
}

int main()
{
    cin >> n;


    for(ll i=1;i<=n;i+=1)
    {
        cin >> x[i];
    }
    sum[0] = 0;
    for(ll i=1;i<=n;i+=1)
    {
        cin >> p[i];
        sum[i] = sum[i-1] + p[i];
    }

    cin >> q;
    while(q--)
    {
        ll l,r;
        cin >> l >> r;
        
        auto idx = find_range(x,n,l,r);
        if(idx.first == -1) cout << 0 << endl;
        else
        {
            cout << sum[idx.second] - sum[idx.first - 1] << endl;
        }
    }
    return 0;
}