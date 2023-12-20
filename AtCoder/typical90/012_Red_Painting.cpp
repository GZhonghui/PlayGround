#include<algorithm>
#include<cstdint>
#include<cstdio>
#include<unordered_set>

const int mmax=2000*2000+10;

const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};

int h,w,q;

inline int id(int x,int y)
{
    if(x<1||x>h||y<1||y>w) return 0;
    return (x-1)*w+y;
}

int fa[mmax];

int root(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=root(fa[x]);
}

void link(int x,int y)
{
    int xfa=root(x),yfa=root(y);
    fa[xfa]=yfa;
}

std::unordered_set<int> red;

int main()
{
    for(int i=0;i<mmax;i+=1) fa[i]=i;

    scanf("%d %d %d",&h,&w,&q);
    while(q--)
    {
        int t;scanf("%d",&t);
        if(t==1)
        {
            int x,y;scanf("%d %d",&x,&y);
            int _id=id(x,y);
            red.insert(_id);
            for(int i=0;i<4;i+=1)
            {
                int xx=x+dx[i],yy=y+dy[i];
                int _iid=id(xx,yy);
                if(_iid&&red.count(_iid)) link(_iid,_id);
            }

        }else if(t==2)
        {
            int x1,y1,x2,y2;scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
            int id1=id(x1,y1),id2=id(x2,y2);
            if(red.count(id1)&&red.count(id2)&&(root(id1)==root(id2)))
            {
                puts("Yes");
            }else puts("No");
        }
    }

    return 0;
}