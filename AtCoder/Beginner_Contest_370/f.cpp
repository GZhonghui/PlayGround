// 很绕的一道题，卡了超久
// 猪脑爆炸了

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

const int64_t maxn = 4e5 + 8;

int64_t n,k,a[maxn],sum[maxn],succ_cut_size = 0;

inline int64_t q_a(int64_t id)
{
    while(id > n) id -= n;
    return a[id];
}

inline bool check(int64_t x)
{
    std::unordered_set<int64_t> cut;
    std::unordered_set<int64_t> succ_cut;

    int64_t succ = 0;
    for(int64_t i=0;i<n;i+=1)
    {
        if(cut.count(i)) continue;
        
        int64_t complated = 0,local_sum = 0;

        std::unordered_set<int64_t> this_cut;
        this_cut.insert(i);

        // todo
        // [i+1,i+n]
        for(int64_t j=i+1;j<=i+n;j+=1)
        {
            int64_t target_value = sum[j-1] + x;
            int64_t *it = std::lower_bound(sum+j,sum+i+n+1,target_value);
            if(it >= sum+i+n+1)
            {
                break;
            }
            j = it - sum;
            complated += 1;
            this_cut.insert(j%n);
        }

        /*
        for(int64_t j=i+1;j<=i+n;j+=1)
        {
            local_sum += q_a(j);
            if(local_sum >= x)
            {
                complated += 1;
                local_sum = 0;
                this_cut.insert(j%n);
            }
        }
        */

        if(complated >= k)
        {
            succ += 1;
            succ_cut.insert(this_cut.begin(),this_cut.end());
        }
        cut.insert(this_cut.begin(),this_cut.end());
    }

    succ_cut_size = (int64_t)succ_cut.size();

    return succ > 0;
}

int32_t main()
{
    std::cin >> n >> k;

    int64_t all = 0;
    for(int64_t i=1;i<=n;i+=1)
    {
        std::cin >> a[i];
        a[i+n] = a[i];
        all += a[i];
    }

    sum[0] = 0;
    for(int64_t i=1;i<=2*n;i+=1)
    {
        sum[i] = sum[i-1] + a[i];
    }

    int64_t l = 1, r = all / k + 1;
    while(r - l > 3)
    {
        int64_t mid = (l+r) >> 1;
        if(check(mid))
        {
            l = mid;
        }else
        {
            r = mid - 1;
        }
    }
    while(r >= l)
    {
        if(check(r))
        {
            // found
            std::cout << r << " " << n - succ_cut_size << std::endl;
            break;
        }
        r -= 1;
    }

    return 0;
}