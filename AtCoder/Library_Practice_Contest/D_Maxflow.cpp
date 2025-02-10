/*

最大流

*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <atcoder/all>

namespace Maxflow {

    using namespace atcoder;
    using namespace std;

    inline void solve() {
        const int maxn = 108;
        char grid[maxn][maxn];
        int n, m;

        cin >> n >> m;
        for(int i = 0; i < n; i++) {
            cin >> grid[i];
        }

        mf_graph<int> mf(n * m + 2);

        int s = n * m, t = s + 1; // [0, n * m) + [n * m, n * m + 1]

        const int dx[] = {0, 1, 0, -1};
        const int dy[] = {1, 0, -1, 0};

        auto id = [&](int i, int j) -> int {
            return i * m + j;
        };

        auto pos = [&](int id) -> pair<int, int> {
            return {id / m, id % m};
        };

        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
            if(grid[i][j] == '.') {
                if((i + j) & 1) {
                    mf.add_edge(s, id(i, j), 1);
                    for(int k = 0; k < 4; k++) {
                        int x = i + dx[k], y = j + dy[k];
                        if(x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == '#') {
                            continue;
                        }
                        mf.add_edge(id(i, j), id(x, y), 1);
                    }
                } else {
                    mf.add_edge(id(i, j), t, 1);
                }
            }
        }

        cout << mf.flow(s, t) << endl;

        for(auto e : mf.edges()) {
            if(e.from < n * m && e.to < n * m && e.flow == 1) {
                int x = min(e.from, e.to), y = max(e.from, e.to);
                auto px = pos(x), py = pos(y);
                if(px.first == py.first) {
                    grid[px.first][px.second] = '>';
                    grid[py.first][py.second] = '<';
                } else if(px.second == py.second) {
                    grid[px.first][px.second] = 'v';
                    grid[py.first][py.second] = '^';
                }
            }
        }

        for(int i = 0; i < n; i++) {
            cout << grid[i] << endl;
        }
    }
}

int main() {
    Maxflow::solve();
    return 0;
}