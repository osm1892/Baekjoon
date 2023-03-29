n = int(input())
data = list(map(int, input().split()))

l, r = 0, n - 1

result = 1e9

while l < r:
    cur = data[l] + data[r]

    if cur == 0:
        print(0)
        break

    if abs(cur) < abs(result):
        result = cur

    if cur < 0:
        l += 1
    else:
        r -= 1

print(result)
