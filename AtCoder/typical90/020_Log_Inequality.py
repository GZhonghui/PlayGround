def main():
    a,b,c=[int(i) for i in input().split()]
    # if math.log2(a) < b*math.log2(c):
    if a < c**b:
        print("Yes")
    else:
        print("No")

if __name__=='__main__':
    main()