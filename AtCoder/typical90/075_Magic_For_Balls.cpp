#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

void breakdown(int64_t N, vector<int64_t>& result) {
  for (int64_t i = 2; i * i <= N; i++) {
    if (N % i == 0) {  // 如果 i 能够整除 N，说明 i 为 N 的一个质因子。
      while (N % i == 0) N /= i,result.push_back(i);
    }
  }
  if (N != 1) {  // 说明再经过操作之后 N 留下了一个素数
    result.push_back(N);
  }
}

int64_t n;

int32_t main()
{
    // freopen("in.txt","r",stdin);

    std::cin >> n;
    vector<int64_t> res;
    breakdown(n,res);

    int64_t ans = 0, _size = 1;
    while(_size < res.size())
    {
        _size = _size * 2;
        ans += 1;
    }

    std::cout << ans << std::endl;

    return 0;
}