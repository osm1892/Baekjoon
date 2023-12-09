import collections
import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    dy = (-1, 0, 1, 0)
    dx = (0, 1, 0, -1)

    size = int(read())
    apple_count = int(read())
    board = [[0 for _ in range(size)] for _ in range(size)]
    for i in range(apple_count):
        y, x = map(int, read().split())
        board[y - 1][x - 1] = 2

    change_count = int(read())
    changes = {}
    for i in range(change_count):
        x, c = read().split()
        x = int(x)
        c = 1 if c == "D" else -1
        changes[x] = c

    snake = collections.deque()
    snake.append((0, 0))
    direction = 1
    count = 0
    while True:
        count += 1
        y, x = snake[-1]

        ny = y + dy[direction]
        nx = x + dx[direction]

        if not (0 <= ny < size):
            break
        if not (0 <= nx < size):
            break
        if board[ny][nx] == 1:
            break

        if board[ny][nx] == 0:
            tail = snake.popleft()
            board[tail[0]][tail[1]] = 0

        board[ny][nx] = 1
        snake.append((ny, nx))

        direction = (direction + changes.get(count, 0)) % 4

    print(count)


main()
