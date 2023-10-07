import sys


read = sys.stdin.readline
write = sys.stdout.write


def main():
    read()
    cases = sys.stdin.read().strip().removesuffix("\n0").split("\n0\n")

    for case in cases:
        arr = list(map(int, case.strip().split("\n")))
        arr = sorted(arr, reverse=True)
        result = 0
        for i, v in enumerate(arr):
            result += v ** (i + 1) * 2
        if result > 5000000:
            write("Too expensive\n")
        else:
            write(f"{result}\n")


main()
