import sys
import collections

read = sys.stdin.readline
# read = open("input.txt", "rt").readline
write = sys.stdout.write


def main():
    n = int(read())
    data = collections.Counter(map(int, read().split()))
    m = int(read())
    finds = list(map(int, read().split()))
    print(' '.join(map(lambda find: str(data.get(find, 0)), finds)))


main()
