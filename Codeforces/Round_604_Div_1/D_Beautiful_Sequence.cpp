#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a,b,c,d;
int main()
{
    scanf("%d %d %d %d",&a,&b,&c,&d);
    if(a>b||d>c)
    {
        if(a-b==1&&c==0&&d==0)
        {
            puts("YES");
            for(int i=1;i<=b;i+=1) printf("0 1 ");
            printf("0\n");
        }else if(d-c==1&&a==0&&b==0)
        {
            puts("YES");
            for(int i=1;i<=c;i+=1) printf("3 2 ");
            printf("3\n");
        }
        else puts("NO");
        return 0;
    }
    int l(b-a),r(c-d);
    if(l==r)
    {
        puts("YES");
        for(int i=1;i<=a;i+=1) printf("0 1 ");
        for(int i=1;i<=l;i+=1) printf("2 1 ");
        for(int i=1;i<=d;i+=1) printf("2 3 ");
        puts("");
    }else if(l-1==r)
    {
        puts("YES");
        printf("1 ");
        for(int i=1;i<=a;i+=1) printf("0 1 ");
        for(int i=1;i<=r;i+=1) printf("2 1 ");
        for(int i=1;i<=d;i+=1) printf("2 3 ");
        puts("");
    }else if(l==r-1)
    {
        puts("YES");
        for(int i=1;i<=a;i+=1) printf("0 1 ");
        for(int i=1;i<=l;i+=1) printf("2 1 ");
        for(int i=1;i<=d;i+=1) printf("2 3 ");
        printf("2\n");
    }else puts("NO");
    return 0;
}