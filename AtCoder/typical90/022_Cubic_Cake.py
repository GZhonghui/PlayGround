from math import gcd

a,b,c = [int(i) for i in input().split()]
e=gcd(gcd(a,b),gcd(b,c))
print((a+b+c)//e-3)