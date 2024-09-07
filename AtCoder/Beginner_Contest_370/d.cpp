#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cstdint>
#include<unordered_map>
#include<unordered_set>

const int64_t max_size = 4e5 + 1;
const int64_t dx[4] = {0,0,-1,1};
const int64_t dy[4] = {-1,1,0,0};

int64_t h,w;
std::unordered_map<int64_t, int64_t> fa[4];
std::unordered_set<int64_t> flag;
std::unordered_map<int64_t, std::pair<int64_t,int64_t> > id_to_rc;

int64_t hash(int64_t r, int64_t c)
{
    int64_t id = (int64_t)r * max_size + c;
    id_to_rc[id] = std::make_pair(r,c);
    return id;
}

int64_t root(int64_t i, int64_t node)
{
    if(!flag.count(node))
    {
        return node;
    }
    if(fa[i][node] == -1)
    {
        return -1;
    }
    return fa[i][node] = root(i,fa[i][node]);
}

inline bool in(int64_t r, int64_t c)
{
    return 1 <= r && r <= h && 1 <= c && c <= w;
}

inline void destroy(int64_t r, int64_t c, int64_t id, int64_t& ans)
{
    flag.insert(id);
    ans -= 1;
    // std::cout << "destroy: " << r << "," << c << std::endl;

    for(int64_t i=0;i<4;i+=1)
    {
        fa[i][id] = -1;
        int64_t rr = r + dx[i], cc = c + dy[i];
        if(in(rr,cc))
        {
            fa[i][id] = root(i,hash(rr,cc));
        }
    }
}

int main()
{
    int64_t q,r,c;
    std::cin >> h >> w >> q;

    int64_t ans = h * w;
    while(q--)
    {
        std::cin >> r >> c;

        int64_t id = hash(r,c);
        if(!flag.count(id))
        {
            destroy(r,c,id,ans);
        }
        else
        {
            for(int64_t i=0;i<4;i+=1)
            {
                int64_t target = root(i,id);
                if(target != -1)
                {
                    destroy(id_to_rc[target].first,id_to_rc[target].second,target,ans);
                }
            }
        }
    }

    std::cout << ans << std::endl;

    return 0;
}