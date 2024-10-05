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

string a,b;

int main()
{
    cin >> a >> b;
    if(a == b) cout << 0 << endl;
    else {
        ll ans = 0;
        for(ll i=0;i<min(a.length(),b.length());i+=1) {
            if(a[i] == b[i]) ans += 1;
            else break;
        }
        cout << ans + 1 << endl;
    }
    return 0;
}