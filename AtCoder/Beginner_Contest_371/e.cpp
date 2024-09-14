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

ll n,a[maxn], ans = 0;
unordered_map<ll,vector<ll> > c;

int main()
{
    // freopen("in.txt","r",stdin);

    cin >> n;
    ll total = ((1 + n) * n) >> 1;

    for(ll i=1;i<=n;i+=1)
    {
        cin >> a[i];
        c[a[i]].push_back(i);
        /*
        if(!c.count(a[i])) c[a[i]] = 0;

        ll l = 1, r = c.size();
        ll delta = 0; //(((l + r) * (r - l + 1)) >> 1);

        ans += delta; // + c[a[i]];
        cout << i << ": delta >= " << delta << endl;

        ll delta_right = 0;
        for(ll j=1;j<=i;j+=1)
        {
            unordered_set<ll> cc;
            for(ll k=j;k<=i;k+=1)
            {
                cc.insert(a[k]);
            }
            delta_right += cc.size();
        }
        cout << i << ": right delta = " << delta_right << endl;
        c[a[i]] += 1;
        */
    }

    // 转换思路
    // 总区间个数是固定的，是total
    // 对于每一个数字，出现在了这total个区间中的哪几个呢？
    // 出现在了几个区间中，这个数字的贡献就是几
    // 本体关键还是还是考虑，每个数字是怎样对最终结果作出贡献的
    for(auto i=c.begin();i!=c.end();i++)
    {
        ll left = 0, this_ans = total;
        vector<ll>& pos = i->second;
        if(!pos.size()) continue;

        pos.push_back(n+1);
        for(ll j=0;j<pos.size();j+=1)
        {
            ll right = pos[j];
            ll len = right - left - 1;
            this_ans -= ((1 + len) * len) >> 1;
            left = right;
        }
        ans += this_ans;
    }

    /*
    ll ans1 = 0;
    for(ll i=1;i<=n;i+=1)
    {
        for(ll j=i;j<=n;j+=1)
        {
            unordered_set<ll> cc;
            for(ll k=i;k<=j;k+=1)
            {
                cc.insert(a[k]);
            }
            ans1 += cc.size();
        }
    }

    cout << ans1 << endl;
    */

    cout << ans << endl;

    return 0;
}