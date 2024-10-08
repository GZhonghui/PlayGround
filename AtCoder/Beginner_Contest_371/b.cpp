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

ll n,m;
unordered_set<ll> counter;

int main()
{
    cin >> n >> m;
    while(m--)
    {
        ll a;
        char b;
        cin >> a >> b;
        if(b == 'F')
        {
            cout << "No" << endl;
        }else if(b == 'M')
        {
            if(!counter.count(a))
            {
                cout << "Yes" << endl;
                counter.insert(a);
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }


    return 0;
}