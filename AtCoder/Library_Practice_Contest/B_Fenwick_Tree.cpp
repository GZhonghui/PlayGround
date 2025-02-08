/*

Fenwick Tree 树状数组

*/

#include <algorithm>
#include <iostream>
#include <atcoder/all>

namespace Fenwick_Tree {
    using namespace atcoder;
    using namespace std;

    using ll = int64_t;

    inline void solve() {
        ll n,q;
        cin >> n >> q;

        fenwick_tree<ll> fw(n); // [0, n)

        for(ll i = 0; i < n; i++) {
            static ll x;
            cin >> x;
            fw.add(i, x);
        }

        while(q--) {
            static ll t, a, b;
            cin >> t >> a >> b;

            if(t == 0) {
                fw.add(a, b); // add value b on pos a
            } else {
                cout << fw.sum(a, b) << endl; // [a, b)
            }
        }
    }

}

int main()
{
    Fenwick_Tree::solve();
    return 0;
}