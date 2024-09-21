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
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,q,x,flag[maxn],sum = 0;
char c,s[maxn];

int main()
{
    memset(flag,0,sizeof(flag));
    cin >> n >> q;
    cin >> (s+1);

    for(ll i=1;i<=n;i+=1)
    {
        if(i+2 <= n && s[i] == 'A' && s[i+1] == 'B' && s[i+2] == 'C')
        {
            flag[i] = 1;
            sum += 1;
        }
    }

    while(q--)
    {
        cin >> x >> c;
        s[x] = c;
        for(ll i=x-2;i<=x;i+=1)
        {
            ll l = i, r = i+2;
            if(l >= 1 && r <= n)
            {
                ll new_res = (s[l] == 'A' && s[l+1] == 'B' && s[r] == 'C');
                ll delta = new_res - flag[l];
                flag[l] = new_res;
                sum += delta;
            }
        }

        cout << sum << endl;
    }

    return 0;
}