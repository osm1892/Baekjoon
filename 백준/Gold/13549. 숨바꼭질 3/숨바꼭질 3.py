import collections


visit = [1e9] * 200001
a, b = map(int, input().split())
q = collections.deque()

q.append((a, 0))
visit[a] = 0
while len(q):
    cur, depth = q.popleft()

    if cur - 1 >= 0 and visit[cur - 1] > depth + 1:
        q.append((cur - 1, depth + 1))
        visit[cur - 1] = depth + 1
    if cur + 1 <= 100000 and visit[cur + 1] > depth + 1:
        q.append((cur + 1, depth + 1))
        visit[cur + 1] = depth + 1
    if cur * 2 <= 200000 and visit[cur * 2] > depth:
        q.append((cur * 2, depth))
        visit[cur * 2] = depth

print(visit[b])
