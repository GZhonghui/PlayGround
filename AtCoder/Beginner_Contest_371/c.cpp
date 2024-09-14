// 我真是傻逼

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
const ll maxn = 10;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct edge
{
    ll x,y;
    bool operator==(const edge& other) const
    {
        return (x==other.x && y==other.y) || (x==other.y&&y==other.x);
    }
};

vector<edge> g,h;

ll n, ans = INT64_MAX, p[9] = {0,1,2,3,4,5,6,7,8}, revp[9] = {0,1,2,3,4,5,6,7,8};
ll mg,mh,a[maxn][maxn];
ll gmap[maxn][maxn],hmap[maxn][maxn];

inline ll calc()
{
    ll this_ans = 0;

    for(ll i=1;i<n;i+=1)
    {
        for(ll j=i+1;j<=n;j+=1)
        {
            // i < j
            bool e1 = (gmap[i][j] == 1 || gmap[j][i] == 1);
            bool e2 = (hmap[p[i]][p[j]] == 1 || hmap[p[j]][p[i]] == 1);
            if(e1!=e2)
            {
                this_ans += a[i][j];
            }
        }
    }

    if(this_ans == 0)
    {
        // for(ll i=1;i<=8;i+=1) cout << p[i] << " "; cout << endl;
    }
    return this_ans;
}

inline ll calc1()
{
    ll this_ans = 0;
    for(ll i=0;i<g.size();i+=1)
    {
        bool found = false;
        for(ll j=0;j<h.size();j+=1)
        {
            edge new_h = (edge){p[h[j].x],p[h[j].y]};
            if(g[i] == new_h)
            {
                found = true;
                break;
            }
        }
        
        ll xx = revp[g[i].x],yy=revp[g[i].y];
        // if(!found) this_ans += a[min(g[i].x,g[i].y)][max(g[i].x,g[i].y)];
        if(!found) this_ans += a[min(xx,yy)][max(xx,yy)];
    }

    for(ll i=0;i<h.size();i+=1)
    {
        edge new_h = (edge){p[h[i].x],p[h[i].y]};
        bool found = false;
        for(ll j=0;j<g.size();j+=1)
        {
            if(g[j] == new_h)
            {
                found = true;
                break;
            }
        }
        
        if(!found) this_ans += a[min(h[i].x,h[i].y)][max(h[i].x,h[i].y)];
        // if(!found) this_ans += a[min(new_h.x,new_h.y)][max(new_h.x,new_h.y)];
    }

    if(this_ans == 7)
    {
        for(ll i=1;i<=8;i+=1) cout << p[i] << " "; cout << endl;
        for(ll i=1;i<=8;i+=1) cout << revp[i] << " "; cout << endl;
    }
    return this_ans;
}

int main()
{
    memset(hmap,0,sizeof(hmap));
    memset(gmap,0,sizeof(gmap));

    cin >> n;
    cin >> mg;
    for(ll i=0;i<mg;i+=1)
    {
        ll x,y;
        cin >> x >> y;
        g.push_back((edge){x,y});
        gmap[x][y] = gmap[y][x] = 1;
    }

    cin >> mh;
    for(ll i=0;i<mh;i+=1)
    {
        ll x,y;
        cin >> x >> y;
        h.push_back((edge){x,y});
        hmap[x][y] = hmap[y][x] = 1;
    }
    for(ll i=1;i<n;i+=1)
    {
        for(ll j=i+1;j<=n;j+=1)
        {
            cin >> a[i][j];
        }
    }

    do
    {
        for(ll i=1;i<=n;i+=1)
        {
            revp[p[i]] = i;
        }
        ans = min(ans,calc1());
        // for(ll i=1;i<=8;i+=1) cout << p[i] << " "; cout << endl;
        

    } while (next_permutation(p+1,p+1+n));

    cout << ans << endl;
    
    return 0;
}