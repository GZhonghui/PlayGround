#include<algorithm>
#include<cmath>
#include<cstdio>

// 这题可能是蒙对的

int n, k;
int fill_length, fill_number;

inline int set_bit(int data, int index)
{
    data = data | (1<<(index-1));
    return data;
}

inline int clear_bit(int data, int index)
{
    data = set_bit(data, index);
    data = data - (1<<(index-1));
    return data;
}

inline int get(int index)
{
    int ans = 0;
    for(int i=1;i<=k;i+=1)
    {
        // ans += 1<<i;
        ans = set_bit(ans,i);
    }

    if(index == 1)
    {
        
    }else if(index == 2)
    {
        // ans -= 1<<(k-2);
        ans = clear_bit(ans, k-1);
    }else if(fill_length <= k-2)
    {
        // index -= 2;
        
        // fill
        for(int i=1;i<=fill_length;i+=1)
        {
            ans = clear_bit(ans, k-i);
        }
        ans = ans | (fill_number << (k-1-fill_length));
        ans = clear_bit(ans, k-1-fill_length);

        // after fill
        fill_number += 1;
        if(fill_number >= (1<<fill_length))
        {
            fill_length += 1;
            fill_number = 0;
        }
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);

        fill_length = 1;
        fill_number = 0;

        for(int i=1;i<=n;i+=1)
        {
            printf("%d ",get(i));
        }
        puts("");
    }
    return 0;
}