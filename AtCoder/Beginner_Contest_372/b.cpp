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
const ll maxn = 30;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll m;

vector<ll> dfs(ll m)
{
    vector<ll> ans;
    if(m == 0) return ans;
    if(m == 1)
    {
        ans.push_back(0);
        return ans;
    }
    if(m == 2)
    {
        ans.push_back(0);
        ans.push_back(0);
        return ans;
    }
    
    ll rr = m % 3;
    ll mm = (m - rr) / 3;
    vector<ll> mv = dfs(mm);
    vector<ll> rv = dfs(rr);
    for(ll i=0;i<mv.size();i+=1) ans.push_back(mv[i] + 1);
    for(ll i=0;i<rv.size();i+=1) ans.push_back(rv[i]);
    return ans;
}

int main()
{
    cin >> m;
    vector<ll> ans = dfs(m);

    ll n = ans.size();
    cout << n << endl;
    for(ll i=0;i<n;i+=1) cout << ans[i] << " "; cout << endl;

    return 0;
}