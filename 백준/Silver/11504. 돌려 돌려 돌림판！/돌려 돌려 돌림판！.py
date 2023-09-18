import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    test_case = int(read())

    for t in range(test_case):
        n, m = map(int, read().split())
        x = int("".join(read().split()))
        y = int("".join(read().split()))
        arr = list(map(int, read().split()))
        result = 0

        for i in range(-n, 0):
            cur = 0
            for j in range(m):
                cur = cur * 10 + arr[i + j]

            if x <= cur <= y:
                result += 1

        write(f"{result}\n")


main()
