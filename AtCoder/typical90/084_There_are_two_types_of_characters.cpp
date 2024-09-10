#include <algorithm>
#include <iostream>
#include <cstdint>
#include <ctime>

using namespace std;

typedef int64_t ll;

// 字符串，结尾符
// 不想用下标0
// 那就空间开大一点
// 记住这个惨痛的教训
const ll maxn = 1e6 + 10;

ll n;
char s[maxn];

ll main_ok(ll n, char* s)
{
	// 入力
	int N = (int)n;
	std::string S(s);
	// std::cin >> N >> S;

	long long result = 0;

	if( N == 1)
	{
		// std::cout << 0 << std::endl;
		return 0;
	}

	int r = 1;
	for( int l = 0; l < N; ++l)
	{
		if( l == r )
		{
			++r;
		}

		while( r < N && S[r-1] == S[r])
		{
			++r;
		}

		// std::cout << "l:" << l << " r:" << r << std::endl;

		result += N - r;
	}

	// std::cout << result << std::endl;

	return result;
}

int main_mine()
{
    srand((unsigned)time(nullptr));
    n = 1e6;
    for(int i=1;i<=n;i+=1)
    {
        s[i] = (rand()%2) ? 'x' : 'o';
    }
    // cin >> n >> (s+1);

    ll ans = 0, o = 0, x = 0, l = 1, r = 0;
    while(r < n)
    {
        r += 1;
        if(s[r] == 'o')
        {
            o = r;
            if(x)
            {
                ans += x;
            }
        }
        if(s[r] == 'x')
        {
            x = r;
            if(o)
            {
                ans += o;
            }
        }
        // if(s[r] == 'o') o += 1;
        // if(s[r] == 'x') x += 1;

        /*
        while(min(o,x) > 0)
        {
            l += 1;
            if(s[l-1] == 'o') o -= 1;
            if(s[l-1] == 'x') x -= 1;
        }

        ans += (l-1);
        */
    }
    // cout << ans << endl;
    // cout << main_ok(n,s+1) << endl;
    // cout << ((ans == main_ok(n,s+1)) ? "AC" : "WA") << endl;
    if(ans != main_ok(n,s+1))
    {
        cout << "WA" << endl;
        return 1;
    }

    return 0;
}

int main()
{
    cin >> n >> (s+1);

    ll ans = 0, o = 0, x = 0, l = 1, r = 0;
    while(r < n)
    {
        r += 1;
        if(s[r] == 'o')
        {
            o = r;
            if(x)
            {
                ans += x;
            }
        }
        if(s[r] == 'x')
        {
            x = r;
            if(o)
            {
                ans += o;
            }
        }

    }
    cout << ans << endl;
    return 0;
}


int main1()
{
    while(true)
    {
        if(main_mine()) return 0;
    }
    return 0;
}