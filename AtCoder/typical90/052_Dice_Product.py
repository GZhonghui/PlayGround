mod = int(1e9+7)
n = int(input())

ans = 1
for i in range(n):
    one = [int(i) for i in input().split()]
    ans = ans * sum(one) % mod

print(ans)