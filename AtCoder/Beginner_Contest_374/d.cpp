#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <cmath>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 10;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

class Vector3f
{
public:
    double x,y,z;
public:
    Vector3f():x(0),y(0),z(0){}
    Vector3f(double k):x(k),y(k),z(k){}
    Vector3f(double x,double y,double z):x(x),y(y),z(z){}
    ~Vector3f()=default;
public:
    Vector3f operator+(const Vector3f &rhx) const
    {
        return Vector3f(x+rhx.x,y+rhx.y,z+rhx.z);
    }
    Vector3f operator-(const Vector3f &rhx) const
    {
        return Vector3f(x-rhx.x,y-rhx.y,z-rhx.z);
    }
    Vector3f operator*(double k) const
    {
        return Vector3f(x*k,y*k,z*k);
    }
    Vector3f operator/(double k) const
    {
        return Vector3f(x/k,y/k,z/k);
    }
    double operator[](unsigned int k) const
    {
        switch(k)
        {
            case 1:return x;
            case 2:return y;
            case 3:return z;
        }
        return 0;
    }
    bool operator<(const Vector3f &rhx) const
    {
        for(unsigned int i=1;i<=3;i+=1)
        {
            if(operator[](i)>rhx[i])
            {
                return false;
            }
        }
        return true;
    }
public:
    Vector3f hadamard_product(const Vector3f &rhx) const
    {
        return Vector3f(x*rhx.x,y*rhx.y,z*rhx.z);
    }
    Vector3f cross_product(const Vector3f &rhx) const
    {
        return Vector3f(y*rhx.z-rhx.y*z,rhx.x*z-x*rhx.z,x*rhx.y-rhx.x*y);
    }
    double dot_product(const Vector3f &rhx) const
    {
        return x*rhx.x+y*rhx.y+z*rhx.z;
    }
public:
    Vector3f opposite() const
    {
        return Vector3f(-x,-y,-z);
    }
    double normal() const
    {
        return std::sqrt(x*x+y*y+z*z);
    }
    Vector3f normalized() const
    {
        return operator/(normal());
    }
    double distance(const Vector3f &rhx) const
    {
        return operator-(rhx).normal();
    }
    Vector3f middle(const Vector3f &rhx) const
    {
        return operator+(rhx).normalized();
    }
public:
    void normalize()
    {
        (*this)=normalized();
    }
    void limit(double l,double r)
    {
        if(l>r) return;
        
        x=max(l,min(r,x));
        y=max(l,min(r,y));
        z=max(l,min(r,z));
    }
};

typedef Vector3f Color;
typedef Vector3f Point;
typedef Vector3f Direction;

ll n,p[maxn];
f s,t;
Point u[maxn],v[maxn];

int main()
{
    cin >> n >> s >> t;
    for(ll i=1;i<=n;i+=1) {
        cin >> u[i].x >> u[i].y;
        cin >> v[i].x >> v[i].y;
        p[i] = i;
    }

    f ans = 1e18;
    do {
        // p
        for(ll i=0;i<(1<<n);i+=1)
        {
            Point start;
            f local_ans = 0;

            for(ll j=1;j<=n;j+=1)
            {
                local_ans += start.distance((i & (1<<(j-1))) ? u[p[j]] : v[p[j]]) / s;
                local_ans += u[p[j]].distance(v[p[j]]) / t;
                start = (i & (1<<(j-1))) ? v[p[j]] : u[p[j]];
            }

            ans = min(ans, local_ans);
        }

    } while(next_permutation(p+1,p+1+n));

    cout << fixed << setprecision(10) << ans << endl;
    

    return 0;
}