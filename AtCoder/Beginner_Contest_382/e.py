# PyPy ~150 ms
# CPython TLE
# 评测机的 CPython 没有问题吧？

import math

n,x = [int(i) for i in input().split()]
p = [float(i) * 0.01 for i in input().split()]
g = [0.0] * (n + 1)
g[0] = 1.0

for i in range(n):
    for j in range(n, 0, -1):
        g[j] = g[j] * (1 - p[i]) + g[j-1] * p[i]
    g[0] *= 1 - p[i]

dp = [0.0] * (x + 1)
for i in range(1, x+1):
    dp[i] = 1.0
    for j in range(1, n+1):
        dp[i] += dp[max(i - j, 0)] * g[j]
        if i - j <= 0:
            break
    dp[i] /= (1 - g[0])
    
print(f"{dp[x]:.20f}")