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

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 5e3 + 8;
const ll maxd = 5e3 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct node
{
    ll d,c,s;
    bool operator<(const node &r) const
    {
        return d < r.d;
    }
};

ll n,dp[maxd];
node nodes[maxn];

int main()
{
    cin >> n;
    for(int i=1;i<=n;i+=1)
        cin >> nodes[i].d >> nodes[i].c >> nodes[i].s;

    // 初见的时候，很明显这里就是要排序，自己好像也理解为什么
    // 但是不知道怎么严格证明
    sort(nodes+1,nodes+1+n);

    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i+=1)
    {
        for(int j=nodes[i].d;j>=nodes[i].c;j-=1)
        {
            dp[j] = max(dp[j], dp[j-nodes[i].c] + nodes[i].s);
        }
    }

    ll ans = 0;
    for(int i=0;i<maxd;i+=1) ans = max(ans,dp[i]);
    cout << ans << endl;

    return 0;
}