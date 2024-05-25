import sys
import collections

read = sys.stdin.readline
# read = open('input.txt', 'rt').readline
write = sys.stdout.write


def main():
    for t in range(int(read())):
        n, m = map(int, read().split())
        data = list(map(int, read().split()))
        queue = collections.deque(enumerate(data))
        counter = collections.Counter(data)
        result = 0
        while queue:
            index, priority = queue.popleft()
            printable = True
            for j in range(priority + 1, 10):
                if counter.get(j):
                    printable = False
                    break
            
            if printable:
                result += 1
                counter[priority] -= 1
                if index == m:
                    print(result)
                    break
            else:
                queue.append((index, priority))


main()
