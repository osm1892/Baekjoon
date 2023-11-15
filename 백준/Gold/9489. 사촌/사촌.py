import collections
import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    while True:
        n, k = map(int, read().split())

        if n == 0:
            break

        data = list(map(int, read().split()))
        tree = {data[0]: []}
        pointer = -1

        for i in range(1, n):
            if data[i] != data[i - 1] + 1:
                pointer += 1

            tree[data[pointer]].append(data[i])
            tree[data[i]] = []

        k_depth = 0
        parent = 0
        result = 0

        deq = collections.deque()
        deq.append((data[0], 0))

        while deq:
            cur, depth = deq.popleft()

            for i in tree[cur]:
                if i == k:
                    k_depth = depth + 1
                    parent = cur
                    break
                deq.append((i, depth + 1))

        deq.clear()
        deq.append((data[0], 0))

        while deq:
            cur, depth = deq.pop()

            if parent in tree[cur]:
                for i in tree[cur]:
                    result += len(tree[i])
                result -= len(tree[parent])
                break

            for i in tree[cur]:
                deq.append((i, depth + 1))

        print(result)


main()
