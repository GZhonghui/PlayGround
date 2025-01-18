# 经典题目！经典思维误区！

# 之前一直WA是因为没有考虑买不完的情况
# 二分一个limit，在limit之下的都买完，之上的都不买，这样太极端
# 所以需要考虑买不完的情况，limit+1的买一部分，这样就对了

import math

def buy_all(n, m, p, price_limit):
    last_money = m
    buy_cnt = 0
    potential_buy_cnt = 0

    for i in range(n):
        price = p[i]
        _buy_cnt = math.floor((price_limit / price + 1) * 0.5)
        _buy_cost = price * _buy_cnt * _buy_cnt
        if _buy_cost > last_money:
            return None
        last_money -= _buy_cost
        buy_cnt += _buy_cnt
        if (_buy_cnt * 2 + 1) * price == price_limit + 1:
            potential_buy_cnt += 1

    buy_cnt += min(potential_buy_cnt, last_money // (price_limit + 1))
    return buy_cnt

def solve():
    n, m = map(int, input().split())
    p = list(map(int, input().split()))
    
    left, right = 0, 10**18
    
    while right - left > 3:
        mid = (left + right) >> 1
        if buy_all(n, m, p, mid) is not None:
            left = mid
        else:
            right = mid - 1
    
    while right >= left:
        _cnt = buy_all(n, m, p, right)
        if _cnt is not None:
            print(_cnt)
            return
        right -= 1

if __name__ == "__main__":
    solve()