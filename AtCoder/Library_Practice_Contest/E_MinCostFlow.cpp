/*

最小费用流

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_set>
#include <atcoder/all>

namespace Min_Cost_Flow {
    using namespace atcoder;
    using namespace std;

    using ll = int64_t;

    const ll h = 1e9 + 1;

    inline void solve() {
        ll n, k;
        cin >> n >> k;

        ll number_cnt = n * n;
        ll s = number_cnt + n * 2 + 1, t = s + 1;
        mcf_graph<ll, ll> g(t + 1);
        g.add_edge(s, t, k * n, h); // waste some flow...

        vector< vector<ll> > a(n + 1, vector<ll>(n + 1, 0));

        for(ll i = 1; i <= n; i++) for(ll j = 1; j <= n; j++) {
            cin >> a[i][j];
        }

        for(ll i = 1; i <= n; i++) {
            ll l = number_cnt + i, r = l + n;
            g.add_edge(s, l, k, 0);
            g.add_edge(r, t, k, 0);

            for(ll _i = 1, _t = 0; _i <= n; _i++) for(ll _j = 1; _j <= n; _j++) {
                ++_t;
                // cost is [cost per flow]
                if(_i == i) g.add_edge(l, _t, 1, h - a[_i][_j]); // use minus, convert [min cost] to [max cost]
                if(_j == i) g.add_edge(_t, r, 1, 0);
            }
        }

        auto [flow, cost] = g.flow(s, t, k * n); // add limit to flow
        ll res = h * flow - cost;

        unordered_set<ll> selected;
        for(auto e : g.edges()) {
            if(e.to <= number_cnt && e.flow > 0) {
                selected.insert(e.to);
            }
        }

        cout << res << endl;
        for(ll i = 1, _t = 0; i <= n; i++) {
            for(ll j = 1; j <= n; j++) {
                if(selected.count(++_t)) cout << 'X';
                else cout << '.';
            }
            cout << endl;
        }
    }
}

int main() {
    Min_Cost_Flow::solve();
    return 0;
}