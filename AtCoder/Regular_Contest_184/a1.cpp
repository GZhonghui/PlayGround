// 第一种官方解法
// https://atcoder.jp/contests/arc184/editorial/11003

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

int n,m,q;
set<int> T,F;

inline int ask(int i, int j)
{
    int res;
    cout << "? " << i << " " << j << endl;
    cin >> res;
    return res;
}

int main()
{
    set<int> x,y;

    cin >> n >> m >> q;
    for(int i=1;i<=n;i+=1)
    {
        if(x.empty()) x.insert(i);
        else {
            if(!ask(*(x.begin()),i)) x.insert(i);
            else y.insert(i);

            if(x.size() > 10) {
                T.merge(x); F.merge(y);
            } else if(y.size() > 10)
            {
                T.merge(y); F.merge(x);
            }
        }
    }

    if(!x.empty()) {
        if(!ask(*T.begin(),*x.begin())) {
            T.merge(x); F.merge(y);
        } else {
            T.merge(y); F.merge(x);
        }
    }

    cout << "!";
    for(auto i=F.begin();i!=F.end();i++) {
        cout << " " << *i;
    }
    cout << endl;

    return 0;
}