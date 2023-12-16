#include<algorithm>
#include<cstdio>

int main()
{
    int n;
    scanf("%d",&n);

    long long nums[4]={1,1,1,1};
    for(int i=1;i<n;i+=1)
    {
        /*
        nums[nums[0]]=nums[nums[0]]*10+1;
        nums[0]=nums[0]+1;
        nums[0]=(nums[0]==4)?1:nums[0];
        */

       if(nums[1]==nums[2]&&nums[2]==nums[3])
       {
            nums[1]=nums[1]*10+1;
            nums[2]=nums[3]=1;
       }else if(nums[2]==nums[3])
       {
            nums[2]=nums[2]*10+1;
            nums[3]=1;
       }else
       {
            nums[3]=nums[3]*10+1;
       }

    }

    printf("%lld\n",nums[1]+nums[2]+nums[3]);

    return 0;
}