x,y = [int(i) for i in input().split()]
if x==y:
  print(1)
else:
  if (x-y)%2 == 0:
    print(3)
  else:
    print(2)