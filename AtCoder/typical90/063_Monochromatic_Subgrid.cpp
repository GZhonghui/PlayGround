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

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

const ll maxh = 10;
const ll maxw = 10000 + 10;

ll h,w,a[maxh][maxw];

int main()
{
    cin >> h >> w;
    for(ll i=1;i<=h;i+=1)
    {
        for(ll j=1;j<=w;j+=1)
        {
            cin >> a[i][j];
        }
    }

    ll ans = 0;

    for(ll i=1; i<(1<<h); i+=1)
    {
        unordered_map<ll,ll> counter;
        ll maxw = 0;

        for(ll j=1;j<=w;j+=1)
        {
            ll local = -1;
            bool failed = false;
        
            for(ll k=1;k<=h;k+=1)
            {
                if(i & (1<<(k-1)))
                {
                    // test target
                    if(local == -1)
                    {
                        local = a[k][j];
                    }else if(a[k][j] == local)
                    {

                    }else
                    {
                        failed = true;
                    }
                }
            }
            if(!failed)
            {
                if(!counter.count(local)) counter[local] = 0;
                counter[local] += 1;
                maxw = max(maxw, counter[local]);
            }
        }

        ll nowh = 0, ii = i;
        while(ii)
        {
            if(ii & 1) nowh += 1;
            ii >>= 1;
        }

        ans = max(ans, nowh * maxw);
    }

    cout << ans << endl;

    return 0;
}