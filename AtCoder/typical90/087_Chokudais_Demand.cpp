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
const ll maxn = 50;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll dist[maxn][maxn],dist_bck[maxn][maxn],n,p,k;

namespace ac
{
    long long N, P, K, A[69][69];
    long long dist[69][69];

    int count_number(long long lens) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (A[i][j] == -1) dist[i][j] = lens;
                if (A[i][j] != -1) dist[i][j] = A[i][j];
            }
        }
        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
        int cnt = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (dist[i][j] <= P) cnt++;
            }
        }
        return cnt;
    }

    long long get_border(long long cnts) {
        long long cl = 1, cr = 5000000000LL, cm, minx = 5000000000LL;
        for (int i = 0; i < 40; i++) {
            cm = (cl + cr) / 2LL;
            int res = count_number(cm);
            if (res <= cnts) { cr = cm; minx = min(minx, cm); }
            else { cl = cm; }
        }
        return minx;
    }

    int main() {
        long long L = get_border(K);
        long long R = get_border(K - 1);
        if (R - L >= 2000000000LL) return -1;
        else return R - L;
    }
}

inline void floydWarshall(ll selected_value) {
    memcpy(dist,dist_bck,sizeof(ll)*maxn*maxn);
    for(ll i=1;i<=n;i+=1) for(ll j=1;j<=n;j+=1)
        dist[i][j] = (dist[i][j] == -1) ? selected_value : dist[i][j];

    for (ll k = 1; k <= n; ++k) {
        for (ll i = 1; i <= n; ++i) {
            for (ll j = 1; j <= n; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

inline ll check(ll selected_value)
{
    floydWarshall(selected_value);

    ll count = 0;
    for(ll i=1;i<n;i+=1)
    {
        for(ll j=i+1;j<=n;j+=1)
        {
            if(dist[i][j] <= p) count += 1;
        }
    }

    return count;
}

inline ll search(ll k)
{
    if(k > (n * (n - 1) / 2)) return 0;

    // 本来这里的l初始值设定为了0
    // 正数不包括0啊，我真是犯蠢了
    // [l,r]是二分搜索的范围，不应该包括0
    // 因为这一点debug了好久
    // 还找了ac的代码跑随机数据
    // 我真是服了我自己了
    // 认真读题目啊
    // 这道题的二分的部分也还是值得再复习的
    ll l = 1, r = 1e9 + 100;
    while(r - l > 3)
    {
        ll mid = (l + r) >> 1;
        ll count = check(mid);
        if(count < k)
        {
            r = mid - 1;
        }else l = mid;
    }

    ll r_to = r;
    while(r_to >= l)
    {
        if(check(r_to) >= k) break;
        r_to -= 1;
    }

    return r_to;
}

int32_t main_test()
{
    
    n = 3;
    p = (ll)rand() % (ll)100 + 1;

    for(ll i=1;i<=n;i+=1)
    {
        dist_bck[i][i] = 0;
        for(ll j=i+1;j<=n;j+=1)
        {
            ll local_d = (ll)rand() % (ll)20 + 1;
            if(rand()%10 <= 3) local_d = -1;
            dist_bck[i][j] = dist_bck[j][i] = local_d;
        }
    }

    ll ans,ac_ans;

    for(ll k=1;k<=(n * (n-1) / 2);k+=1)
    {
        if(check(1e9 + 100) > k)
        {
            ans = 0;
        }

        else if(check(1e9 + 100) == k)
        {
            ans = -1;
        }

        else
        {
            ll l = search(k+1), r = search(k);
            ans = r - l;
        }

        // AC
        ac::N = n, ac::P = p, ac::K = k;
        for(ll i=1;i<=n;i+=1)
        {
            for(ll j=1;j<=n;j+=1) ac::A[i][j] = dist_bck[i][j];
        }

        ac_ans = ac::main();

        if(ac_ans == ans) ; // cout << "AC" << endl;
        else {
            cout << "WA: " << ans << " AC: " << ac_ans << endl;
            cout << n << " " << p << " " << k << endl;
            for(ll i=1;i<=n;i+=1)
            {
                for(ll j=1;j<=n;j+=1) cout << dist_bck[i][j] << " "; cout << endl;
            }
        }
    }

    return 0;
}

int32_t main_bck() {
    cin >> n >> p >> k; // 正好有K组 P是距离限制

    for(ll i=1;i<=n;i+=1)
    {
        for(ll j=1;j<=n;j+=1)
        {
            cin >> dist_bck[i][j];
        }
    }

    if(check(1e9 + 100) > k) {
        cout << 0 << endl;
        return 0;
    }

    if(check(1e9 + 100) == k)
    {
        cout << "Infinity" << endl;
        return 0;
    }

    ll l = search(k+1), r = search(k);
    /*
    while(check(l) > k) l += 1;
    while(l-1 >= 0 && check(l-1) <= k) l -= 1;

    while(check(r) < k) r -= 1;
    while(check(r+1) >= k) r += 1;
    */
    /*
    if(l > 1e9 + 1)
    {
        cout << 0 << endl;
    }else if(r > 1e9 + 1)
    {
        cout << "Infinity" << endl;
    }else cout << r - l << endl;
    */
    cout << r - l << endl;

    return 0;
}


int main()
{
    return main_bck();

    srand((unsigned)time(nullptr));
    ll t = 10000;
    while(t--) main_test();
    return 0;
}