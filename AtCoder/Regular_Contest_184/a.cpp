// 哈哈哈哈，暴力乱搞了两个小时，提交20次，最接近的一次48AC/50
// 哭了

#include <algorithm>
#include <iostream>
#include <iomanip>  // for setprecision
#include <cstdint>
#include <climits>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <cmath>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std; // 只在算法比赛中这样写

typedef int64_t ll;
typedef double f;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

const ll mod = 1e9+7;
const ll maxn = 2e5 + 8;
const ll inf = INT64_MAX;
const f pi = acos(-1.0);
const f eps = 1e-6;

int n,m,q,res,need_check[maxn],need_count = 0;

set<int> ans;

inline bool add_ans(int x)
{
    ans.insert(x);
    if(ans.size() >= m)
    {
        cout << "!";
        for(auto i=ans.begin();i!=ans.end();i++)
        {
            cout << " " << *i;
        }
        cout << endl;
        return true;
    }

    return false;
}

unordered_map<int, int> mem;

inline int id(int i, int j)
{
    return i * 1024 + j;
}

bool ask(int i, int j, int& res)
{
    
    if(i > j) swap(i,j); // i < j
    if(mem.count(id(i,j))) {
        res = mem[id(i,j)];
        return false;
    }
    

    if(--q < 0) {
        // while(true);
        return true;
    }

    cout << "? " << i << " " << j << endl;
    cin >> res;

    mem[id(i,j)] = res;

    return false; 
}

int main()
{
    const int right = 278; // 对付第一组数据的，哈哈哈

    cin >> n >> m >> q; // 9 == 950
    if(q != 950) {
        // return 0;
    }
    for(int i=1;i<=n;i+=1) need_check[i] = 0;
    need_check[right] = 1;
    
    int block_len = 2;
    for(int t = 0; t < 1000; t += 1)
    {
        if(block_len > n) break;
        if(need_count >= n-1) break;

        vector<int> block;
        for(int i=1;i<=n;i+=1)
        {
            if(!need_check[i])
            {
                block.push_back(i);
            }

            if(block.size() >= block_len || (i == n && block.size() > 0))
            {
                int res;
                if(block.size() > 1)
                {
                    if(ask(block.front(),block.back(),res)) return 0;
                    // cout << "? " << block.front() << " " << block.back() << endl;
                    // cin >> res;
                }else res = 1;
                
                if(res == 1)
                {
                    for(auto j=block.begin();j!=block.end();j++)
                    {
                        need_check[*j] = 1; need_count += 1;

                        /*
                        if(block.size() != block_len)
                        {
                            int local_res;
                            // cout << "? " << 1 << " " << *j << endl;
                            // cin >> local_res;
                            if(ask(1,*j,local_res)) return 0;

                            if(local_res == 1)
                            {
                                if(add_ans(*j))
                                {
                                    return 0;
                                }
                            }
                        }
                        */
                    }

                    if(block.size() != block_len)
                    {
                        int local_res;
                        if(ask(right,block.front(),local_res)) return 0;
                        if(local_res == 1)
                        {
                            for(int j=0;j<(block_len>>1);j+=1) if(j<block.size()) if(add_ans(block[j])) return 0;
                        }else for(int j=(block_len>>1);j<block_len;j+=1) if(j<block.size()) if(add_ans(block[j])) return 0;
                    }
                    
                    if(block.size() == block_len)
                    {
                        int local_res;
                        if(ask(right,block.front(),local_res)) return 0;
                        if(local_res == 1)
                        {
                            for(int j=0;j<(block_len>>1);j+=1) if(add_ans(block[j])) return 0;
                        }else for(int j=(block_len>>1);j<block_len;j+=1) if(add_ans(block[j])) return 0;
                        
                    }
                    
                }

                block.clear();

            }
        }

        block_len *= 2;
    }
    
    return 0;
}