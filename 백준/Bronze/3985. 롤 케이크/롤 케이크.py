import collections
import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    l = int(read())
    n = int(read())

    wants = [list(map(lambda x: int(x) - 1, read().split())) for _ in range(n)]
    wants_sorted = sorted(
        list(enumerate(wants)), key=lambda x: (x[1][0] - x[1][1], x[0])
    )
    print(wants_sorted[0][0] + 1)

    cake = [-1 for _ in range(l)]
    for i in range(n):
        for j in range(wants[i][0], wants[i][1] + 1):
            if cake[j] != -1:
                continue
            cake[j] = i
    counter = collections.Counter(cake)
    del counter[-1]
    result = sorted(counter.items(), key=lambda x: -x[1])
    print(result[0][0] + 1)


main()
