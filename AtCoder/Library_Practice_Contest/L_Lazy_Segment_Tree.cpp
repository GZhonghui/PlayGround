/*

lazy segment tree

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <atcoder/all>

namespace Lazy_Segment_Tree
{
    using namespace std;
    using namespace atcoder;

    using ll = int64_t;

    struct S_both
    {
        ll zero, one, cnt, len;
    };

    struct F_both
    {
        ll is_flip;
    };

    S_both op_both(S_both a, S_both b)
    {
        return S_both{
            a.zero + b.zero,
            a.one + b.one,
            a.cnt + b.cnt + a.one * b.zero,
            a.len + b.len
        };
    }

    S_both e_both()
    {
        return S_both{0, 0, 0, 0};
    }

    S_both mapping_both(F_both f, S_both s)
    {
        if (f.is_flip)
        {
            return S_both{
                s.one,
                s.zero,
                s.one * s.zero - s.cnt,
                s.len
            };
        }
        return s;
    }

    F_both composition_both(F_both new_op, F_both old_op)
    {
        return F_both{
            new_op.is_flip ^ old_op.is_flip
        };
    }

    F_both id_both()
    {
        return F_both{0};
    }

    inline void solve()
    {
        ll n, q;
        cin >> n >> q;

        vector<S_both> initial(n + 1, {1, 0, 0, 1});
        for (ll i = 1; i <= n; i++)
        {
            static ll _t;
            cin >> _t;
            initial[i] = S_both{1 - _t, _t, 0, 1};
        }

        lazy_segtree<S_both, op_both, e_both, F_both, mapping_both, composition_both, id_both> seg(initial);

        while(q--) {
            static ll t, l, r;
            cin >> t >> l >> r;

            if(t == 1) {
                seg.apply(l, r + 1, F_both{1});
            } else {
                cout << seg.prod(l, r + 1).cnt << endl;
            }
        }
    }
}

int main()
{
    Lazy_Segment_Tree::solve();
    return 0;
}