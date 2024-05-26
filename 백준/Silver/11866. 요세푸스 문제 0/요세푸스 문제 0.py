import sys
import collections

read = sys.stdin.readline
# read = open("input.txt", "rt").readline
write = sys.stdout.write


def main():
    n, k = map(int, read().split())
    sequence = collections.deque(range(1, n + 1))
    output = []
    for i in range(n):
        sequence.rotate(-k + 1)
        output.append(sequence.popleft())
    print(f"<{', '.join(map(str, output))}>")


main()
