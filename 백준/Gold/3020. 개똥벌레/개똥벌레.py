import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n, h = map(int, read().split())
    arr = [int(read()) - 1 for _ in range(n)]
    lows = [0] * h
    highs = [0] * h

    for i in range(n // 2):
        lows[arr[i * 2]] += 1
    for i in range(len(lows) - 1, 0, -1):
        lows[i - 1] += lows[i]

    for i in range(n // 2):
        highs[arr[i * 2 + 1]] += 1
    for i in range(len(highs) - 1, 0, -1):
        highs[i - 1] += highs[i]

    costs = [(lows[i] + highs[h - i - 1]) for i in range(h)]

    min_cost = min(costs)
    count = costs.count(min_cost)
    print(min_cost, count)


main()
