import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n = int(read())
    fives = 0
    for i in range(5, n + 1):
        tmp = i
        while tmp % 5 == 0:
            fives += 1
            tmp //= 5
    print(fives)


main()
