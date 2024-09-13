#include <algorithm>
#include <iostream>
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
const ll maxn = 42;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,k,p,a[maxn];

int main()
{
    cin >> n >> k >> p;
    for(ll i=1;i<=n;i+=1)
    {
        cin >> a[i];
    }

    ll ans = 0;
    ll s1 = n >> 1, s2 = n - s1;
    for(ll left_size=0; left_size<=k; left_size+=1)
    {
        ll right_size = k-left_size;
        if(left_size > s1 || right_size > s2) continue;

        vector<ll> left_numbers;
        for(ll j=0;j<(1<<s1);j+=1)
        {
            ll selceted = 0, left_sum = 0;
            for(ll kk=1;kk<=s1;kk+=1)
            {
                if(j & (1<<(kk-1))) selceted += 1, left_sum += a[kk];
            }
            if(selceted == left_size)
            {
                left_numbers.push_back(left_sum);
            }
        }
        sort(left_numbers.begin(),left_numbers.end());

        // right
        for(ll j=0;j<(1<<s2);j+=1)
        {
            ll selceted = 0, right_sum = 0;
            for(ll kk=1;kk<=s2;kk+=1)
            {
                if(j & (1<<(kk-1))) selceted += 1, right_sum += a[s1+kk];
            }
            if(selceted == right_size)
            {
                // left_numbers.push_back(left_sum);
                ll ac_left = p - right_sum;

                // 这里用二分查找计数，一开始没有想到这一点
                auto idx = upper_bound(left_numbers.begin(),left_numbers.end(),ac_left);

                /*
                for(ll i=0;i<left_numbers.size();i+=1)
                {
                    if(left_numbers[i] <= ac_left) ans += 1;
                }
                */
                
                if(idx == left_numbers.end())
                {
                    ans += (ll)left_numbers.size();
                }else
                {
                    ans += idx - left_numbers.begin();
                }
                
            }
        }
    }

    cout << ans << endl;

    return 0;
}