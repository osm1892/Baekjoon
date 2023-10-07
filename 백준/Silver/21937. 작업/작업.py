import collections
import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n, m = map(int, read().split())
    tree = collections.defaultdict(list)
    for i in range(m):
        a, b = map(int, read().split())
        tree[b].append(a)
    dest = int(read())
    stack = collections.deque()
    visit = set()
    stack.append(dest)
    while stack:
        cur = stack.pop()
        if cur in visit:
            continue
        visit.add(cur)

        for i in tree[cur]:
            stack.append(i)
    print(len(visit) - 1)


main()
