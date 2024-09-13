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
const ll maxn = 102;
const ll maxs = 1e5 + 2;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,s,a[maxn],b[maxn],dp[maxn][maxs];

int main()
{
    // freopen("in.txt","r",stdin);

    // 因为题目要求是“恰好”，所以初始值是-1（不是0）【重要】
    memset(dp,-1,sizeof(dp));
    dp[0][0] = 0;

    cin >> n >> s;
    for(ll i=1;i<=n;i+=1)
    {
        cin >> a[i] >> b[i];
    }

    for(ll i=1;i<=n;i+=1)
    {
        for(ll j=s;j>=a[i];j-=1)
        {
            if(dp[i-1][j-a[i]] >= 0)
            {
                dp[i][j] = 1;
            }
            /*
            if(dp[j-a[i]][0] == i-1)
            {
                dp[j][0] = i;
                dp[j][1] = 1;
            }
            */
        }
        for(ll j=s;j>=b[i];j-=1)
        {
            if(dp[i-1][j-b[i]] >= 0)
            {
                dp[i][j] = 2;
            }
            /*
            if(dp[j-b[i]][0] == i-1)
            {
                dp[j][0] = i;
                dp[j][1] = 2;
            }
            */
        }
    }

    if(dp[n][s] > 0)
    {
        vector<char> ans;
        ll ss = s, nn = n;
        while(ss > 0)
        {
            ans.push_back((dp[nn][ss] == 1) ? 'A' : 'B');
            ss -= ((dp[nn][ss] == 1) ? a[nn] : b[nn]);
            nn -= 1;
        }

        for(ll i=ans.size();i>=1;i-=1)
        {
            cout << ans[i-1];
        }
        cout << endl;

    }else cout << "Impossible" << endl;

    return 0;
}