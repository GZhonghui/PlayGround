// 尝试用傅里叶变化加速乘法，没写完，后面补上

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

#define mk make_pair
#define pb push_back
#define rep(i, s, t) for (ll i = (s); i <= (t); i++)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef uint64_t ull;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
// const ll maxn = 6e5 + 8;
const ll inf = INT64_MAX;
// const f pi = acos(-1.0);
const f eps = 1e-6;

const int maxn=6e5+10;
const double pi=acos(-1.0);

class Complex
{
public:
    double re,im;
    Complex(double r=0,double i=0):re(r),im(i){}
    Complex operator+(const Complex &rhs)
    {
        return Complex(re+rhs.re,im+rhs.im);
    }
    Complex operator*(const Complex &rhs)
    {
        return Complex(re*rhs.re-im*rhs.im,re*rhs.im+im*rhs.re);
    }
    Complex operator-(const Complex &rhs)
    {
        return Complex(re-rhs.re,im-rhs.im);
    }
};

void change(Complex *y,int len)
{
    for(int i=1,j=len>>1;i+1<len;i++)
    {
        if(i<j) swap(y[i],y[j]);
        int k=len>>1;
        while(j>=k)
        {
            j-=k;
            k>>=1;
        }
        if(j<k) j+=k;
    }
}

void FFT(Complex *y,int len,int on=1)
{
    change(y,len);
    for(int i=2;i<=len;i<<=1)
    {
        Complex wn(cos(-on*2*pi/i),sin(-on*2*pi/i));
        for(int j=0;j<len;j+=i)
        {
            Complex w(1);
            int o=i>>1;
            for(int k=j;k<j+o;k++)
            {
                Complex u=y[k],t=w*y[k+o];
                y[k]=u+t;
                y[k+o]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
    {
        for(int i=0;i<len;i++)
        {
            y[i].re/=len;
        }
    }
}

int ans[maxn<<2];
Complex ComA[maxn<<2],ComB[maxn<<2];

void solve(const char *A,const char *B, ll *output)
{
    memset(ans,0,sizeof(ans));
    int lenA=strlen(A),lenB=strlen(B);
    int len=1;while(len<lenA+lenB) len<<=1;

    for(int i=0;i<lenA;i+=1) ComA[i]=Complex(A[lenA-i-1]-'0',0);
    for(int i=lenA;i<len;i+=1) ComA[i]=Complex();
    for(int i=0;i<lenB;i+=1) ComB[i]=Complex(B[lenB-i-1]-'0',0);
    for(int i=lenB;i<len;i+=1) ComB[i]=Complex();

    FFT(ComA,len,1);FFT(ComB,len,1);
    for(int i=0;i<len;i+=1) ComA[i]=ComA[i]*ComB[i];
    FFT(ComA,len,-1);

    for(int i=0;i<len;i+=1) ans[i]=int(ComA[i].re+0.5);
    for(int i=0;i<len;i+=1)
    {
        ans[i+1]+=ans[i]/10;
        ans[i]%=10;
    }

    int endPoint=lenA+lenB-1;
    while(ans[endPoint]<=0&&endPoint>=1) endPoint-=1;
    // for(int i=endPoint;i>=0;i-=1) putchar(ans[i]+'0');puts("");
    output[0] = 0;
    for(int i=endPoint;i>=0;i-=1) {
        output[0] += 1;
        output[output[0]] = ans[i];
    }

    for(ll i=1;i<=output[0];i+=1) {
        ll j = output[0] - i + 1;
        if(i < j) swap(output[i], output[j]);
    }
}

template<class T> struct point {
    T x,y;

    T dis2(const point &r) {
        T dx = x - r.x, dy = y - r.y;
        return dx * dx + dy * dy;
    }
};

typedef point<ll> pl;
typedef point<f> pf;

struct edge {
    ll to,dis;
};

vector<edge> edges;
vector<ll> g[maxn]; // id of target OR id of edge

ll n;
char s[maxn];
ll res[maxn];

char buffer1[maxn],buffer2[maxn];

ll buffer3[maxn],buffer4[maxn];

inline void add(ll a[], ll b[], ll result[]) {
    ll n = max(a[0], b[0]); // 确定结果的最大位数
    result[0] = n; // 结果的位数初始化为最大位数

    ll carry = 0; // 进位初始化为0
    for (ll i = 1; i <= n; i++) {
        ll sum = (i <= a[0] ? a[i] : 0) + (i <= b[0] ? b[i] : 0) + carry;
        result[i] = sum % 10; // 当前位的结果
        carry = sum / 10; // 计算进位
    }

    // 检查是否还有进位需要加到最高位
    if (carry > 0) {
        result[++result[0]] = carry;
    }
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    cin >> n;
    cin >> s;

    memset(res,0,sizeof(res));
    rep(i,0,n-1) {
        for(ll j=0;j<n-i;j+=1) buffer1[j] = s[i]; buffer1[n-i] = 0;
        
        ll buffer2_len = 0, data = i+1;
        while(data) {
            buffer2[buffer2_len] = data % 10;
            data = data / 10;
            buffer2_len += 1;
        }
        buffer2[buffer2_len] = 0;
        for(ll j=0;j<buffer2_len;j+=1)
        {
            ll k = buffer2_len - j - 1;
            if(j < k) swap(buffer2[j],buffer2[k]);
        }

        solve(buffer1,buffer2,buffer3);

        memcpy(buffer4,res,sizeof(res));
        add(buffer3,buffer4,res);
    }

    for(ll i=res[0]; i>=1; i-=1) {
        cout << res[i];
    } cout << endl;

    return 0;
}