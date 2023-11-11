import sys
import collections

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n, m = map(int, read().split())
    info = list(map(int, read().split()))
    watch = list(map(int, read().split()))
    result = 0

    stack = collections.deque()

    for i in range(len(info)):
        stack.append((1, i, info[i]))
        stack.append((1, i, watch[i]))

    while stack:
        day, pos, score = stack.pop()

        if day == n:
            result += score >= m
            continue

        for i in range(len(info)):
            if pos == i:
                stack.append((day + 1, i, score + info[i] // 2))
                stack.append((day + 1, i, score + watch[i] // 2))
            else:
                stack.append((day + 1, i, score + info[i]))
                stack.append((day + 1, i, score + watch[i]))

    print(result)


main()
