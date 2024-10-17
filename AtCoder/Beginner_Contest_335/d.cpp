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
const ll maxn = 50;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,ans[maxn][maxn];

struct point
{
    ll x,y,dir,index;

    bool move_right()
    {
        ll new_dir = (dir + 1) % 4;
        swap(new_dir, dir);
        if(move_forward())
        {
            return true;
        }

        swap(new_dir, dir);
        move_forward();

        return false;
    }

    bool move_forward()
    {
        ll xx = x + dx[dir];
        ll yy = y + dy[dir];

        if(ans[xx][yy] == -1)
        {
            ans[xx][yy] = ++index;
            // cout << xx << ", " << yy << endl;
            x = xx, y = yy;
            return true;
        }

        return false;
    }
};

int main()
{
    memset(ans,-1,sizeof(ans));
    cin >> n;

    ll x = (n+1)>>1, y = (n+1)>>1;
    ans[x][y] = 0;
    point s = (point){x, y, 3, 0};

    for(ll i=1; i<=(n*n-1); i+=1)
    {
        s.move_right();
    }

    for(ll i=1;i<=n;i+=1)
    {
        for(ll j=1;j<=n;j+=1)
        {
            if(ans[i][j] == 0) cout << 'T';
            else cout << ans[i][j];
            cout << " ";
        }
        cout << endl;
    }

    return 0;
}