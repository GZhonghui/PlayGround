#include<algorithm>
#include<cstdio>
#include<cstring>

const int mmax = 2010;
int h,w,data[mmax][mmax],col[mmax],row[mmax];

int main()
{
    memset(col,0,sizeof(col));
    memset(row,0,sizeof(row));

    scanf("%d %d",&h,&w);
    for(int i=1;i<=h;i+=1)
    {
        for(int j=1;j<=w;j+=1)
        {
            scanf("%d",&data[i][j]);
            row[i]+=data[i][j];
            col[j]+=data[i][j];
        }
    }

    for(int i=1;i<=h;i+=1)
    {
        for(int j=1;j<=w;j+=1)
        {
            printf("%d ",row[i]+col[j]-data[i][j]);
        }
        puts("");
    }

    return 0;
}
