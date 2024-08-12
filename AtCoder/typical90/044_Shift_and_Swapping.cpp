#include<algorithm>
#include<cstdio>

const int maxn=2e5+1;

int data[maxn],n,q,offset=0;

inline int* get(int index)
{
    return data + (index + offset - 1 + n) % n + 1;
}

int main()
{
    scanf("%d %d",&n,&q);
    for(int i=1;i<=n;i+=1)
    {
        scanf("%d",data+i);
    }
    while(q--)
    {
        int type,x,y;
        scanf("%d %d %d",&type,&x,&y);
        if(type == 1)
        {
            int *_x = get(x), *_y = get(y);
            int _value = *_x;
            *_x = *_y;
            *_y = _value;
        }else if(type == 2)
        {
            offset -= 1;
            if(offset <= -n) offset += n;
        }else if(type == 3)
        {
            printf("%d\n",*get(x));
        }

        for(int i=1;i<=n;i+=1)
        {
            // printf("%d%c",*get(i),i==n?'\n':' ');
        }
    }
    return 0;
}