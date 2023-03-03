def main():
    dy = [-1, 0, 1, 0]
    dx = [0, 1, 0, -1]
    n, m, k = map(int, input().split())
    arr = [input() for _ in range(n)]
    dest = input()
    size = len(dest)

    dp = [[[0] * size for _x in range(m)] for _y in range(n)]
    for y in range(n):
        for x in range(m):
            if arr[y][x] == dest[0]:
                dp[y][x][0] = 1

    for depth in range(1, size):
        for y in range(n):
            for x in range(m):
                if arr[y][x] != dest[depth]:
                    continue
                for d in range(4):
                    for mul in range(1, k + 1):
                        ny = y + dy[d] * mul
                        nx = x + dx[d] * mul

                        if not (0 <= ny < n):
                            continue
                        if not (0 <= nx < m):
                            continue

                        dp[y][x][depth] += dp[ny][nx][depth - 1]

    result = 0
    for y in range(n):
        for x in range(m):
            result += dp[y][x][size - 1]

    print(result)


main()
