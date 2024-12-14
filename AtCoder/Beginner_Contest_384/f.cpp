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
#define pb push_back
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef uint64_t ull;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 2e5 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 8;
const f pi = acos(-1.0);
const f eps = 1e-6;

template<class T> struct point {
    T x,y;

    T dis2(const point &r) {
        T dx = x - r.x, dy = y - r.y;
        return dx * dx + dy * dy;
    }
};

typedef point<ll> pl;
typedef point<f> pf;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

ll n,a[maxn];

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=1024;
struct LowBitTree
{   
    // 树状数组求和的区间包括0的话，会出一点小问题，因为lowbit(0) = 0
    // 如果需要包括0的话，可以在Add和Sum的函数内部统一做一个偏移
    int C[maxn],n;
    void init(int n=maxn-1) // n为支持的数据规模，支持的下标范围是[1,n]
    {
        this->n=n;
        memset(C,0,sizeof(int)*maxn);
    }
    int lowbit(int x){ return x&(-x); }
    int Sum(int pos) // 计算Sum[1,pos]
    {
        int ans=0;
        for(int i=pos;i;i-=lowbit(i)) ans+=C[i];
        return ans;
    }
    void Add(int pos,int value) // 在pos的位置增加value
    {
        for(int i=pos;i<=n;i+=lowbit(i)) C[i]+=value;
    }
};

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    rep(i,1,n) cin >> a[i];




    return 0;
}