import sys
import collections

read = sys.stdin.readline
# read = open("input.txt", "rt").readline
write = sys.stdout.write


def main():
    t = int(read())
    for _ in range(t):
        data = read().strip()
        res = check(data)

        if res:
            print("YES")
        else:
            print("NO")


def check(data):
    stack = []
    for i in data:
        if i == "(":
            stack.append(i)
        else:
            if not stack:
                return False
            stack.pop()
    return not stack


main()
