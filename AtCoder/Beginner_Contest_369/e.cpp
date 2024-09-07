// 最短路，但是要求某些边一定要经过

#include<algorithm>
#include<iostream>
#include<vector>
#include<climits>
#include<cstdint>

const int64_t maxn = 401;
const int64_t maxm = 2e5 + 1;

struct edge
{
    int64_t from,to,cost;
};

int64_t n,m,dist[maxn][maxn];
std::vector<edge> edges;

void floydWarshall(int64_t n) {
    for (int64_t k = 1; k <= n; ++k) {
        for (int64_t i = 1; i <= n; ++i) {
            for (int64_t j = 1; j <= n; ++j) {
                if (dist[i][k] != INT64_MAX && dist[k][j] != INT64_MAX)
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main()
{
    std::cin >> n >> m;

    // 初始化距离数组
    for (int64_t i = 1; i <= n; ++i) {
        for (int64_t j = 1; j <= n; ++j) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INT64_MAX;
        }
    }

    edges.push_back((edge){0,0,0});
    for (int64_t i = 0; i < m; ++i) {
        int64_t u, v, w;
        std::cin >> u >> v >> w;
        dist[u][v] = std::min(dist[u][v], w); // 因为是无向图
        dist[v][u] = std::min(dist[v][u], w);

        edges.push_back((edge){u,v,w});
    }
    floydWarshall(n);

    int64_t q;
    std::cin >> q;
    while(q--)
    {
        int64_t k,ks[8];
        int64_t ans = INT64_MAX;
        std::vector<int64_t> index;

        std::cin >> k;
        index.push_back(0);
        for(int64_t i=1;i<=k;i+=1)
        {
            std::cin >> ks[i];
            index.push_back(i);
        }
        for(uint32_t i=0;i<((uint32_t)1 << k);i+=1)
        {
            do{
                // key
                /*
                std::cout << 1 << " - ";
                for(int64_t j=1;j<=k;j+=1)
                {
                    std::cout << "["
                        << (((i & ((uint32_t)1 << (j-1))) == 0) ? edges[ks[index[j]]].from : edges[ks[index[j]]].to)
                        << " - "
                        << (((i & ((uint32_t)1 << (j-1))) == 0) ? edges[ks[index[j]]].to : edges[ks[index[j]]].from)
                        << "]";
                }
                std::cout << " - " << n << std::endl;
                */

                int64_t _ans = 0;
                for(int64_t j=1;j<=k;j+=1) _ans += edges[ks[index[j]]].cost;
                for(int64_t j=2;j<=k;j+=1)
                {
                    int64_t s = (i & ((uint32_t)1 << (j-2))) ? edges[ks[index[j-1]]].from : edges[ks[index[j-1]]].to;
                    int64_t t = (i & ((uint32_t)1 << (j-1))) ? edges[ks[index[j]]].to : edges[ks[index[j]]].from;
                    _ans += dist[s][t];
                }
                int64_t t = (i & (uint32_t)1) ? edges[ks[index[1]]].to : edges[ks[index[1]]].from;
                _ans += dist[1][t];

                int64_t s = (i & ((uint32_t)1 << (k-1))) ? edges[ks[index[k]]].from : edges[ks[index[k]]].to;
                _ans += dist[s][n];

                ans = std::min(ans, _ans);

            }while(std::next_permutation(index.begin()+1,index.end()));
        }

        std::cout << ans << std::endl;
    }

    return 0;
}