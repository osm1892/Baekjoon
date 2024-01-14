import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    for t in range(int(read())):
        n, m, k = map(int, read().split())
        if k == 1 and m == 1:
            if n == 1:
                write("1\n")
            else:
                write("-1\n")
            continue
        n -= m * k
        count = 1
        while n > 0:
            n += 1
            n -= m * k
            count += 2
        write(f"{count}\n")


main()
