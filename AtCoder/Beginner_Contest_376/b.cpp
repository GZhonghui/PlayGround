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

ll n,q;

int main()
{
    cin >> n >> q;
    
    ll ans = 0, l = 1, r = 2;
    while(q--)
    {
        char h;
        ll target;
        cin >> h >> target;

        if(h == 'L')
        {
            ll l1 = l, l1ans = 0, l2 = l, l2ans = 0, local_ans = 1000;
            while(true)
            {
                if(l1 == target)
                {
                    local_ans = min(local_ans, l1ans);
                    break;
                }
                if(l1 == r)
                {
                    break;
                }

                l1 += 1;
                if(l1 == n + 1) l1 = 1;
                l1ans += 1;
            }
            while(true)
            {
                if(l2 == target)
                {
                    local_ans = min(local_ans, l2ans);
                    break;
                }
                if(l2 == r)
                {
                    break;
                }

                l2 -= 1;
                if(l2 == 0) l2 = n;
                l2ans += 1;
            }
            
            l = target;
            ans += local_ans;
        }else if(h == 'R')
        {
            ll r1 = r, r1ans = 0, r2 = r, r2ans = 0, local_ans = 1000;
            while(true)
            {
                if(r1 == target)
                {
                    local_ans = min(local_ans, r1ans);
                    break;
                }
                if(r1 == l)
                {
                    break;
                }

                r1 += 1;
                if(r1 == n + 1) r1 = 1;
                r1ans += 1;
            }
            while(true)
            {
                if(r2 == target)
                {
                    local_ans = min(local_ans, r2ans);
                    break;
                }
                if(r2 == l)
                {
                    break;
                }

                r2 -= 1;
                if(r2 == 0) r2 = n;
                r2ans += 1;
            }
            
            r = target;
            ans += local_ans;

        }

    }

    cout << ans << endl;

    return 0;
}