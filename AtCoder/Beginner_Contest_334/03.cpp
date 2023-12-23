#include<algorithm>
#include<cstdio>
#include<cstdint>
#include<cmath>

const int maxn=2e5+10;
int n,k;
int data[maxn],l[maxn],r[maxn];

int main()
{
    scanf("%d %d",&n,&k);


    for(int i=1;i<=k;i+=1)
    {
        scanf("%d",data+i);
    }

    int64_t ans=0;
    if(k%2)
    {
        ans=1e18;
        l[0]=0;
        for(int i=2;i<=k;i+=2)
        {
            l[i]=l[i-2]+data[i]-data[i-1];
        }
        r[k+1]=0;
        for(int i=k-1;i>=1;i-=2)
        {
            r[i]=r[i+2]+data[i+1]-data[i];
        }
        for(int i=1;i<=k;i+=2)
        {
            ans=std::min(ans,(int64_t)(l[i-1]+r[i+1]));
        }
    }else
    {
        for(int i=1;i<=k;i+=2)
        {
            ans+=data[i+1]-data[i];
        }
    }
    printf("%lld\n",ans);

    return 0;
}