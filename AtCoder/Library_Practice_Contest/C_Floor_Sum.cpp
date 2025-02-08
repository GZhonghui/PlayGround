/*

Floor Sum
暂时不懂可以用在哪里

*/

#include <algorithm>
#include <iostream>
#include <atcoder/all>

namespace Floor_Sum {

    using namespace atcoder;
    using namespace std;

    using ll = int64_t;

    inline void solve() {
        ll n, m, a, b;
        cin >> n >> m >> a >> b;

        cout << floor_sum(n, m, a, b) << endl;
    }

}

int main() {
    int T;
    std::cin >> T;
    while(T--) {
        Floor_Sum::solve();
    }
    return 0;
}