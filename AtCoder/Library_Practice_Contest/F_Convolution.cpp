/*

Convolution 卷积

*/

#include <algorithm>
#include <iostream>
#include <atcoder/all>

namespace Convolution {

    using namespace std;
    using namespace atcoder;
    using mint = modint998244353;

    inline void solve() {
        int n, m, t;
        cin >> n >> m;
        vector<mint> a(n), b(m);
        for(int i = 0; i < n; i++) cin >> t, a[i] = t;
        for(int i = 0; i < m; i++) cin >> t, b[i] = t;

        // c[0] = a[0] * b[0], 0 + 0 == 0
        // c[1] = a[0] * b[1] + a[1] * b[0], 0 + 1 == 1, 1 + 0 == 1
        auto c = convolution(a, b);
        for(int i = 0; i < n + m - 1; i++) {
            cout << c[i].val() << " ";
        }
        cout << endl;
    }
}

int main() {
    Convolution::solve();
    return 0;
}