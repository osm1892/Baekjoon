import queue
import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n, m = map(int, read().split())
    s, e = map(int, read().split())
    teleports = [[] for _ in range(n + 1)]

    for _ in range(m):
        x, y = map(int, read().split())
        teleports[x].append(y)
        teleports[y].append(x)

    visit = [-1] * (n + 1)
    q = queue.Queue()
    q.put(s)
    visit[s] = 0

    while q:
        cur = q.get()

        if cur == e:
            print(visit[e])
            return

        if cur != 1 and visit[cur - 1] == -1:
            visit[cur - 1] = visit[cur] + 1
            q.put(cur - 1)
        if cur != n and visit[cur + 1] == -1:
            visit[cur + 1] = visit[cur] + 1
            q.put(cur + 1)

        for tele in teleports[cur]:
            if visit[tele] == -1:
                visit[tele] = visit[cur] + 1
                q.put(tele)


main()
