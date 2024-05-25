def main():
    n, m = map(int, input().split())
    board = [list(map(lambda x: int(x == "W"), input())) for _ in range(n)]

    result = 1e9
    for y in range(n - 7):
        for x in range(m - 7):
            result = min(result, check(board, y, x))

    print(result)


def check(board, y0, x0):
    count = 0
    for y in range(8):
        for x in range(8):
            if board[y0 + y][x0 + x] != (y + x) % 2:
                count += 1

    return count if count < 32 else 64 - count


main()
