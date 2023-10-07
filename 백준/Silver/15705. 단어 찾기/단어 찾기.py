import sys


read = sys.stdin.readline
write = sys.stdout.write


def main():
    dy = [-1, -1, 0, 1, 1, 1, 0, -1]
    dx = [0, 1, 1, 1, 0, -1, -1, -1]
    s = read().strip()
    n, m = map(int, read().split())
    data = sys.stdin.read().strip().splitlines()
    for y in range(n):
        for x in range(m):
            if s[0] != data[y][x]:
                continue
            for d in range(8):
                complete = True
                for i in range(1, len(s)):
                    ny = y + dy[d] * i
                    nx = x + dx[d] * i
                    if not (0 <= ny < n):
                        complete = False
                        break
                    if not (0 <= nx < m):
                        complete = False
                        break
                    if data[ny][nx] != s[i]:
                        complete = False
                        break
                if complete:
                    print(1)
                    return
    print(0)


main()
