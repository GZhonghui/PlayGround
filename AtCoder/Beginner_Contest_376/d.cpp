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
#define rep(i, n) for (ll i = 1; i <= (n); i++)

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct node
{
    ll id,d;
};

queue<node> Q;

ll n,m,dis[maxn];
vector<ll> G[maxn];

int main()
{
    cin >> n >> m;
    rep(i, m)
    {
        static ll a,b;
        cin >> a >> b;
        G[a].push_back(b);
    }

    memset(dis,-1,sizeof(dis));
    Q.push((node){1,0});

    while(!Q.empty())
    {
        node t = Q.front();
        Q.pop();

        if(dis[t.id] != -1)
        {
            if(t.id == 1)
            {
                cout << t.d << endl;
                return 0;
            }
            else continue;
        }

        dis[t.id] = t.d;
        for(ll i=0;i<G[t.id].size();i+=1)
        {
            Q.push((node){G[t.id][i],t.d+1});
        }
    }

    cout << -1 << endl;


    return 0;
}