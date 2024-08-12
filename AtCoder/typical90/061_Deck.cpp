#include<algorithm>
#include<cstdio>

const int maxq=1e5+1;

int data[maxq<<1],l=maxq+1,r=maxq;

int main()
{
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int type,x;
        scanf("%d %d",&type,&x);
        if(type == 1)
        {
            l -= 1;
            data[l] = x;
        }else if(type == 2)
        {
            r += 1;
            data[r] = x;            
        }else if(type == 3)
        {
            printf("%d\n",data[l + x - 1]);
        }
    }
    return 0;
}