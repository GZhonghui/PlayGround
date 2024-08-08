n=int(input())
names=set()
for i in range(n):
    name = input()
    if name not in names:
        print(i+1)
        names.add(name)