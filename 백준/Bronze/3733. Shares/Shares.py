import sys


def main():
    for line in sys.stdin.readlines():
        a, b = map(int, line.split())
        print(b // (a + 1))


main()
