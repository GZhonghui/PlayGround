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
#include <cmath>
#include <unordered_map>
#include <unordered_set>

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const ll dx[4] = {0,0,1,-1};
const ll dy[4] = {1,-1,0,0};

const ll mod = 1e9+7;
const ll maxn = 4e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct LowBitTree
{
    ll C[maxn],n;
    void init(ll n=maxn-1) // 待验证：n为支持的数据规模，支持的下标范围是[1,n]
    {
        this->n=n;
        memset(C,0,sizeof(ll)*maxn);
    }
    ll lowbit(ll x){ return x&(-x); }
    ll Sum(ll pos) // 待验证：计算Sum[1,pos]
    {
        ll ans=0;
        for(ll i=pos;i;i-=lowbit(i)) ans+=C[i];
        return ans;
    }
    void Add(ll pos,ll value) // 待验证：在pos的位置增加value
    {
        for(ll i=pos;i<=n;i+=lowbit(i)) C[i]+=value;
    }
};

ll lis(ll numbers_count, ll* numbers, ll* dp, bool allow_equal = true)
{
    ll buffer[numbers_count + 1];
    buffer[0] = 1, buffer[1] = numbers[0], dp[0] = 1;

    for(ll i = 1; i < numbers_count; i += 1)
    {
        ll index = allow_equal
            ?std::upper_bound(buffer+1, buffer+1+buffer[0], numbers[i]) - buffer - 1
            :std::lower_bound(buffer+1, buffer+1+buffer[0], numbers[i]) - buffer - 1;
        if(index >= buffer[0])
        {
            buffer[0] += 1;
            buffer[buffer[0]] = numbers[i];
        }else
        {
            buffer[index+1] = numbers[i];
        }
        dp[i] = index + 1;
    }

    return buffer[0];
}

struct node
{
    ll v;
    bool operator<(const node& r) const
    {
        return v > r.v;
    }
};

ll n,h[maxn],rev_h[maxn],ans[maxn],dp[maxn],dp2[maxn];
priority_queue<node> q;

int32_t main()
{
    cin >> n;
    for(ll i=1;i<=n;i+=1){
        cin >> h[i];
        rev_h[n-i+1] = -h[i];
    }

    // lis(n,rev_h+1,dp+1); dp[0] = 0;
    // for(ll i=1;i<=n;i+=1)
    {
        // cout << dp[n-i] << " ";
        // dp2[i] = dp[n-i];
    }

    // cout << endl;

    ans[n] = 0;
    for(ll i=n-1;i>=1;i-=1)
    {
        q.push((node){h[i+1]});
        while(q.top().v != h[i+1])
        {
            q.pop();
        }
        ans[i] = q.size();
    }

    for(ll i=1;i<=n;i+=1)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}