import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n = int(read())
    res = 0
    for i in range(666, 10000667):
        cnt = 0
        tmp = i
        while tmp:
            if tmp % 10 == 6:
                cnt += 1
                if cnt == 3:
                    res += 1
                    if res == n:
                        write(f"{i}\n")
                        return
                    break
            else:
                cnt = 0
            tmp //= 10


main()
