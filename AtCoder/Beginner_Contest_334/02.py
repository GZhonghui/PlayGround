from math import *

a,m,l,r=[int(i) for i in input().split()]
if l<=a and a<=r:
    ll=(a-l)
    rr=(r-a)
    print(rr//m+ll//m+1)
elif a<l:
    print((r-a)//m-(l-1-a)//m)
elif a>r:
    print((a-l)//m-(a-r-1)//m)
