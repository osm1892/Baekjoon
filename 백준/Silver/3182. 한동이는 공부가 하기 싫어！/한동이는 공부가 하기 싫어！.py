import sys
import collections

read = sys.stdin.readline
write = sys.stdout.write

n = int(read())
answers = [int(read()) - 1 for _ in range(n)]
depths = [0 for _ in range(n)]
stack = collections.deque()

for i in range(n):
    stack.append((i, i, 1, 1 << i))

while stack:
    start, cur, depth, visit = stack.pop()

    next_cur = answers[cur]

    if visit & (1 << next_cur):
        depths[start] = depth
        continue

    stack.append((start, next_cur, depth + 1, visit | (1 << next_cur)))

max_value = max(depths)
print(depths.index(max_value) + 1)
