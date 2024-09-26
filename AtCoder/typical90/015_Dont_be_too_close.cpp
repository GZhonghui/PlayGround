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

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const ll dx[4] = {-1,0,1,0};
const ll dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 1e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll n,ans[maxn];

struct Quick_C
{
    ll Jc[maxn],mod; // Jc是阶乘的意思，可以预先计算
    void pre_cal()
    {
        Jc[0]=Jc[1]=1;
        for(ll i=2;i<maxn;i++)
            Jc[i]=Jc[i-1]*i%mod;
    }
    void exgcd(ll a,ll b,ll &x,ll &y)
    {
        if(!b) x=1,y=0;
        else
        {
            exgcd(b,a%b,y,x);
            y-=x*(a/b);
        }
    }
    ll niYuan(ll a,ll b)
    {
        ll x,y;
        exgcd(a,b,x,y);
        return (x+b)%b;
    }
    ll cal_C(ll a,ll b) // a >= b C_{a}^{b}
    {
        return Jc[a]*niYuan(Jc[b],mod)%mod*niYuan(Jc[a-b],mod)%mod;
    }
}solver;

int main()
{
    solver.mod = ::mod;
    solver.pre_cal();

    cin >> n;

    /*
    ans[n] = n;
    for(ll k=n-1;k>=1;k-=1)
    {
        // dis == k, at least 2
        ans[k] = (ans[k+1] + min(k, n-k)) % mod;
    }
    */

   // 这个复杂度，一开始想大了
   // 这里是调和级数的时间复杂度
    for(ll k=1;k<=n;k+=1) {
        // calc k
        ans[k] = 0;

        for(ll selected = 1; selected <= (n / k + 1); selected += 1) {
            // 关键是这个组合数的式子，也就是a和b的值
            ll a = n - (k - 1) * (selected - 1);
            ll b = selected;
            if(a >= 1 && a >= b) {
                ans[k] = (ans[k] + solver.cal_C(a,b)) % mod;
            }
        }
    }

    for(ll i=1;i<=n;i+=1) cout << ans[i] << endl;
    return 0;
}