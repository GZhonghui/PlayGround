#include<algorithm>
#include<cstdio>
#include<cmath>

int main()
{
    char s1[8],s2[8];
    scanf("%s",s1);
    scanf("%s",s2);
    int x1=abs(s1[0]-s1[1]);
    int x2=abs(s2[0]-s2[1]);
    
    x1=std::min(x1,5-x1);
    x2=std::min(x2,5-x2);

    printf("%s\n",x1==x2?"Yes":"No");

    return 0;
}