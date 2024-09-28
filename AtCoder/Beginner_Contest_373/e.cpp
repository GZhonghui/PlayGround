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

const ll dx[4] = {-1,0,1,0};
const ll dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll maxm = 2e5 + 8;
const ll maxk = 1e12 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct node {
    ll id,got;

    bool operator<(const node &r) const
    {
        return got > r.got;
    }
};

ll sum_got = 0, left_got;
ll n,m,k,a[maxn],ans[maxn],nodes_sum[maxn],nodes_got[maxn];
node nodes[maxn];

ll count_elements_greater_than(ll a[], ll n, ll x) {
    ll* it = std::lower_bound(a, a + n, x, std::greater<ll>());

    return it - a;
}

// make_sure
inline bool sure_selected(ll nodes_id, ll new_got)
{
    ll final_got = nodes[nodes_id].got + new_got;

    ll bigger_count = count_elements_greater_than(nodes_got+1,n,final_got);

    if(bigger_count >= m) return false;

    ll poss_l = bigger_count + 1;
    ll poss_r = m;
    ll poss_size = poss_r - poss_l + 1;

    ll poss_sum = nodes_sum[poss_r] - nodes_sum[poss_l - 1];

    if(nodes_id <= m)
    {
        poss_sum += nodes[m+1].got;
        poss_sum -= nodes[nodes_id].got;
    }

    ll left_for_poss = left_got - new_got;
    ll need_of_poss = (final_got + 1) * poss_size - poss_sum;

    if(left_for_poss >= need_of_poss) return false;
    return true;
}

int main()
{
    cin >> n >> m >> k;

    for(ll i=1;i<=n;i+=1) {
        cin >> a[i];
        nodes[i] = (node){i,a[i]};

        sum_got += a[i];
    }

    left_got = k - sum_got;

    sort(nodes+1,nodes+1+n);

    nodes_sum[0] = 0;
    for(ll i=1;i<=n;i+=1)
    {
        nodes_sum[i] = nodes_sum[i-1] + nodes[i].got;
        nodes_got[i] = nodes[i].got;
    }

    for(ll i=1;i<=n;i+=1)
    {
        if(m == n) {
            ans[nodes[i].id] = 0;
            continue;
        }
        if(sure_selected(i,0)) {
            ans[nodes[i].id] = 0;
            continue;
        }

        if(!sure_selected(i,left_got)) {
            ans[nodes[i].id] = -1;
            continue;
        }

        ll l = 0, r = left_got;
        
        while(r - l > 3)
        {
            ll mid = (l + r) >> 1;
            if(sure_selected(i,mid))
            {
                r = mid;
            }else l = mid + 1;
        }

        for(ll j=l;j<=r;j+=1)
        {
            if(sure_selected(i,j))
            {
                ans[nodes[i].id] = j;
                break;
            }
        }
    }

    for(ll i=1;i<=n;i+=1)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}