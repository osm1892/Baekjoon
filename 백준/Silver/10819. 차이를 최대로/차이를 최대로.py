def dfs(data, order, visit):
    if len(order) == len(data):
        reordered = list(map(lambda i: data[i], order))
        res = 0
        for i in range(1, len(reordered)):
            res += abs(reordered[i - 1] - reordered[i])
        return res

    res = -10000000
    for i in range(len(data)):
        if visit[i]:
            continue
        new_visit = visit[:]
        new_visit[i] = True
        res = max(res, dfs(data, order + [i], new_visit))

    return res


def main():
    n = int(input())
    data = list(map(int, input().split()))

    res = -10000000
    for i in range(n):
        visit = [False for _ in data]
        visit[i] = True
        res = max(res, dfs(data, [i], visit))

    print(res)


main()
