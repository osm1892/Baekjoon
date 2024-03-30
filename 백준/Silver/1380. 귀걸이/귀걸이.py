import sys


def read() -> str:
    return sys.stdin.readline()


def write(x):
    sys.stdout.write(x)


def main():
    test_case = 1
    while True:
        n = int(read())
        if n == 0:
            return
        names = [read().strip() for _ in range(n)]
        flags = [False] * n
        for i in range(2 * n - 1):
            num, alpha = read().split()
            num = int(num) - 1
            flags[num] = not flags[num]

        write(f"{test_case} {names[flags.index(True)]}\n")

        test_case += 1


main()
