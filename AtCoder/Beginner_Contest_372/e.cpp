#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
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
const ll maxk = 11;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,q,fa[maxn];
priority_queue<ll> qs[maxn];

ll root(ll x)
{
    if(fa[x] == x) return x;
    return fa[x] = root(fa[x]);
}

inline bool same(ll x, ll y)
{
    return root(x) == root(y);
}

inline void link(ll x, ll y)
{
    ll rx = root(x), ry = root(y);
    for(ll i=1;i<=maxk;i+=1)
    {
        if(!qs[rx].empty())
        {
            qs[ry].push(qs[rx].top());
            qs[rx].pop();
        }
    }

    fa[rx] = ry;
}

int main()
{
    cin >> n >> q;
    for(ll i=1;i<=n;i+=1) {
        fa[i] = i;
        qs[i].push(i);
    }

    ll a,b,c;
    while(q--)
    {
        cin >> a >> b >> c;
        if(a == 1)
        {
            link(b,c);
            // for(ll i=1;i<=n;i+=1) cout << fa[i] << " "; cout << endl;
            // cout << "link " << b << " - " << c << endl;
        }else if(a == 2)
        {
            ll r = root(b);
            if(qs[r].size() >= c)
            {
                vector<ll> t;
                for(ll i=1;i<c;i+=1)
                {
                    t.push_back(qs[r].top());
                    qs[r].pop();
                }
                cout << qs[r].top() << endl;
                for(ll i=0;i<t.size();i+=1) qs[r].push(t[i]);
            }else cout << -1 << endl;
            /*
            for(ll i=n;i>=1;i-=1)
            {
                if(same(i,b))
                {
                    // cout << "test " << i << " - " << b << endl; 
                    c -= 1;
                    if(!c)
                    {
                        cout << i << endl;
                        break;
                    }
                }
            }
            if(c) cout << -1 << endl;
            */
        }
    }

    return 0;
}