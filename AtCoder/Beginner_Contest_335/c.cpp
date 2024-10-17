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
const ll maxn = 2e6 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

struct pos
{
    int32_t x,y;

    void print()
    {
        cout << x << " " << y << endl;
    }
}ps[maxn];

ll n,q;

int main()
{
    cin >> n >> q;

    ll s = q + 10;
    for(ll i=1;i<=n;i+=1)
    {
        ps[s + i - 1] = (pos){i,0};
    }

    while(q--)
    {
        ll op,p;
        char dir;
        cin >> op;
        if(op == 1)
        {
            cin >> dir;
            if(dir == 'R') ps[s-1].x = ps[s].x + 1, ps[s-1].y = ps[s].y;
            if(dir == 'L') ps[s-1].x = ps[s].x - 1, ps[s-1].y = ps[s].y;
            if(dir == 'U') ps[s-1].x = ps[s].x, ps[s-1].y = ps[s].y + 1;
            if(dir == 'D') ps[s-1].x = ps[s].x, ps[s-1].y = ps[s].y - 1;
            s -= 1;
        }
        else
        {
            cin >> p;
            ps[s + p - 1].print();
        }
    }
    
    return 0;
}