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

struct house {
    ll id,x,y;
}houses[maxn];

bool cmp_x_first(const house &a, const house &b) {
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

bool cmp_y_first(const house &a, const house &b) {
    if(a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

struct road {
    ll pin,l,r;

    bool operator<(const road &other) const {
        if(pin == other.pin) return r < other.r;
        return pin < other.pin;
    }
}roads_ud[maxn], roads_lr[maxn];

ll n,m,sx,sy,roads_ud_size = 0, roads_lr_size = 0;

ll input_x[maxn],input_y[maxn],input_c[maxn];
char input_d[maxn];

namespace ac
{

using namespace std;
using ll=long long;

int main(){
	int n,m;
	ll x,y;
	// cin >> n >> m >> x >> y;
    n = ::n;
    m = ::m;
    x = ::sx;
    y = ::sy;
	
	map<ll,set<ll>>xy;//xy[i]={j s.t. (i,j) に家}
	map<ll,set<ll>>yx;//yx[j]={i s.t. (i,j) に家}
	
	for(int i=0;i<n;i++){
		int xx,yy;
		// cin >> xx >> yy;
        xx = ::input_x[i+1];
        yy = ::input_y[i+1];

		xy[xx].insert(yy);
		yx[yy].insert(xx);
	}
	
	int ans=0;
	for(int i=0;i<m;i++){
		char c;
		int d;
		// cin >> c >> d;
        c = ::input_d[i+1];
        d = ::input_c[i+1];

		if(c=='U'){
			ll new_y=y+d;
			auto it=xy[x].lower_bound(y);
			while(it!=xy[x].end()&&*it<=new_y){
				ans++;
				yx[*it].erase(x);
				it=xy[x].erase(it);
			}
			y=new_y;
		}else if(c=='D'){
			ll new_y=y-d;
			auto it=xy[x].lower_bound(new_y);
			while(it!=xy[x].end()&&*it<=y){
				ans++;
				yx[*it].erase(x);
				it=xy[x].erase(it);
			}
			y=new_y;
		}else if(c=='L'){
			ll new_x=x-d;
			auto it=yx[y].lower_bound(new_x);
			while(it!=yx[y].end()&&*it<=x){
				ans++;
				xy[*it].erase(y);
				it=yx[y].erase(it);
			}
			x=new_x;
		}else if(c=='R'){
			ll new_x=x+d;
			auto it=yx[y].lower_bound(x);
			while(it!=yx[y].end()&&*it<=new_x){
				ans++;
				xy[*it].erase(y);
				it=yx[y].erase(it);
			}
			x=new_x;
		}
	}
	
	// cout << x << ' ' << y << ' ' << ans << endl;

    return ans;
}

}

int main_test()
{
#ifdef ZH_DEBUG
    freopen("in.txt", "r", stdin);
#endif
    roads_ud_size = 0, roads_lr_size = 0;
    // cin >> n >> m >> sx >> sy;
    ll _sx = sx, _sy = sy;
    rep(i,1,n) {
        houses[i].x = input_x[i];
        houses[i].y = input_y[i];
        // cin >> houses[i].x >> houses[i].y;
        houses[i].id = i;

        input_x[i] = houses[i].x;
        input_y[i] = houses[i].y;
    }

    rep(i,1,m) {
        char dir;
        ll len;
        // cin >> dir >> len;
        dir = input_d[i];
        len = input_c[i];

        input_d[i] = dir;
        input_c[i] = len;

        switch(dir) {
            case 'U':
                roads_ud[++roads_ud_size] = (road){sx, sy, sy + len};
                sy += len;
            break;
            case 'D':
                roads_ud[++roads_ud_size] = (road){sx, sy - len, sy};
                sy -= len;
            break;
            case 'L':
                roads_lr[++roads_lr_size] = (road){sy, sx - len, sx};
                sx -= len;
            break;
            case 'R':
                roads_lr[++roads_lr_size] = (road){sy, sx, sx + len};
                sx += len;
            break;
        }

    }

    sort(roads_lr+1, roads_lr+1+roads_lr_size);
    sort(roads_ud+1, roads_ud+1+roads_ud_size);

    unordered_set<ll> cnt;

    ll _idx = 1;
    sort(houses+1, houses+1+n, cmp_x_first); // up & down
    rep(i,1,roads_ud_size) {
        const road &now = roads_ud[i];

        while(_idx <= n && houses[_idx].x < now.pin) _idx += 1;
        while(_idx <= n && houses[_idx].x == now.pin && houses[_idx].y <= now.r) {
            if(houses[_idx].y >= now.l) cnt.insert(houses[_idx].id);
            _idx +=1;
        }
    }

    _idx = 1;
    sort(houses+1, houses+1+n, cmp_y_first);
    rep(i,1,roads_lr_size) {
        const road &now = roads_lr[i];

        while(_idx <= n && houses[_idx].y < now.pin) _idx += 1;
        while(_idx <= n && houses[_idx].y == now.pin && houses[_idx].x <= now.r) {
            if(houses[_idx].x >= now.l) cnt.insert(houses[_idx].id);
            _idx +=1;
        }
    }

    // cout << sx << " " << sy << " " << cnt.size() << endl;

    sx = _sx, sy = _sy;
    auto ac_res = ac::main();

    if(cnt.size() != ac_res) {
        // cout << "WA" << endl;
        cout << n << " " << m << " " << sx << " " << sy << endl;
        rep(i,1,n) cout << input_x[i] << " " << input_y[i] << endl;
        rep(i,1,m) cout << input_d[i] << " " << input_c[i] << endl;

        return -1;
    }

    return 0;
}

inline void gen_data()
{
    srand((unsigned)time(nullptr));
    n = 100, m = 100;
    sx = (rand() % 100) - 50;
    sy = (rand() % 100) - 50;

    rep(i,1,n) {
        input_x[i] = (rand() % 200) - 100;
        input_y[i] = (rand() % 200) - 100;
    }

    rep(i,1,m) {
        input_d[i] = "UPLR"[rand()%4];
        input_c[i] = rand() % 100 + 1;
    }
}

int main()
{
    while(true)
    {
        gen_data();
        if(-1 == main_test()) break;
    }
    
    return 0;
}