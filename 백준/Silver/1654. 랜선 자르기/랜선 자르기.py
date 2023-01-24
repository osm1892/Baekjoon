import sys

read = sys.stdin.readline
write = sys.stdout.write

k, n = map(int, read().split())

cables = [int(read()) for i in range(k)]

high, low = 2**31, 0
mid = 0

while low <= high:
    mid = (high + low) // 2
    count = 0

    for cable in cables:
        count += cable // mid

    if count < n:
        high = mid - 1
    else:
        low = mid + 1

count = 0
for cable in cables:
    count += cable // mid

if count < n:
    mid -= 1

print(mid)
