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

#define mk make_pair
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> G[maxn]; // id of target OR id of edge

ll n,q,dis_allow[100],a[100];

// dfs的总方案会很多，但是不用担心，不用所有的都找到
// 我们只需要找到9000个左右就一定是足够的了
// 根据：鸽巢原理

vector< vector<ll> > ans[9000];
vector<ll> g[100];
vector<ll> now;

bool found = false;

void dfs(ll idx, ll sum)
{
    if(found) return; // 方案太多了，也不需要找到所有的方案
    if(idx > n) {
        ans[sum].push_back(now);
        if(ans[sum].size() > 1) {
            found = true;
        }
        return;
    }

    dfs(idx+1, sum);

    if(!dis_allow[idx]) {
        now.push_back(idx);
        for(ll i : g[idx]) dis_allow[i] += 1;
        dfs(idx+1,sum+a[idx]);
        for(ll i : g[idx]) dis_allow[i] -= 1;
        now.pop_back();
    }
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    memset(dis_allow,0,sizeof(dis_allow));

    cin >> n >> q;
    rep(i,1,n) cin >> a[i];

    ll x,y; // x < y
    rep(i,1,q) {
        cin >> x >> y;
        g[x].push_back(y);
    }

    dfs(1,0);

    rep(i,1,9000) {
        if(ans[i].size() > 1) {
            cout << ans[i][0].size() << endl;
            for(ll i : ans[i][0]) cout << i << " "; cout << endl;

            cout << ans[i][1].size() << endl;
            for(ll i : ans[i][1]) cout << i << " "; cout << endl;

            break;
        }
    }

    return 0;
}