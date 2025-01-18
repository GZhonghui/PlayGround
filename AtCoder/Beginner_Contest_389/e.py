import heapq

def can_buy(n, m, p, cnt):
    if cnt == 0:
        return True

    remain = m
    pq = []
    
    for i in range(n):
        next_price = p[i]
        heapq.heappush(pq, (next_price, 0, i))
    
    need_to_buy = cnt
    for _ in range(cnt):
        price, buy_cnt, idx = heapq.heappop(pq)
        
        if price > remain:
            return False
        if price * need_to_buy > remain:
            return False

        need_to_buy -= 1
        remain -= price
        buy_cnt += 1
        next_price = p[idx] * ((buy_cnt + 1) * (buy_cnt + 1) - buy_cnt * buy_cnt)
        heapq.heappush(pq, (next_price, buy_cnt, idx))
    
    return True

def solve():
    n, m = map(int, input().split())
    p = list(map(int, input().split()))
    
    left, right = 0, 10**18
    
    while right - left > 3:
        mid = (left + right) >> 1
        if can_buy(n, m, p, mid):
            left = mid
        else:
            right = mid - 1
    
    while right >= left:
        if can_buy(n, m, p, right):
            print(right)
            return
        right -= 1

if __name__ == "__main__":
    solve()