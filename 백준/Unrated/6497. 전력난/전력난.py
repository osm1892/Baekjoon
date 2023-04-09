import sys

read = sys.stdin.readline
write = sys.stdout.write


class CycleChecker:
    def __init__(self, size):
        self.parent = [i for i in range(size)]

    def union(self, a, b):
        a_root = self.get_root(a)
        b_root = self.get_root(b)

        if a_root > b_root:
            a_root, b_root = b_root, a_root

        self.parent[b_root] = a_root

    def get_root(self, x):
        if x == self.parent[x]:
            return x

        self.parent[x] = self.get_root(self.parent[x])

        return self.parent[x]

    def check(self, a, b):
        a_root = self.get_root(a)
        b_root = self.get_root(b)

        return a_root == b_root


def main():
    m, n = map(int, read().split())

    while m:
        edges = [tuple(map(int, read().split())) for _ in range(n)]
        edges.sort(key=lambda x: x[2])

        checker = CycleChecker(m)
        result = 0

        for x, y, z in edges:
            if checker.check(x, y):
                result += z
                continue

            checker.union(x, y)

        write(f"{result}\n")
        m, n = map(int, read().split())


main()
