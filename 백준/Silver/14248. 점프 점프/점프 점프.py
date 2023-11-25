import collections
import sys

read = sys.stdin.readline
write = sys.stdout.write

n = int(read())
arr = list(map(int, read().split()))
visit = [False] * n
s = int(read())

queue = collections.deque()

queue.append(s - 1)
visit[s - 1] = True

while queue:
    cur = queue.popleft()
    left = cur - arr[cur]
    right = cur + arr[cur]

    if left >= 0 and visit[left] == False:
        queue.append(left)
        visit[left] = True

    if right < n and visit[right] == False:
        queue.append(right)
        visit[right] = True

print(sum(visit))
