import sys
import collections

read = sys.stdin.readline
write = sys.stdout.write

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]

r, c, q = map(int, read().split())
photo = [list(map(int, read().split())) for i in range(r)]
row_sums = [[0] * c for i in range(r)]

for i in range(r):
    row_sums[i][0] = photo[i][0]
    for j in range(1, c):
        row_sums[i][j] = row_sums[i][j - 1] + photo[i][j]

for i in range(q):
    r1, c1, r2, c2 = map(lambda x: int(x) - 1, read().split())

    result = 0
    count = (r2 - r1 + 1) * (c2 - c1 + 1)
    for row in range(r1, r2 + 1):
        result += row_sums[row][c2] - row_sums[row][c1] + photo[row][c1]

    result //= count

    write("{}\n".format(result))
