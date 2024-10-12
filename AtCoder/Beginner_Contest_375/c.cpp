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

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 3e3 + 2;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,s = 0;
char m[5][maxn][maxn];
char fin[maxn][maxn];

inline void op(ll x, ll y, ll target)
{ 
    m[target][y][n+1-x] = m[target-1][x][y];
    fin[y][n+1-x] = m[target-1][x][y];
}

int main()
{
    cin >> n;
    for(ll i=1;i<=n;i+=1) {
        cin >> (m[s][i] + 1);
    }

    memcpy(fin,m,sizeof(fin));

    /*
    ll l = 1, r = n, rot = 1;
    while(l < r)
    {
        if(rot) for(ll i=l;i<=r;i+=1) 
        {
            swap(m[s][i][l],m[s][l][i]);
            swap(m[s][r][i],m[s][i][r]);
        }

        rot = 1 - rot;

        l += 1;
        r -= 1;
    }
    */

    ll rot = 1;
    for(ll i=1;i<=(n>>1);i+=1)
    {
        // memcpy(m[1-s],m[s],sizeof(m) >> 1);

        ll l = i, r = (n+1-i);
        for(ll t = 1; t <= rot; t += 1)
        {
            for(ll y=l,x=l; x<=r; x += 1) op(x,y,t);
            for(ll y=r,x=l; x<=r; x += 1) op(x,y,t);
            for(ll x=l,y=l; y<=r; y += 1) op(x,y,t);
            for(ll x=r,y=l; y<=r; y += 1) op(x,y,t);
        }
        

        /*
        for(ll x=l;x<=r;x+=1)
        {
            for(ll y=l;y<=r;y+=1)
            {
                m[1-s][y][n+1-x] = m[s][x][y];
                fin[y][n+1-x] = m[s][x][y];
            }
        }
        */

        rot = (rot + 1) % 4;
        // s = 1 - s;
    }

    for(ll i=1;i<=n;i+=1)
    {
        cout << (fin[i] + 1) << endl;
    }
    return 0;
}