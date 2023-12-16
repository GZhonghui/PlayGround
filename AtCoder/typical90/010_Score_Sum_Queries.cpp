#include<algorithm>
#include<cstdio>

const int maxn=100000+10;
int n,sum1[maxn],sum12[maxn];

int main()
{
    scanf("%d",&n);
    sum1[0]=sum12[0]=0;
    for(int i=1,_class,_score;i<=n;i+=1)
    {
        scanf("%d %d",&_class,&_score);
        sum12[i]=sum12[i-1]+_score;
        sum1[i] = (_class==1) ? sum1[i-1]+_score : sum1[i-1];
    }

    int q,l,r;scanf("%d",&q);
    while(q--)
    {
        scanf("%d %d",&l,&r);
        printf("%d %d\n",sum1[r]-sum1[l-1],sum12[r]-sum12[l-1]-sum1[r]+sum1[l-1]);
    }

    return 0;
}