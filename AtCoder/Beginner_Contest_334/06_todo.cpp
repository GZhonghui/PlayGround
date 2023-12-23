#include<algorithm>
#include<cstdio>
#include<cmath>

const int maxn=2e5+10;

struct Point
{
    double x,y;

    public:
    Point(double x=0,double y=0):x(x),y(y){}
};

double dis(const Point& a,const Point& b)
{
    double dx=a.x-b.x,dy=a.y-b.y;
    return std::sqrt(dx*dx+dy*dy);
}

int n,k;
Point points[maxn],start;

double dp[maxn];

int main()
{
    int x,y;
    scanf("%d %d",&n,&k);
    scanf("%d %d",&x,&y);
    start.x=(double)x;
    start.y=(double)y;

    for(int i=1;i<=n;i+=1)
    {
        scanf("%d %d",&x,&y);
        points[i].x=(double)x;
        points[i].y=(double)y;
    }

    double sum=0;
    for(int i=2;i<=n;i+=1)
    {
        sum+=dis(points[i],points[i-1]);
    }
    sum+=dis(start,points[1]);
    sum+=dis(start,points[n]);

    double min_del=0;

    

    for(int i=2;i<=n;i+=1)
    {
        
    }

    printf("%lf\n",sum-min_del);

    return 0;
}