import collections

n, m = map(int, input().split())

prevs = collections.deque([0 for i in range(100)])
prevs[-1] = 1

for i in range(1, n + 1):
    cur = (prevs[-1] + prevs[-m]) % 1000000007
    prevs[0] = cur
    prevs.rotate(-1)

print(cur)