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
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

const int maxhw = 17;

char map[maxhw][maxhw];
bool v1[maxhw][maxhw],v2[maxhw][maxhw];
ll h,w,sx,sy,ans = 0;

inline bool in(ll x, ll y)
{
    return 1 <= x && x <= h && 1 <= y && y <= w;
}

void dfs(ll x, ll y, ll depth)
{
    // v1[x][y] = true;

    if(depth == 0)
    {
        for(ll i=0;i<4;i+=1)
        {
            ll xx = x + dx[i], yy = y + dy[i];
            if(in(xx,yy) && !v2[xx][yy] && map[xx][yy] == '.')
            {
                v2[xx][yy] = true;
                dfs(xx, yy, depth + 1);
                v2[xx][yy] = false;
            }
        }
    }else
    {
        if(x == sx && y == sy)
        {
            ans = max(ans, depth);
        }else
        {
            for(ll i=0;i<4;i+=1)
            {
                ll xx = x + dx[i], yy = y + dy[i];
                if(in(xx,yy) && !v2[xx][yy] && map[xx][yy] == '.')
                {
                    v2[xx][yy] = true;
                    dfs(xx, yy, depth + 1);
                    v2[xx][yy] = false;
                }
            }
        }
    }
}

int main()
{
    memset(v1,0,sizeof(v1));
    memset(v2,0,sizeof(v2));

    cin >> h >> w;
    for(ll i=1;i<=h;i+=1)
    {
        cin >> (map[i] + 1);
    }

    for(ll i=1;i<=h;i+=1)
    {
        for(ll j=1;j<=w;j+=1)
        {
            if(map[i][j] == '.' && !v1[i][j])
            {
                sx = i, sy = j;
                dfs(i,j,0);
            }
        }
    }

    if(ans <= 2)
    {
        cout << -1 << endl;
    }else
    {
        cout << ans << endl;
    }
    return 0;
}