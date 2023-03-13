import collections


def main():
    n = int(input())
    results = [calc(n, i) for i in range(1, n + 1)]
    result = max(results)
    print(result[0])
    for i in result[1]:
        print(i, end=" ")


def calc(first, second):
    prev = second
    cur = first - second
    history = collections.deque([first, second])

    count = 2
    while cur >= 0:
        history.append(cur)
        tmp = prev - cur
        prev = cur
        cur = tmp
        count += 1

    return count, history


main()
