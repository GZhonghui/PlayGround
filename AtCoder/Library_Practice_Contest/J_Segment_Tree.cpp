/*

线段树

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <atcoder/all>

namespace Segment_Tree {
    using namespace std;
    using namespace atcoder;

    using ll = int64_t;

    struct S_both {
        ll sum;
        ll max;
        ll len;
    };

    struct F_both {
        ll add;
        ll set;
        bool is_set;
    };

    S_both op_both(S_both a, S_both b) {
        return S_both{
            a.sum + b.sum,
            max(a.max, b.max),
            a.len + b.len
        };
    }

    S_both e_both() {
        return S_both{0, (ll)-1e18, 0};
    }

    S_both mapping_both(F_both f, S_both s) {
        if (f.is_set) {
            return S_both{
                f.set * s.len,
                f.set,
                s.len
            };
        } else {
            return S_both{
                s.sum + f.add * s.len,
                s.max + f.add,
                s.len
            };
        }
    }

    F_both composition_both(F_both new_op, F_both old_op) {
        if (new_op.is_set) {
            return new_op;
        } else if (old_op.is_set) {
            return F_both{new_op.add + old_op.add, old_op.set + new_op.add, true};
        } else {
            return F_both{new_op.add + old_op.add, 0, false};
        }
    }

    F_both id_both() {
        return F_both{0, 0, false};
    }

    inline void solve() {
        ll n, q;
        cin >> n >> q;

        vector<S_both> initial(n + 1, {0, 0, 1}); // avaliable range: [0, n]
        for(int i = 1; i <= n; i++) {
            static ll _t;
            cin >> _t;
            initial[i] = S_both{_t, _t, 1};
        }

        lazy_segtree<S_both, op_both, e_both, F_both, mapping_both, composition_both, id_both> seg(initial);

        while(q--) {
            static ll t, a, b;
            cin >> t >> a >> b;

            if(t == 1) {
                seg.set(a, S_both{b, b, 1});
            } else if(t == 2) {
                cout << seg.prod(a, b + 1).max << endl; // [a, b]
            } else if(t == 3) {
                cout << seg.max_right(a, [&](S_both s) {
                    return s.max < b;
                }) << endl;
            }
        }
    }
}

int main() {
    Segment_Tree::solve();
    return 0;
}