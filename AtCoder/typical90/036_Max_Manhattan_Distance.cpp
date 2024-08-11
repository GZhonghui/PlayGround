#include<algorithm>
#include<cstdio>
#include<cstdint>

typedef int64_t ll;

const ll maxn = 100000 + 1;
const ll maxc = 1000000000 + 1;

ll x[maxn],y[maxn],n,q,c_x[4],c_y[4],max_distance[4] = {0,0,0,0};

inline ll distance(ll x1,ll y1,ll x2,ll y2)
{
    return std::abs(x1-x2) + std::abs(y1-y2);
}

inline void update(ll x,ll y,ll cx,ll cy,int index)
{
    // printf("distance of (%lld,%lld) and (%lld,%lld) is %lld\n",x,y,cx,cy,distance(x,y,cx,cy));
    if(distance(x,y,cx,cy) > max_distance[index])
    {
        max_distance[index] = distance(x,y,cx,cy);
        c_x[index] = x;
        c_y[index] = y;
    }
}

int main()
{
    scanf("%lld %lld",&n,&q);
    for(int i=1;i<=n;i+=1)
    {
        scanf("%lld %lld",&x[i],&y[i]);

        update(x[i],y[i],-maxc,-maxc,0);
        update(x[i],y[i], maxc,-maxc,1);
        update(x[i],y[i],-maxc, maxc,2);
        update(x[i],y[i], maxc, maxc,3);
        
    }
    
    for(int i=0;i<4;i+=1)
    {
        // printf("%lld %lld\n",c_x[i],c_y[i]);
    }

    while(q--)
    {
        int ask;
        scanf("%d",&ask);

        ll ans = 0;
        for(int i=0;i<4;i+=1)
            ans = std::max(ans, distance(x[ask],y[ask],c_x[i],c_y[i]));
        printf("%lld\n",ans);
    }

    return 0;
}