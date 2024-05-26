import sys
import collections

read = sys.stdin.readline
# read = open('input.txt', 'rt').readline
write = sys.stdout.write


def main():
    n = int(read())
    cards = collections.deque(range(1, n + 1))
    while len(cards) > 1:
        cards.popleft()
        cards.rotate(-1)
    print(cards[0])


main()
