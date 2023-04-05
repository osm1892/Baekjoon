import sys
import collections

read = sys.stdin.readline
write = sys.stdout.write

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]

row, col = map(int, read().split())
arr = [list(read().strip()) for i in range(row)]

stack = collections.deque()

for i in range(col):
    if arr[0][i] == "0":
        stack.append((0, i))

while stack:
    y, x = stack.pop()

    if arr[y][x] != "0":
        continue

    arr[y][x] = "2"

    for d in range(4):
        ny = y + dy[d]
        nx = x + dx[d]

        if not (0 <= ny < row):
            continue
        if not (0 <= nx < col):
            continue

        stack.append((ny, nx))

finish = False
for i in range(col):
    if arr[row - 1][i] == "2":
        finish = True
        break

if finish:
    print("YES")
else:
    print("NO")
