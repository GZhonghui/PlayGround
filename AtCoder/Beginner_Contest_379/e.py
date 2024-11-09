# 算法应该是正确的，速度太慢

import sys

sys.set_int_max_str_digits(500000)

def main():
    n = int(input())
    s = input()

    ans = 0

    for i in range(n):
        ans = ans + int(s[i] * (n-i)) * (i+1)

    print(ans)
    
main()