import sys

read = sys.stdin.readline
write = sys.stdout.write


def main():
    n = int(read())
    costs = [list(map(int, read().split())) for _ in range(n)]
    cost_vol = dict()
    for i in range(1 << n):
        mask = "{{:0{}b}}".format(n).format(i)
        vol, cost = 0, 0
        for j in range(n):
            if mask[j] == "1":
                vol += costs[j][0]
                cost += costs[j][1]
        if cost in cost_vol:
            cost_vol[cost] = min(vol, cost_vol[cost])
        else:
            cost_vol[cost] = vol

    test_case = int(read())
    for t in range(1, test_case + 1):
        volume, hour = map(int, read().split())
        result = 1 << 60
        for cost in cost_vol:
            if volume <= cost_vol[cost] * hour:
                result = min(result, cost)
        if result == 1 << 60:
            write("Case {}: IMPOSSIBLE\n".format(t))
        else:
            write("Case {}: {}\n".format(t, result))


main()
