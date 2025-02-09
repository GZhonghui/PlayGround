/*

lazy segment tree

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <atcoder/all>

namespace Range_Affine_Range_Sum {
    using namespace std;
    using namespace atcoder;

    using ll = int64_t;
    using mint = modint998244353;

    struct S_both {
        mint sum, len;
    };

    struct F_both {
        mint b, c;
    };

    S_both op_both(S_both a, S_both b) {
        return S_both{
            a.sum + b.sum,
            a.len + b.len
        };
    }

    S_both e_both() {
        return S_both{0, 0};
    }

    S_both mapping_both(F_both f, S_both s) {
        return S_both{
            f.b * s.sum + f.c * s.len,
            s.len
        };
    }

    F_both composition_both(F_both new_op, F_both old_op) {
        return F_both{
            new_op.b * old_op.b,
            new_op.b * old_op.c + new_op.c
        };
    }

    F_both id_both() {
        return F_both{1, 0};
    }

    inline void solve() {
        ll n, q;
        cin >> n >> q;

        vector<S_both> initial(n, {0, 1}); // avaliable range: [0, n)
        for(int i = 0; i < n; i++) {
            static ll _t;
            cin >> _t;
            initial[i] = S_both{_t, 1};
        }

        lazy_segtree<S_both, op_both, e_both, F_both, mapping_both, composition_both, id_both> seg(initial);

        while(q--) {
            static ll t, l, r, b, c;
            cin >> t >> l >> r;

            if(t == 0) {
                cin >> b >> c;
                seg.apply(l, r, F_both{b, c});
            } else if(t == 1) {
                cout << seg.prod(l, r).sum.val() << endl;
            }
        }
    }
}

int main() {
    Range_Affine_Range_Sum::solve();
    return 0;
}