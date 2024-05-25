import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    k, n = map(int, read().split())
    cables = list(map(int, sys.stdin.read().strip().split()))
    low = 0
    high = 1 << 31
    while low + 1 < high:
        mid = (low + high) // 2
        count = 0
        for cable in cables:
            count += cable // mid

        if count >= n:
            low = mid
        else:
            high = mid

    print(low)


main()
