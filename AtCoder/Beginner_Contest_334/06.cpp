#include<algorithm>
#include<cstdio>
#include<cmath>
#include<deque>

template<class T>
class sliding_window_min_max
{
protected:
    struct node
    {
        int id;
        T value;
    };

protected:
    int window_size = 1, now_index = 0;
    std::deque<node> min_q,max_q;

public:
    void init(int window_size)
    {
        this->window_size = window_size;
        now_index = 0;
        min_q.clear();
        max_q.clear();
    }

    void add(T new_number)
    {
        node new_node = (node){++now_index,new_number};

        if(min_q.size() && new_node.id - min_q.front().id >= window_size)
        {
            min_q.pop_front();
        }
        while(min_q.size() && min_q.back().value >= new_node.value)
        {
            min_q.pop_back();
        }
        min_q.push_back(new_node);

        if(max_q.size() && new_node.id - max_q.front().id >= window_size)
        {
            max_q.pop_front();
        }
        while(max_q.size() && max_q.back().value <= new_node.value)
        {
            max_q.pop_back();
        }
        max_q.push_back(new_node);
    }

    T min_in_last_window()
    {
        if(min_q.size())
        {
            return min_q.front().value;
        }
        return (T)0;
    }

    T max_in_last_window()
    {
        if(max_q.size())
        {
            return max_q.front().value;
        }
        return (T)0;
    }
};

sliding_window_min_max<double> solver;

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

double select_from[maxn], dp[maxn];

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

    // start -> 1 -> N -> start
    double sum=0;
    for(int i=2;i<=n;i+=1)
    {
        sum+=dis(points[i],points[i-1]);
    }
    sum+=dis(start,points[1]);
    sum+=dis(start,points[n]);

    // 这里选择的是什么？是什么时候回家，N个目标点，有N-1个间隔需要选择，加上头尾的话（便于计算）是N+1
    // 不回家是i->j的距离，回家的话是i->s + s->j的距离，一定是增加了，dp是计算怎么选择的增加量最小
    // 关键：dp[i]表示的是“在第i个间隔回家的最小增加量”，“回家”是确定的
    // 所以，dp[i]依赖于i前面k个状态
    // select_from: [0,N] (length = N+1)
    select_from[0] = select_from[n] = 0;
    for(int i=1;i<n;i+=1)
    {
        select_from[i] = dis(start, points[i]) + dis(start, points[i+1]) - dis(points[i], points[i+1]);
    }

    // dp
    dp[0] = select_from[0];
    solver.init(k);
    solver.add(dp[0]);
    for(int i=1;i<=n;i+=1)
    {
        dp[i] = solver.min_in_last_window() + select_from[i];
        solver.add(dp[i]);
    }

    printf("%.10lf\n",dp[n] + sum);

    return 0;
}