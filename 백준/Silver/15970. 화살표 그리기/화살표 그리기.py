import sys

read = sys.stdin.readline
write = sys.stdout.write


def abs_diff(a, b):
    return abs(a - b)


def main():
    n = int(read())
    dots = [tuple(map(int, read().split())) for _ in range(n)]
    dots.sort()

    dists = [1e9 for _ in range(n)]
    for i in range(n - 1):
        for j in range(i + 1, n):
            if dots[i][1] != dots[j][1]:
                continue
            dists[i] = min(dists[i], abs_diff(dots[i][0], dots[j][0]))
            dists[j] = min(dists[j], abs_diff(dots[i][0], dots[j][0]))
    print(sum(dists))


main()
