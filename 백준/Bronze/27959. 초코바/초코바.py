import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n, m = map(int, read().split())
    if n * 100 >= m:
        print("Yes")
    else:
        print("No")


main()
