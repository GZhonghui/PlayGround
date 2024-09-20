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
const ll maxn = 1e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

const ll delta = 100;
ll link[(ll)(maxn / delta + 10)][(ll)(maxn / delta + 10)];

ll fa[maxn];
ll n,q,t,x,y,v,sum_with_before[maxn];

// 这个并查集是很容易想到的
ll root(ll x)
{
    if(fa[x] == x) return x;
    return fa[x] = root(fa[x]);
}

void make_union(ll x, ll y)
{
    fa[x] = root(y);
}

bool same_union(ll x, ll y)
{
    return root(x) == root(y);
}

// 本来以为会TLE，但是AC了
// 这里记录以下原本的想法
// 以100为单位，预计算“关系”，比如link[1][2]=5表示a[100] + 5 == a[200]
// 以这种分块的方式加速计算
// 如果数据给出的询问是下标距离很远的情况的话，就可以利用link数组加速
// link数据的计算也不会太久
inline void repair_link()
{

}

ll calc_direct(ll idx, ll value, ll target)
{
    while(idx < target)
    {
        value = sum_with_before[idx + 1] - value;
        idx += 1;
    }
    while(idx > target)
    {
        value = sum_with_before[idx] - value;
        idx -= 1;
    }
    return value;
}

int main()
{
    memset(link,-1,sizeof(link));
    memset(sum_with_before,0,sizeof(sum_with_before));
    for(ll i=0;i<maxn;i+=1) fa[i] = i;

    cin >> n >> q;
    while(q--)
    {
        cin >> t >> x >> y >> v;
        if(t)
        {
            // ask a[x] == v
            if(same_union(x,y))
            {
                cout << calc_direct(x,v,y) << endl;
            }else
            {
                cout << "Ambiguous" << endl;
            }
        }else
        {
            // set x+1 == y
            sum_with_before[y] = v;
            make_union(x,y);
        }
    }
    return 0;
}