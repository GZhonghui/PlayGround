n,k = [int(i) for i in input().split()]
A = [int(i) for i in input().split()]
B = [int(i) for i in input().split()]

diff = 0
for i in range(n):
    diff += abs(A[i]-B[i])

if diff <= k and ((k-diff) % 2) == 0:
    print("Yes")
else:
    print("No")