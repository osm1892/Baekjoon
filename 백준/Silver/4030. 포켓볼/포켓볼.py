import sys
import math

read = sys.stdin.readline
write = sys.stdout.write

tris = set()
pows = set()

for i in range(1, 50000):
    tris.add(i * (i + 1) // 2)
    pows.add(i * i)

a, b = map(int, read().split())
test_case = 1
while a:
    count = 0

    for x in pows:
        if x <= a or b <= x:
            continue
        if x - 1 in tris:
            count += 1

    write(f"Case {test_case}: {count}\n")

    a, b = map(int, read().split())
    test_case += 1
