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

ll n;

int main()
{
    cin >> n;

    for(ll a = 0; a <= n; a += 1)
    {
        for(ll b = 0; b <= n; b += 1)
        {
            for(ll c = 0; c <= n; c += 1)
            {
                if(a + b + c <= n)
                {
                    cout << a << " " << b << " " << c << endl;
                }
            }
        }
    }

    return 0;
}