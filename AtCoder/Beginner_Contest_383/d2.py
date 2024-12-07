import math

class Sieve:
    maxn = int(2e6 + 10)

    def __init__(self):
        self.check = [False] * Sieve.maxn
        self.prime = list()

    def calc(self, n: int) -> None:
        for i in range(2,n+1):
            if not self.check[i]:
                self.prime.append(i)
            for j in self.prime:
                if i*j > n: break
                self.check[i*j] = True
                if i%j == 0: break

n = int(input())
solver = Sieve()
solver.calc(int(math.sqrt(n)) + 1)

ans = 0
ps = len(solver.prime)
running = True
for i in range(ps):
    x = solver.prime[i]
    if running:
        if x**8 > n:
            running = False
        else:
            ans += 1
    for j in range(i+1,ps):
        y = solver.prime[j]
        if x * x * y * y <= n:
            ans += 1
        else:
            break

print(ans)
