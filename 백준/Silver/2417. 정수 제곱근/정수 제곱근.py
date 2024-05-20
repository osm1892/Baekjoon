n = int(input())

low = 0
high = n
mid = 0

while low <= high:
    mid = (low + high) // 2

    if mid ** 2 < n:
        low = mid + 1
    else:
        high = mid - 1

if mid ** 2 < n:
    mid += 1

print(mid)
