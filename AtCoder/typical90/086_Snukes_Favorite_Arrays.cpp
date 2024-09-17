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

const ll mod = 1000000007;
const ll maxn = 16;
const ll maxq = 55;

const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,q,x[maxq],y[maxq],z[maxq],w[maxq],ans=1;

inline bool check(ll idx, ll *data)
{
    for(ll i=1;i<=q;i+=1)
    {
        if((data[x[i]] | data[y[i]] | data[z[i]]) != ((w[i] & ((ll)1<<(idx-1))) ? 1 : 0)) return false;
    }

    /*
    for(ll i=1;i<=n;i+=1)
    {
        cout << data[i] << " ";
    }
    cout << endl;

    for(ll i=1;i<=q;i+=1)
    {
        // ((w[i] & (1<<(idx-1))) ? 1 : 0) // （我发现这个写法有点蠢啊）
        // 记住这愚蠢的教训！！！

        cout << "Q " << i  << ":" << (data[x[i]] | data[y[i]] | data[z[i]]) << " = " << ((w[i] & (1<<(idx-1))) ? 1 : 0)
            << "(" << w[i] <<  " idx = " << idx << ")" << endl; 
    }
    */

    return true;
}

int main()
{
    cin >> n >> q;
    for(ll i=1;i<=q;i+=1)
    {
        cin >> x[i] >> y[i] >> z[i] >> w[i];
    }

    // [0, ((ll)1)>>60)
    for(ll i=1;i<=60;i+=1)
    {
        ll data[maxn],local_ans = 0;
        for(ll j=0;j<(1<<n);j+=1)
        {
            for(ll k=1;k<=n;k+=1)
            {
                data[k] = (j & (1<<(k-1))) ? 1 : 0;
            }
            // check data
            if(check(i,data)) local_ans += 1;
        }

        // cout << i << ":" << local_ans << endl;
        ans = (local_ans * ans) % mod;
    }
    
    cout << ans << endl;

    return 0;
}