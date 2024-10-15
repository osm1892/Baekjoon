import collections


def main():
    n = int(input())
    data = list(map(int, input().split()))
    data.sort()
    counter = collections.Counter(data)
    x = int(input())

    res = 0
    for i in data:
        if i >= x - i:
            break
        if x - i in counter:
            res += counter[x - i]

    print(res)


main()
