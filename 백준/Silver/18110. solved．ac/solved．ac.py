import sys
import collections

read = sys.stdin.readline
# read = open("input.txt", "rt").readline
write = sys.stdout.write


def main():
    n = int(read())
    if n == 0:
        print(0)
        return
    data = [int(read()) for _ in range(n)]
    data.sort()
    exclude_count = round(n * 0.15 + 0.0000001)
    if exclude_count:
        data = data[exclude_count:-exclude_count]
    print(round(sum(data) / len(data) + 0.0000001))


main()
