import collections
import sys


def main():
    left = collections.deque(input())
    right = collections.deque()

    m = int(input())

    for command in sys.stdin.readlines():
        if command[0] == "L":
            if left:
                c = left.pop()
                right.appendleft(c)
        elif command[0] == "D":
            if right:
                c = right.popleft()
                left.append(c)
        elif command[0] == "B":
            if left:
                left.pop()
        elif command[0] == "P":
            c = command[2]
            left.append(c)

    print("".join(left) + "".join(right))


main()
