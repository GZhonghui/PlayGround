/*

2-SAT
这个算法还有点不明白的地方

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>
#include <atcoder/all>

namespace TwoSAT {

    using namespace atcoder;
    using namespace std;

    using ll = int64_t;

    inline void solve() {
        ll n, d;
        cin >> n >> d;

        two_sat ts(n);

        vector< pair<ll, ll> > points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].first >> points[i].second;
        }

        auto try_add_edge = [&](int i, bool f, int j, bool g) {
            ll pos_i = f ? points[i].first : points[i].second;
            ll pos_j = g ? points[j].first : points[j].second;
            
            // conflict
            if(abs(pos_i - pos_j) < d) {
                ts.add_clause(i, f, j, g);
            }
        };

        for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++) {
            try_add_edge(i, true, j, true);
            try_add_edge(i, true, j, false);
            try_add_edge(i, false, j, true);
            try_add_edge(i, false, j, false);
        }

        if(ts.satisfiable()) {
            cout << "Yes" << endl;
            auto ans = ts.answer();
            for(int i = 0; i < n; i++) {
                cout << (ans[i] ? points[i].second : points[i].first) << endl; // a little wried...
            }
        } else {
            cout << "No" << endl;
        }
    }

}

int main() {
    TwoSAT::solve();
    return 0;
}