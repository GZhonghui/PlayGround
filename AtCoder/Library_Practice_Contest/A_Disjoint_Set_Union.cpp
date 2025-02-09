/*

一些ACL共通的内容：
区间都是左闭右开，下标都是0-indexed，C++17以上语言标准
https://atcoder.github.io/ac-library/production/document_en/index.html

并查集

*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <atcoder/all>

namespace Disjoint_Set_Union {
    using namespace atcoder;
    using namespace std;

    using ll = int64_t;

    inline void solve() {
        ll n, q;
        cin >> n >> q;

        dsu d(n); // [0, n)

        while(q--) {
            static ll t, u, v;
            cin >> t >> u >> v;

            if(t == 0) {
                d.merge(u, v);
            } else {
                cout << (d.same(u, v) ? 1 : 0) << endl;
            }
        }
    }
}

int main()
{
    Disjoint_Set_Union::solve();
    return 0;
}