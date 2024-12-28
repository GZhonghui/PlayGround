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
typedef long double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 2e5 + 100;
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

struct node {
    ll x,y;
    char c;

    bool operator<(const node &other) const {
        if(y == other.y) return x < other.x;
        return y < other.y;
    }
};

vector<node> nodes;

ll n,m;

unordered_map<ll,ll> most_right, most_down;

// https://vjudge.net/problem/HDU-1698
// https://acm.hdu.edu.cn/showproblem.php?pid=1698 Just a Hook

// 比较全面的一个模板。修改支持：修改为定值；查询支持：Min、Max、Sum

using namespace std;
struct SGTree
{
    int N,Record[maxn];
    int mmax[maxn*4],mmin[maxn*4],ssum[maxn*4];
    int lazy[maxn*4],Left,Right,Value;
    void getRecord() // 应该是获取初始值
    {
        scanf("%d",&N);
        for(int i=1;i<=N;i++) scanf("%d",&Record[i]);
    }
    void build(int node,int l,int r)
    {
        lazy[node]=0;
        if(l==r)
        {
            mmax[node]=mmin[node]=ssum[node]=Record[l];
            return;
        }
        int mid=(l+r)>>1;
        build(node<<1,l,mid);
        build((node<<1)+1,mid+1,r);
        ssum[node]=ssum[node<<1]+ssum[(node<<1)+1];
        mmax[node]=max(mmax[node<<1],mmax[(node<<1)+1]);
        mmin[node]=min(mmin[node<<1],mmin[(node<<1)+1]);
    }
    void pushDown(int node,int l,int r)
    {
        int mid=(l+r)>>1;
        lazy[node<<1]=lazy[(node<<1)+1]=lazy[node];
        ssum[node<<1]=lazy[node]*(mid-l+1);
        ssum[(node<<1)+1]=lazy[node]*(r-mid);
        mmax[node<<1]=mmax[(node<<1)+1]=lazy[node];
        mmin[node<<1]=mmin[(node<<1)+1]=lazy[node];
        lazy[node]=0;
    }
    void Update(int node,int l,int r)
    {
        if(Left<=l&&r<=Right)
        {
            lazy[node]=Value;
            ssum[node]=Value*(r-l+1);
            mmax[node]=mmin[node]=Value;
            return;
        }
        int mid=(l+r)>>1;
        if(lazy[node]) pushDown(node,l,r);
        if(Left<=mid) Update(node<<1,l,mid);
        if(Right>mid) Update((node<<1)+1,mid+1,r);
        ssum[node]=ssum[node<<1]+ssum[(node<<1)+1];
        mmax[node]=max(mmax[node<<1],mmax[(node<<1)+1]);
        mmin[node]=min(mmin[node<<1],mmin[(node<<1)+1]);
    }
    int AskMax(int node,int l,int r)
    {
        if(Left<=l&&r<=Right) return mmax[node];
        if(lazy[node]) pushDown(node,l,r);
        int mid=(l+r)>>1;
        bool exl=(Left<=mid),exr=(Right>mid);
        if(exl&&exr) return max(AskMax(node<<1,l,mid),AskMax((node<<1)+1,mid+1,r));
        if(exl) return AskMax(node<<1,l,mid); return AskMax((node<<1)+1,mid+1,r);
    }
    int AskMin(int node,int l,int r)
    {
        if(Left<=l&&r<=Right) return mmin[node];
        if(lazy[node]) pushDown(node,l,r);
        int mid=(l+r)>>1;
        bool exl=(Left<=mid),exr=(Right>mid);
        if(exl&&exr) return min(AskMin(node<<1,l,mid),AskMin((node<<1)+1,mid+1,r));
        if(exl) return AskMin(node<<1,l,mid); return AskMin((node<<1)+1,mid+1,r);
    }
    int AskSum(int node,int l,int r)
    {
        if(Left<=l&&r<=Right) return ssum[node];
        if(lazy[node]) pushDown(node,l,r);
        int mid=(l+r)>>1,ans=0;
        if(Left<=mid) ans+=AskSum(node<<1,l,mid);
        if(Right>mid) ans+=AskSum((node<<1)+1,mid+1,r);
        return ans;
    }
}ac;
int main_test()
{
    //freopen("in.txt","r",stdin);
    int T,Case=0;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&ac.N);
        for(int i=1;i<=ac.N;i++) ac.Record[i]=1; // 手动设定初始值
        ac.build(1,1,ac.N);
        int Q;scanf("%d",&Q);
        while(Q--)
        {
            scanf("%d %d %d",&ac.Left,&ac.Right,&ac.Value); // ac.Value
            ac.Update(1,1,ac.N);
        }
        printf("Case %d: The total value of the hook is %d.\n",++Case,ac.ssum[1]);
    }
    return 0;
}

vector<node> nodes_black, nodes_white;

unordered_map<ll,ll> zip_x, unzip_x;

vector<ll> xs;
unordered_set<ll> xset;

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n >> m;

    rep(i,1,m) {
        ll x,y;
        char c;
        cin >> x >> y >> c;
        nodes.pb((node){x,y,c});

        if(!xset.count(x)) {
            xset.insert(x);
            xs.pb(x);
        }

        if(c == 'B') nodes_black.pb((node){x,y,c});
        else if(c == 'W') nodes_white.pb((node){x,y,c});
    }

    sort(xs.begin(), xs.end());

    for(ll x : xs) {
        zip_x[x] = zip_x.size() + 1;
        // unzip_x[zip_x[x]] = x;
    }

    sort(nodes_black.begin(), nodes_black.end());

    ll L = 1, R = 2e5 + 10;
    ac.N = R;
    for(int i=1;i<=ac.N;i++) ac.Record[i]=0;
    ac.build(1,1,ac.N);

    for(auto n : nodes_black) {
        ac.Left = 1;
        ac.Right = zip_x[n.x];
        ac.Value = n.y;
        ac.Update(1,1,ac.N);
    }

    for(auto n : nodes_white) {
        ll x = zip_x[n.x];

        ac.Left = x, ac.Right = x;
        ll res = ac.AskMax(1,1,ac.N);
        if(n.y <= res) {
            cout << "No" << endl;
            return 0;
        }
    }
    
    cout << "Yes" << endl;

    /*
    for(auto n : nodes) {
        ll x = n.x, y = n.y, c = n.c;

        if(c == 'B') {
            if(!most_right.count(x)) most_right[x] = 0;
            if(!most_down.count(y)) most_down[y] = 0;

            most_right[x] = max(most_right[x], y);
            most_down[y] = max(most_down[y], x);
        }
    }

    for(auto n : nodes) {
        ll x = n.x, y = n.y, c = n.c;

        if(c == 'W') {
            if(!most_right.count(x)) most_right[x] = 0;
            if(!most_down.count(y)) most_down[y] = 0;

            if(y <= most_right[x] || x <= most_down[y]) {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    

    cout << "Yes" << endl;
    */

    return 0;
}