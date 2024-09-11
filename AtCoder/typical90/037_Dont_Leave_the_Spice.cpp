#include <algorithm>
#include <iostream>
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
const ll maxn = 510;
const ll maxw = 1e4 + 10;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

ll w,n,l[maxn],r[maxn],v[maxn],dp[maxw];

namespace g
{
    const ll maxn = maxw;

    struct SGTree
    {
        ll N,Record[maxn];
        ll mmax[maxn*4],mmin[maxn*4],ssum[maxn*4];
        ll lazy[maxn*4],Left,Right,Value;
        void build(ll node,ll l,ll r)
        {
            lazy[node]=0;
            if(l==r)
            {
                mmax[node]=mmin[node]=ssum[node]=Record[l];
                return;
            }
            ll mid=(l+r)>>1;
            build(node<<1,l,mid);
            build((node<<1)+1,mid+1,r);
            ssum[node]=ssum[node<<1]+ssum[(node<<1)+1];
            mmax[node]=max(mmax[node<<1],mmax[(node<<1)+1]);
            mmin[node]=min(mmin[node<<1],mmin[(node<<1)+1]);
        }
        void pushDown(ll node,ll l,ll r)
        {
            ll mid=(l+r)>>1;
            lazy[node<<1]=lazy[(node<<1)+1]=lazy[node];
            ssum[node<<1]=lazy[node]*(mid-l+1);
            ssum[(node<<1)+1]=lazy[node]*(r-mid);
            mmax[node<<1]=mmax[(node<<1)+1]=lazy[node];
            mmin[node<<1]=mmin[(node<<1)+1]=lazy[node];
            lazy[node]=0;
        }
        void Update(ll node,ll l,ll r)
        {
            if(Left<=l&&r<=Right)
            {
                lazy[node]=Value;
                ssum[node]=Value*(r-l+1);
                mmax[node]=mmin[node]=Value;
                return;
            }
            ll mid=(l+r)>>1;
            if(lazy[node]) pushDown(node,l,r);
            if(Left<=mid) Update(node<<1,l,mid);
            if(Right>mid) Update((node<<1)+1,mid+1,r);
            ssum[node]=ssum[node<<1]+ssum[(node<<1)+1];
            mmax[node]=max(mmax[node<<1],mmax[(node<<1)+1]);
            mmin[node]=min(mmin[node<<1],mmin[(node<<1)+1]);
        }
        ll AskMax(ll node,ll l,ll r)
        {
            if(Left<=l&&r<=Right) return mmax[node];
            if(lazy[node]) pushDown(node,l,r);
            ll mid=(l+r)>>1;
            bool exl=(Left<=mid),exr=(Right>mid);
            if(exl&&exr) return max(AskMax(node<<1,l,mid),AskMax((node<<1)+1,mid+1,r));
            if(exl) return AskMax(node<<1,l,mid); return AskMax((node<<1)+1,mid+1,r);
        }
        ll AskMin(ll node,ll l,ll r)
        {
            if(Left<=l&&r<=Right) return mmin[node];
            if(lazy[node]) pushDown(node,l,r);
            ll mid=(l+r)>>1;
            bool exl=(Left<=mid),exr=(Right>mid);
            if(exl&&exr) return min(AskMin(node<<1,l,mid),AskMin((node<<1)+1,mid+1,r));
            if(exl) return AskMin(node<<1,l,mid); return AskMin((node<<1)+1,mid+1,r);
        }
        ll AskSum(ll node,ll l,ll r)
        {
            if(Left<=l&&r<=Right) return ssum[node];
            if(lazy[node]) pushDown(node,l,r);
            ll mid=(l+r)>>1,ans=0;
            if(Left<=mid) ans+=AskSum(node<<1,l,mid);
            if(Right>mid) ans+=AskSum((node<<1)+1,mid+1,r);
            return ans;
        }
    }ac;
}

int main()
{
    cin >> w >> n;
    for(ll i=1;i<=n;i+=1)
    {
        cin >> l[i] >> r[i] >> v[i];
    }

    // 关键
    // 初始值是0还是-inf很重要，表示两种不同的逻辑
    // 0: dp[5] = 0，表示上限是5，w在5以内，v能取得的最大值是多少，也就是说w不够没关系，可以不取，可以省下空间，所以随着w增大v一定增大
    // -inf：dp[5] = -inf，表示w一定要刚好取到5的时候v的最大值，dp[5]不一定大于dp[0...4]，因为w=5可能就是取不到，那么v自然也就是-inf
    // 这很重要，一定要多思考一下
    for(ll i=1;i<=w;i+=1) dp[i] = -1e14, g::ac.Record[i] = -1e14;
    dp[0] = 0, g::ac.Record[0] = 0;

    g::ac.build(1,0,w);

    for(ll i=1;i<=n;i+=1)
    {
        for(ll j=w;j>=l[i];j-=1)
        {
            // j - [l,r] = [j-r, j-l]
            // key
            ll sl = max((ll)0,j-r[i]), sr = j-l[i];
            g::ac.Left = sl, g::ac.Right = sr;
            dp[j] = max(dp[j], (ll)g::ac.AskMax(1,0,w) + v[i]);
            g::ac.Left = j, g::ac.Right = j, g::ac.Value = dp[j];
            g::ac.Update(1,0,w);
        }
    }

    cout << ((dp[w] > 0) ? dp[w] : -1) << endl;
    return 0;
}