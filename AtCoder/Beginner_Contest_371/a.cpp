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

int main()
{
    char ab,ac,bc;
    cin >> ab >> ac >> bc;
    if(ab == '<')
    { // a < b
        if(ac == '<')
        {
            // a < c
            if(bc == '<')
            {
                cout << "B" << endl;
            }else
            {
                cout << "C" << endl;
            }
        }else
        {
            // a > c
            cout << "A" << endl;
        }

    }else
    {
        // a > b
        if(ac == '<')
        {
            // a < c
            cout << "A" << endl;
        }else
        {
            // a > c
            if(bc == '<')
            {
                cout << "C" << endl;
            }else
            {
                cout << "B" << endl;
            }
        }
    }
    return 0;
}