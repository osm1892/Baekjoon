import collections


def main():
    dy = [-1, 0, 1, 0]
    dx = [0, 1, 0, -1]
    n = int(input())
    arr = [list(map(int, input())) for i in range(n)]
    visit = [[1e9] * n for _ in range(n)]
    que = collections.deque()
    que.appendleft((0, 0))
    visit[0][0] = 0

    while que:
        y, x = que.popleft()

        if (y, x) == (n - 1, n - 1):
            print(visit[y][x])
            return

        for d in range(4):
            ny = y + dy[d]
            nx = x + dx[d]

            if not (0 <= ny < n):
                continue
            if not (0 <= nx < n):
                continue

            cost = visit[y][x] + 1 - arr[ny][nx]

            if visit[ny][nx] <= cost:
                continue

            if arr[ny][nx] == 0:
                que.append((ny, nx))
            else:
                que.appendleft((ny, nx))

            visit[ny][nx] = cost


main()
