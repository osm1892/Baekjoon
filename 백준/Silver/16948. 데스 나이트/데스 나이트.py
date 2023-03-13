import collections


def main():
    n = int(input())
    r1, c1, r2, c2 = map(int, input().split())
    dy = [-2, -2, 0, 0, 2, 2]
    dx = [-1, 1, -2, 2, -1, 1]
    count = [[1e9] * n for _ in range(n)]

    que = collections.deque([(r1, c1)])
    count[r1][c1] = 0

    while que:
        y, x = que.popleft()

        if (y, x) == (r2, c2):
            print(count[y][x])
            return

        for d in range(6):
            ny = y + dy[d]
            nx = x + dx[d]

            cost = count[y][x] + 1

            if not (0 <= ny < n):
                continue
            if not (0 <= nx < n):
                continue
            if count[ny][nx] <= cost:
                continue

            que.append((ny, nx))
            count[ny][nx] = cost

    print(-1)


main()
