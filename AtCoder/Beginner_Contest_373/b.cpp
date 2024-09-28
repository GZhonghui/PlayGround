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

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

char s[maxn];

ll get_idx(char x)
{
    for(ll i=1;i<=26;i+=1)
    {
        if(s[i] == x) return i;
    }

    return 0;
}

int main()
{
    cin >> (s+1);

    ll idx = get_idx('A'), ans = 0;
    for(char i = 'B'; i<='Z'; i+=1)
    {
        ans += abs(get_idx(i) - idx);
        idx = get_idx(i);
    }

    cout << ans << endl;
    return 0;
}