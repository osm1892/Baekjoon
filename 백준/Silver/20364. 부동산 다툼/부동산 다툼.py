import sys

read = sys.stdin.readline
write = sys.stdout.write

n, q = map(int, read().split())
arr = [int(read()) for _ in range(q)]
qs = set()

for num in arr:
    tmp = num
    blocker = 0
    while tmp > 0:
        if tmp in qs:
            blocker = tmp

        tmp //= 2

    write(f"{blocker}\n")
    qs.add(num)
