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
#define rre(i, s, t) for (ll i = (t); i >= (s); i--)

using namespace std; // only in algorithm contests

typedef int64_t ll;
typedef uint64_t ull;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll maxn = 2e5 + 8;
const ll mod = 1e9 + 7;
const ll inf = 1e9 + 8;
const f pi = acos(-1.0);
const f eps = 1e-6;

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

ll a[100];

vector<string> all;

inline ll score(string x) {

    ll res = 0;
    for(char y : x) {
        if('A' <= y && y <= 'E')
        res += a[(y - 'A' + 1)];
    }
    return res;
}

bool cmp(const string &a, const string &b)
{
    if(score(a) == score(b)) return a < b;
    return score(a) > score(b);
}

int main()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    rep(i,1,5) cin >> a[i];








all.pb("ABCDE");
all.pb("BCDE");
all.pb("ACDE");
all.pb("ABDE");
all.pb("ABCE");
all.pb("ABCD");
all.pb("CDE");
all.pb("BDE");
all.pb("ADE");
all.pb("BCE");
all.pb("ACE");
all.pb("BCD");
all.pb("ABE");
all.pb("ACD");
all.pb("ABD");
all.pb("ABC");
all.pb("DE");
all.pb("CE");
all.pb("BE");
all.pb("CD");
all.pb("AE");
all.pb("BD");
all.pb("AD");
all.pb("BC");
all.pb("AC");
all.pb("AB");
all.pb("E");
all.pb("D");
all.pb("C");
all.pb("B");
all.pb("A");

sort(all.begin(),all.end(),cmp);

for(string s : all) {
    cout << s << endl;
}



    return 0;
}