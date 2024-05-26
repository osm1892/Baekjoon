import sys
import collections

read = sys.stdin.readline
# read = open("input.txt", "rt").readline
write = sys.stdout.write


def main():
    k = int(read())
    stack = []
    for _ in range(k):
        num = int(read())
        if num:
            stack.append(num)
        else:
            stack.pop()
    
    print(sum(stack))


main()
