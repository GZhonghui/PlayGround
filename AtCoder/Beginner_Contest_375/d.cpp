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
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

unordered_map<char,ll> cnt;
unordered_map<char,ll> last;

char s[maxn];
ll mem[maxn];

int main()
{
    cin >> (s+1);

    ll len = strlen(s+1), ans = 0;
    for(ll i=1;i<=len;i+=1) {
        if(!cnt.count(s[i])) cnt[s[i]] = 0;

        if(cnt[s[i]] == 0) {
            mem[i] = 0;
        } else {
            mem[i] = mem[last[s[i]]];
            mem[i] += (cnt[s[i]] - 1) * (i - last[s[i]]);
            mem[i] += i - last[s[i]] - 1;
            ans += mem[i];
        }

        cnt[s[i]] += 1;
        last[s[i]] = i;

        // cout << i << " " << mem[i] << endl;
    }
    cout << ans << endl;

    return 0;
}