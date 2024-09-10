#include <algorithm>
#include <iostream>
#include <cstdint>

typedef int64_t ll;

const ll mod = 1e9+7;
const int maxn = 100000 + 1;

void exgcd(ll a,ll b,ll& d,ll& x,ll& y){
    if(!b) { d = a; x = 1; y = 0; }
    else{ exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}

// 扩展欧几里得法，计算a的逆元，p是模数，a和p需要是互质的
ll inverse_element_exgcd(ll a, ll p){
    ll d,x,y;
    exgcd(a,p,d,x,y);
    return d == 1 ? (x+p)%p : -1;
}

// 来源：OI-Wiki，p是模数
ll qpow(ll a, ll b, ll p) {
    ll ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1) {
        if (b & 1) ans = (a * ans) % p;
        a = (a * a) % p;
    }
    return ans;
}

// 快速幂法，p是模数，且p需要是质数
ll inverse_element_qpow(ll a, ll p)
{
    // 【逆元】 = a^{p-2}
    return qpow(a,p-2,p);
}

// 线性求逆元，求[1,n]以内所有数字的逆元（i的逆元是inv[i]，p是模数）
void inverse_element_linear(ll n, ll p, ll* inv)
{
    inv[1] = 1;
    for (int i = 2; i <= n; ++i) {
        inv[i] = (ll)(p - p / i) * inv[p % i] % p;
    }
}

// 来源：OI-Wiki
// 计算n个任意数字（不一定要连续）的逆元
// a是输入（需要求逆元的n个数字，下标范围是[1,n]），inv是结果，p是模数
// 速度比上面【单独求逆元】要快
void inverse_elements(ll n, ll* a, ll* inv, ll p)
{
    ll s[n+1],sv[n+1];

    s[0] = 1;
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] * a[i] % p;
    sv[n] = qpow(s[n], p - 2, p);
    // 当然这里也可以用 exgcd 来求逆元,视个人喜好而定.
    for (int i = n; i >= 1; --i) sv[i - 1] = sv[i] * a[i] % p;
    for (int i = 1; i <= n; ++i) inv[i] = sv[i] * s[i - 1] % p;
}

ll jc[maxn];

int main()
{
    // freopen("in.txt","r",stdin);

    ll n,l;
    std::cin >> n >> l;

    jc[0] = jc[1] = 1;
    for(ll i=2; i<maxn; i+=1)
    {
        jc[i] = (jc[i-1]*i) % mod;
    }
    
    ll ans = 0;
    for(ll i = 0; i <= n; i += 1)
    {
        ll last = n - i;
        if(last % l) continue;

        ll j = last / l;

        // i, j
        ll local = (i == 0 || j == 0) ? 1 : jc[i+j] * inverse_element_qpow(jc[i],mod) % mod * inverse_element_qpow(jc[j],mod) % mod;
        ans = (ans + local) % mod;
    }

    std::cout << ans << std::endl;

    return 0;
}