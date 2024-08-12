#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>

typedef double number;
const int maxn=2e3+1;
const number pi = std::acos(-1.0);

// struct point;
// number angle(point pa, point pb, point pc);

struct point
{
    number x,y,angle;

    point() = default;
    point(number x,number y):x(x),y(y)
    {
        angle = atan2(y,x) * 180.0 / pi; // 有一定的精度误差
        /*
        point _a,_b,_c;
        _a.x = x;
        _a.y = y;
        _b.x = 0;
        _b.y = 0;
        _c.x = 1;
        _c.y = 0;
        angle = ::angle(_a,_b,_c);
        */
    }

    inline bool operator<(const point& other) const
    {
        return angle < other.angle;
    }

    inline void print()
    {
        printf("Point: (%lf, %lf), Angle = %lf\n",x,y,angle);
    }
}pa,pb,pc;

class polar_angle_sort
{
protected:
    std::vector<point> points; // 其实根据需求，不一定需要存储这些点的原始数据吧，可能存个角度就可以了

public:
    void init()
    {
        points.clear();
    }

    void add_point(point p)
    {
        points.push_back(p);
    }

    void sort()
    {
        std::sort(points.begin(),points.end());
    }

    std::vector<point>* data()
    {
        return &points;
    }
}solver;

// AI 测试用代码
number angle(point pa, point pb, point pc) {
    // 向量 ab 和向量 cb
    number ab_x = pa.x - pb.x;
    number ab_y = pa.y - pb.y;
    number cb_x = pc.x - pb.x;
    number cb_y = pc.y - pb.y;
    
    // 点积
    number dot_product = ab_x * cb_x + ab_y * cb_y;
    
    // 向量的模
    number ab_len = std::sqrt(ab_x * ab_x + ab_y * ab_y);
    number cb_len = std::sqrt(cb_x * cb_x + cb_y * cb_y);
    
    // 计算余弦值
    number cos_theta = dot_product / (ab_len * cb_len);
    
    // 计算角度（弧度）
    number angle_radians = std::acos(cos_theta);
    
    // 转换为角度
    number angle_degrees = angle_radians * 180.0 / pi;
    
    return angle_degrees;
}

std::vector<point> original_points;

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i+=1)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        original_points.push_back(point((number)x,(number)y));
    }

    number ans = 0;
    for(int i=0;i<n;i+=1)
    {
        const point& center = original_points[i];
        solver.init();
        for(int j=0;j<n;j+=1)
        {
            if(i==j) continue;

            const point& target = original_points[j];
            solver.add_point(point(target.x-center.x,target.y-center.y));
        }

        solver.sort();

        std::vector<point> *data = solver.data();
        int l = 0, r = 0;
        number k = 0; // 注意，一开始这里想错了
        while(l < data->size())
        {
            number diff = 0;
            while(r < data->size() && (diff = (*data)[r].angle + k - (*data)[l].angle) <= 180.0)
            {
                // ans = std::max(ans, diff);
                if(diff > ans)
                {
                    ans = diff;
                    pa = point(center.x+(*data)[r].x,center.y+(*data)[r].y);
                    pb = center;
                    pc = point(center.x+(*data)[l].x,center.y+(*data)[l].y);
                }
                r += 1;
                if(r >= data->size()) r -= data->size(), k += 360;
            }
            l += 1;
        }
    }

    printf("%.10lf\n",ans);
    // pa.print();
    // pb.print();
    // pc.print();

    // 暴力计算答案
    /*
    number real_ans = 0;
    point rpa,rpb,rpc;
    for(int i=0;i<n;i+=1)
    {
        for(int j=0;j<n;j+=1)
        {
            for(int k=0;k<n;k+=1)
            {
                if(i==j || j==k || k==i) continue;
                number result = angle(original_points[i],original_points[j],original_points[k]);
                if(result > real_ans)
                {
                    real_ans = result;
                    rpa=original_points[i];
                    rpb=original_points[j];
                    rpc=original_points[k];
                }
            }
        }
    }
    printf("%.10lf\n",real_ans);
    rpa.print();
    rpb.print();
    rpc.print();
    */

    return 0;
}