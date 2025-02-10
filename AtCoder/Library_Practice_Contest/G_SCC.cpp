/*

SCC 强连通分量

*/

#include <algorithm>
#include <iostream>
#include <atcoder/all>

namespace SCC {

    using namespace std;
    using namespace atcoder;

    inline void solve() {
        int n, m;
        cin >> n >> m;
        scc_graph g(n);
        for(int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            g.add_edge(u, v);
        }

        auto scc = g.scc(); // with topological order
        cout << scc.size() << endl;
        for(auto &v : scc) {
            cout << v.size() << " ";
            for(auto &u : v) {
                cout << u << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    SCC::solve();
    return 0;
}