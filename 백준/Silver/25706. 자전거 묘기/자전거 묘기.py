import sys


read = sys.stdin.readline
write = sys.stdout.write


def main():
    n = int(read())
    arr = list(map(int, read().split()))
    result = [0] * n
    for i in range(n - 1, -1, -1):
        cur = arr[i]
        next_idx = i + cur + 1
        cur_result = 1
        if next_idx < n:
            cur_result += result[next_idx]
        result[i] = cur_result

    print(*result)


main()
