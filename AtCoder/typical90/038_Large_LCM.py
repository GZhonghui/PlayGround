from math import gcd

a,b = [int(i) for i in input().split()]
g=gcd(a,b)
ans = a*b//g
if ans<=1e18: print(ans)
else: print('Large')