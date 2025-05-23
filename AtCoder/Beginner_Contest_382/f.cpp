// https://vjudge.net/problem/HDU-1698
// https://acm.hdu.edu.cn/showproblem.php?pid=1698 Just a Hook

// 比较全面的一个模板。修改支持：修改为定值；查询支持：Min、Max、Sum

#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=2e5+10;
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

struct node {
    int id,r,c,l;

    bool operator<(const node &other) const {
        return r > other.r;
    }
}nodes[maxn];

int h,w,n,ans[maxn];

int main()
{
    cin >> h >> w >> n;
    for(int i=1;i<=n;i+=1) {
        static int r,c,l; cin >> r >> c >> l;
        nodes[i] = (node){i,r,c,l};
    }
    sort(nodes+1,nodes+1+n);

    ac.N = w;
    for(int i=1;i<=ac.N;i+=1) ac.Record[i] = 0;
    ac.build(1,1,ac.N);

    for(int i=1;i<=n;i+=1) {
        const node &now = nodes[i];
        ac.Left = now.c, ac.Right = now.c + now.l - 1;
        int down = ac.AskMax(1,1,ac.N);
        ac.Value = ans[now.id] = down + 1;
        ac.Update(1,1,ac.N);
    }

    for(int i=1;i<=n;i+=1) cout << h - ans[i] + 1 << endl;
    
    return 0;
}